void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial.println("Arduino 2!");
}

String receiveCommand() {
  while (Serial1.available() == 0) {
  }
  String command_received = Serial1.readStringUntil('\r');
  //  Serial.println("Acknowledgement Sent");
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
  Serial.println("received Command: " + complete_command);

  if (command == "zaxis_down") {
    Serial.print("z axis going down in this distance: ");
    Serial.println(distance);
    delay(1000);
  }
  else if (command == "sort_topet") {
    Serial.println("aligning sorter to PET bin...");
    delay(1000);
  }
  else if (command == "sort_tocan") {
    Serial.println("aligning sorter to CAN bin...");
    delay(1000);
  }
  else if (command == "conv___fwd") {
    Serial.println("Moving conveyor forward...");
    delay(2000);
  }
  else if (command == "open__gate") {
    Serial.println("Opening Gate...");
    delay(1000);
  }
  else if (command == "close_gate") {
    Serial.println("Closing Gate...");
    delay(1000);
  }
  else if (command == "zaxis_home") {
    Serial.println("Homing z-axis...");
    delay(1000);
  }
  else if (command == "conv__back") {
    Serial.println("rejecting recyclable...");
    delay(1000);
  }
  
  else{
   //do nothing
   }

   sendDone();



}
