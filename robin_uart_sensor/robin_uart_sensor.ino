/*
 * Pin Connection for UART communication:
 *  arduino1                arduino2
 *  tx1======================>rx1
 *  rx1======================>tx1
 *  tx2======================>rx2
 *  rx2======================>tx2
 */

#include "classes.h"
bool z_axis_down = false;

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600); //mainly just for sending data to rx1 of arduino2
  Serial.begin(9600); //for sending operation logs to Rpi
  Serial2.begin(9600); //mainly for receiving data from tx2 of arduino2
  //  Serial.println("Arduino 1!");
  sendCommandWaitAck("zaxis_home;");//homing
}

bool sendCommandWaitAck(String command) {
  String command1 = command + "\r";
  Serial1.write(command1.c_str());
  while (Serial2.available() == 0) {

  }
  String command_received = Serial2.readStringUntil('\r');
  //  Serial.print("Acknowledgement received: ");
  //  Serial.println(command_received);
  if (command_received == "done") {

    return true;
  }
  return false;
}

void loop() {
  // put your main code here, to run repeatedly:
  int diameter = ultrasonic1.Measure(); //ultrasonic near the chute
  bool homed = true; //to be replaced by response from IR sensor for homing
  bool petBinPresence = true; //to be replaced by ultrasonic reading from PET bin
  bool canBinPresence = true; //to be replaced by ultrasonic reading from CAN bin
  if ((diameter > 3) && petBinPresence && canBinPresence && homed) {
    z_axis_down = sendCommandWaitAck("zaxis_down;" + String(chute_diameter - diameter));
    if (z_axis_down) {
      //classify if recyclable is PET or CAN
      String inductive1_reading = "PET";//debugging  //inductive_reading = Inductive1.Classify(); should return string
      String capacitive1_reading = "PET";//debugging //capacitive_reading = Capacitive1.Classify();should return string
      if (capacitive1_reading == inductive1_reading) {
        if (capacitive1_reading == "PET") {
          sendCommandWaitAck("sort_topet;");//adjusts the sorter in advance
        }
        else {
          sendCommandWaitAck("sort_tocan;");//adjusts the sorter in advance
        }
        sendCommandWaitAck("conv___fwd;");//moves the recyclable forward
        //classify if recyclable is PET or CAN
        String inductive2_reading = "PET";//debugging  //inductive_reading = Inductive2.Classify();
        String capacitive2_reading = "PET";//debugging //capacitive_reading = Capacitive2.Classify();
        if (capacitive2_reading == inductive2_reading) {
          sendCommandWaitAck("open__gate;");
          sendCommandWaitAck("conv___fwd;");
          sendCommandWaitAck("zaxis_home;");
          sendCommandWaitAck("close_gate;");
          //successful run, added "pass" to the string to be sent to rpi for data logging and determining of reward
          Serial.println(String(diameter) + ";" + capacitive1_reading + ";" + inductive1_reading + ";" + capacitive2_reading + ";" + inductive2_reading + ";pass;");
        }
        else {
          //failed run, added "fail" to the string to be sent to rpi for data logging. might be changed.
          Serial.println(String(diameter) + ";" + capacitive1_reading + ";" + inductive1_reading + ";" + capacitive2_reading + ";" + inductive2_reading + ";fail;");
      }
    }
    else {
      if ((sendCommandWaitAck("conv__back;") == 1) && (sendCommandWaitAck("zaxis_home;") == 1)) {
        //failed run, added "fail" to the string to be sent to rpi for data logging
        Serial.println(String(diameter) + ";" + capacitive1_reading + ";" + inductive1_reading + ";null;null;fail;");
      }
    }
  }
}
//do nothing when diameter is the diameter of the chute
delay(1000);
}
