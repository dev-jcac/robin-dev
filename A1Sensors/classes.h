#include "config_sensors.h"
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

    int Measure() {
        // Clears the trigPin condition
      digitalWrite(TrigPin, LOW);
      delayMicroseconds(2);
      // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
      digitalWrite(TrigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(TrigPin, LOW);
      // Reads the echoPin, returns the sound wave travel time in microseconds
      long duration = pulseIn(EchoPin, HIGH);
      // Calculating the distance
      int distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
      // Displays the distance on the Serial Monitor
//      Serial.print("Distance: ");
      Serial.println(distance);
//      Serial.println(" cm");
    }
};

Ultrasonic ultrasonic1(ultrasonic1_trig_pin , ultrasonic1_echo_pin);
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
    bool Classify() {
      int capacitance = analogRead(SensorPin);
      if (capacitance >= 150) { //change values and logic soon
        Serial.println("1");
        return 1;
      }
      Serial.println("0");
      return 0;
    }
};
Capacitive capacitive1(capacitive1_sensor_pin);
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
    bool Classify() {
      int inductance = analogRead(SensorPin);
      if (inductance >= 150) { //change values and logic soon
        return 1;
      }
      return 0;
    }
};
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

class Door{
    int SensorPin;
  public:
    Door(int sensorPin) {
      SensorPin = sensorPin;
      pinMode(SensorPin, INPUT);
    }
    bool Confirm() {
      int closeDoor = digitalRead(SensorPin);
      if (closeDoor == 1) {
        return 1;
      }
      return 0;
    }
};
/*USAGE:
   Door door(door_sensor_pin); //(digital pin for hall effect sensor)
   door.Confirm() //returns 1 or 0
*/
