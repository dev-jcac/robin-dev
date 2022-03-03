#include "pin_config.h"
int chute_diameter = 12;
class Ultrasonic {
    int TrigPin;
    int EchoPin;
    int CurrentDistance;
  public:
    Ultrasonic(int trigpin, int echopin) { //if does not work, try removing void
      TrigPin = trigpin;
      EchoPin = echopin;
      pinMode(TrigPin, OUTPUT);
      pinMode(EchoPin, INPUT);
      digitalWrite(TrigPin, LOW);
    }

    int getDiameter() {
      digitalWrite(TrigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(TrigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(TrigPin, LOW);
      long duration = pulseIn(EchoPin, HIGH);
      int distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
      // Displays the distance on the Serial Monitor
      // Serial.print("Distance: ");
      // Serial.println(" cm");
      return chute_diameter - distance;
    }
    bool isDetected() {
      digitalWrite(TrigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(TrigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(TrigPin, LOW);
      long duration = pulseIn(EchoPin, HIGH);
      int distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
      // Displays the distance on the Serial Monitor
      // Serial.print("Distance: ");
      // Serial.println(" cm");
      if (distance < 10) {
        return true;
      }
      return false;
    }
};

Ultrasonic ultrasonic1(ultrasonic1_trig_pin , ultrasonic1_echo_pin);
Ultrasonic petbin(ultrasonic3_trig_pin , ultrasonic3_echo_pin);
Ultrasonic canbin(ultrasonic4_trig_pin , ultrasonic4_echo_pin);
/*USAGE:
  Ultrasonic ultrasonic1(ultrasonic1_trig_pin , ultrasonic1_echo_pin); //-> (trigger pin, echo pin)
  Ultrasonic ultrasonic2(ultrasonic2_trig_pin , ultrasonic2_echo_pin); //->(trigger pin, echo pin)
  and.... ultrasonic1.Measure(); //etc //returns diameter
*/

class Capacitive {
    int SensorPin;
  public:
    Capacitive (int sensorPin) { //if does not work, try removing void
      SensorPin = sensorPin;
      pinMode(sensorPin, INPUT);
    }
    String Classify() {
      int capacitance = analogRead(SensorPin);
      if (capacitance >= 150) { //change values and logic soon
        //        Serial.println("1");
        return "PET";
      }
      //      Serial.println("0");
      return "CAN";
    }
};
Capacitive capacitive1(capacitive1_sensor_pin);
Capacitive capacitive2(capacitive2_sensor_pin);
/*USAGE:
  Capacitive capacitive1(capacitive1_sensor_pin); //(analog pin for capacitive sensor
  Capacitive capacitive2(capacitive2_sensor_pin); //(analog pin for capacitive sensor

  capacitive1.Classify(); //returns 1 or 0
*/

class Inductive {
    int SensorPin;
  public:
    Inductive (int sensorPin) { //if does not work, try removing void
      SensorPin = sensorPin;
      pinMode(sensorPin, INPUT);
    }
    String Classify() {
      int inductance = analogRead(SensorPin);
      if (inductance >= 150) { //change values and logic soon
        return "PET";
      }
      return "CAN";
    }
};
Inductive inductive1(inductive1_sensor_pin); //(analog pin for inductive sensor)
Inductive inductive2(inductive2_sensor_pin); //(analog pin for inductive sensor)
/*USAGE:
  Inductive inductive1(inductive1_sensor_pin); //(analog pin for inductive sensor)
  inductive1.Classify(); //returns 1 or 0
*/

class Ir {
    int SensorPin;
  public:
    Ir(int sensorPin) {
      SensorPin = sensorPin;
      pinMode(SensorPin, INPUT);
    }
    bool Confirm() {
      int checkObject = digitalRead(SensorPin);
      if (checkObject == 1) {
        return 1;
      }
      return 0;
    }
};
/*USAGE:
   Ir ir (ir1_sensor_pin); //(digital pin for IR sensor)
   ir.Confirm() //returns 1 or 0
*/

class Hall {
    int SensorPin;
  public:
    Hall(int sensorPin) {
      SensorPin = sensorPin;
      pinMode(SensorPin, INPUT);
    }
    bool Confirm() {
      int checkMagnet = digitalRead(SensorPin);
      if (checkMagnet == 1) {
        return 1;
      }
      return 0;
    }
};
Hall doorSensor(door_sensor_pin);
/*USAGE:
   Door door(door_sensor_pin); //(digital pin for hall effect sensor)
   door.Confirm() //returns 1 or 0
*/
