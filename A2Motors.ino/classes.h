#include <Servo.h>
Servo gateServo;

void openGate() {
  gateServo.write(90);
  delay(10);
}

void closeGate() {
  gateServo.write(0);
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
      delay(1000);
    }
    void Reverse() {
      digitalWrite(Positive, LOW);
      digitalWrite(Negative, HIGH);
      delay(1000);
    }
};
/*USAGE:
  Conveyor convLeft(conveyorMotor1Positive, conveyorMotor1Negative );
  Conveyor convRight(conveyorMotor2Positive,conveyorMotor2Negative);

  convLeft.Forward();
  convRight.Reverse(); etc
*/
