#include "classes.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    char commandChar = command[0];
    switch (commandChar) {
      case 'a':
        //some logic to dispay device ID
        Serial.println(deviceID);
        break;
      case 'b':
        //do something
        Serial.println("pressed B");
        break;
      case 'c':
        //do something
        Serial.println("pressed C");
        break;
      case 'd':
        //do something
        Serial.println("pressed D");
        break;
      default:
        //do nothing
        break;
    }
  }
}
