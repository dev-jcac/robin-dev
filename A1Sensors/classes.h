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
      digitalWrite(TrigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(TrigPin, LOW);
      int Time = pulseIn(EchoPin, HIGH, 5000);
      CurrentDistance = Time * 0.1715; //to have additional logic to compute the diameter of the item
      return CurrentDistance; // to be replaced with "diameter"
    }
};


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
        return 1;
      }
      return 0;
    }
};

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
