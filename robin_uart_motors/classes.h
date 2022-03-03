#include "pin_config.h"
#include "Servo.h"
#define stepsPerRevolution 200
Servo gateServo;
Servo sorterServo;

void openGate() {
  gateServo.write(90);
  delay(100);
}

void closeGate() {
  gateServo.write(0);
  delay(10);
}

void paddleToPetBin() {
  sorterServo.write(90);
  delay(10);
}

void paddleToCanBin() {
  sorterServo.write(0);
  delay(10);
}

class Conveyor {
    int Positive;
    int Negative;
  public:
    Conveyor(int positive, int negative) {
      Positive = positive;
      Negative = negative;
      pinMode(Positive, OUTPUT);
      pinMode(Negative, OUTPUT);
    }
    void Forward() {
      digitalWrite(Positive, HIGH);
      digitalWrite(Negative, LOW);
    }
    void Reverse(int duration) {
      digitalWrite(Positive, LOW);
      digitalWrite(Negative, HIGH);
      delay(duration);
      digitalWrite(Positive, LOW);
      digitalWrite(Negative, LOW);
    }
    void Stop() {
      digitalWrite(Positive, LOW);
      digitalWrite(Negative, LOW);
    }
};
Conveyor conv(conveyorMotor1Positive, conveyorMotor1Negative );

/*USAGE:
  Conveyor convLeft(conveyorMotor1Positive, conveyorMotor1Negative );
  Conveyor convRight(conveyorMotor2Positive,conveyorMotor2Negative);

  convleft.Forward();
  convleft.Reverse(); etc
*/

class Z_axis {

    int Dir_pin;
    int Step_pin;
  public:
    Z_axis(int dir_pin, int step_pin) {
      Dir_pin = dir_pin;
      Step_pin = step_pin;
      pinMode(Dir_pin, OUTPUT);
      pinMode(Step_pin, OUTPUT);
    }
    void Up(int distance) {
      digitalWrite(Dir_pin, HIGH);//clockwise
      for (int i; i < distance * stepsPerRevolution; i++) {
        digitalWrite(Step_pin, HIGH);
        delayMicroseconds(1000);
        digitalWrite(Step_pin, LOW);
        delayMicroseconds(1000);
      }
    }
    void Down(int distance) {
      digitalWrite(Dir_pin, LOW); //counterclockwise
      for (int i; i < distance * stepsPerRevolution; i++) {
        digitalWrite(Step_pin, HIGH);
        delayMicroseconds(500);
        digitalWrite(Step_pin, LOW);
        delayMicroseconds(500);
      }
    }
};

Z_axis z_axis(zAxisDirPin, zAxisStepPin);


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
      digitalWrite(TrigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(TrigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(TrigPin, LOW);
      long duration = pulseIn(EchoPin, HIGH);
      int distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
      // Displays the distance on the Serial Monitor
      //      Serial.print("Distance: ");
      //      return chute_diameter - distance;
      //      Serial.println(" cm");
    }
    bool isOpen() {
      digitalWrite(TrigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(TrigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(TrigPin, LOW);
      long duration = pulseIn(EchoPin, HIGH);
      int distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
      if (distance > 5) {
        return true;
      }
      return false;
    }
    bool hasDetectedObject() {
      digitalWrite(TrigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(TrigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(TrigPin, LOW);
      long duration = pulseIn(EchoPin, HIGH);
      int distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
      if (distance > 5) {
        return true;
      }
      return false;
    }
};


Ultrasonic ultrasonic_zaxis(ultrasonic_trig_pin , ultrasonic_echo_pin);
Ultrasonic gate(ultrasonic1_trig_pin , ultrasonic1_echo_pin);

class Ir {
    int SensorPin;
  public:
    Ir(int sensorPin) {
      SensorPin = sensorPin;
      pinMode(SensorPin, INPUT);
    }
    bool isHit() {
      int checkObject = digitalRead(SensorPin);
      if (checkObject == 1) {
        return true;
      }
      return false;
    }
};
Ir irTopLimit(ir1_sensor_pin);
Ir irBottomLimit(ir2_sensor_pin);
Ir irHome(ir3_sensor_pin);
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
Hall PaddlePet(hall1_sensor_pin);
Hall PaddleCan(hall2_sensor_pin);
/*USAGE:
   Door door(door_sensor_pin); //(digital pin for hall effect sensor)
   door.Confirm() //returns 1 or 0
*/
