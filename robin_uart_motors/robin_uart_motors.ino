/* //test_change
   Pin Connection for UART communication:
    arduino1                arduino2
    tx1======================>rx1
    rx1======================>tx1
    tx2======================>rx2
    rx2======================>tx2
*/
#include "classes.h"

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  Serial2.begin(9600);
  // Serial.println("Arduino 2!");
}

String receiveCommand() {
  while (Serial1.available() == 0) {
  }
  String command_received = Serial1.readStringUntil('\r');
  // Serial.println("Acknowledgement Sent");
  return command_received;
}

void sendDone() {
  Serial2.write("done\r");

}
void loop() {
  // put your main code here, to run repeatedly:
  String complete_command = receiveCommand();
  String command = complete_command.substring(0, 10);
  String zaxis_distance = complete_command.substring(11, 13);
  int distance = zaxis_distance.toInt();
  // Serial.println("received Command: " + complete_command);

  if (command == "zaxis_down") {
    //move the z axis down based from the distance given by the other arduino.
    z_axis.Down(distance);
    delay(500);
  }
  else if (command == "sort_topet") {
    //use hall sensor to verify position of paddle.
    while (!PaddlePet.Confirm()) {
      paddleToPetBin();
    }
    delay(500);
  }
  else if (command == "sort_tocan") {
    //use hall sensor to verify position of paddle.
    while (!PaddleCan.Confirm()) {
      paddleToCanBin();
    }
    delay(500);
  }
  else if (command == "conv___fwd") {
    //use Ultrasonic to determine until when the conveyors are to be run forward.
    while (!ultrasonic_zaxis.hasDetectedObject()) {
      conv.Forward();
    }
    conv.Stop();
    delay(500);
  }
  else if (command == "open__gate") {
    //use ultrasonic to determine if gate is really opened.
    while (gate.isOpen() != true) {
      openGate();
    }
    delay(500);
  }
  else if (command == "close_gate") {
    //use ultrasonic to determine if gate is really opened.
    while (gate.isOpen() == true) {
      closeGate();
    }
    delay(500);
  }
  else if (command == "zaxis_home") {
    //use IR for homing
    while (!irHome.isHit()) {
      z_axis.Up(10);//jog 1cm up until ir sensor for homing is hit.
    }
    delay(1000);
  }
  else if (command == "conv__back") {
    //fixed distance
    conv.Reverse(1000); //reverse conveyor by 1000milliseconds or 1sec
    delay(500);
  }
  else {
    //do nothing
  }
  sendDone();
}
