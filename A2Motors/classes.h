#include <Servo.h>
Servo gateServo;
Servo sorterServo;

void openGate() {
  gateServo.write(90);
  delay(10);
}

void closeGate() {
  gateServo.write(0);
  delay(10);
}

void toPetBin(){
  sorterServo.write(90);
  delay(10);
  }

void toCanBin(){
  sorterServo.write(0);
  delay(10);
  ope}

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
    void Reverse() {
      digitalWrite(Positive, LOW);
      digitalWrite(Negative, HIGH);
    }
    void Stop() {
      digitalWrite(Positive, LOW);
      digitalWrite(Negative, LOW);
    }
};
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
    z_axis(int dir_pin, int step_pin) {
      Dir_pin = dir_pin;
      Step_pin = step_pin;
      pinMode(Dir_pin, OUTPUT);
      pinMode(Step_pin, OUTPUT);
    }
    void Up() {
      digitalWrite(Dir_pin, HIGH);
      digitalWrite(Step_pin, HIGH);
    }
    void Down() {
      digitalWrite(Dir_pin, LOW);
      digitalWrite(Step_pin, HIGH);
    }
};
