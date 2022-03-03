/*
   Pin Connection for UART communication:
    arduino1                arduino2
    tx1======================>rx1
    rx1======================>tx1
    tx2======================>rx2
    rx2======================>tx2
*/

#include "classes.h"
bool z_axis_down = false;

void setup() {
  Serial1.begin(9600); //mainly just for sending data to rx1 of arduino2
  Serial2.begin(9600); //mainly for receiving data from tx2 of arduino2
  Serial.begin(9600); //for sending operation logs to Rpi
  sendCommandWaitAck("zaxis_home;");//homing
}

bool sendCommandWaitAck(String command) {
  //concatinates received string with delimiter \r
  String command1 = command + "\r";
  //Sends command to Serial1 (rx1) of Arduino for motors
  Serial1.write(command1.c_str());
  //waits for an acknowledgement and status reply
  while (Serial2.available() == 0) {
  }
  //processing of reply if successfully execute(done) or not
  String command_received = Serial2.readStringUntil('\r');
  if (command_received == "done") {
    return true;
  }
  return false;
}

void loop() {
  int diameter = ultrasonic1.getDiameter(); //ultrasonic near the chute
  bool petBinPresence = petbin.isDetected();
  bool canBinPresence = canbin.isDetected();
  bool doorClosed = doorSensor.Confirm();
  if ((diameter > 3) && petBinPresence && canBinPresence && doorClosed) {
    z_axis_down = sendCommandWaitAck("zaxis_down;" + String(chute_diameter - diameter));
    if (z_axis_down) {
      //classify if recyclable is PET or CAN (round 1)
      String inductive1_reading = inductive1.Classify();
      String capacitive1_reading = capacitive1.Classify();
      if (capacitive1_reading == inductive1_reading) {
        if (capacitive1_reading == "PET") {
          sendCommandWaitAck("sort_topet;");//adjusts the sorter in advance
        }
        else {
          sendCommandWaitAck("sort_tocan;");//adjusts the sorter in advance
        }
        sendCommandWaitAck("conv___fwd;");//moves the recyclable forward
        //classify if recyclable is PET or CAN (round 2)
        String inductive2_reading = inductive2.Classify();
        String capacitive2_reading = capacitive2.Classify();
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
