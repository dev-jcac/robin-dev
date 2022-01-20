class Ultrasonic {
    int TrigPin;
    int EchoPin;
    int CurrentDistance;

  public:
    void ultrasonic (int trigpin, int echopin) { //if does not work, try removing void
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
  Ultrasonic ultrasonic1(ultrasonic1_trig_pin,ultrasonic1_echo_pin); -> (trigger pin, echo pin)
  Ultrasonic ultrasonic2(ultrasonic2_trig_pin,ultrasonic2_echo_pin); ->(trigger pin, echo pin)

  and.... ultrasonic1.Measure(); etc  -> returns diameter ideally.
*/


class Capactive {
    int SensorPin;
  public:
    void capactive (int sensorPin) { //if does not work, try removing void
      SensorPin = sensorPin;
      pinMode(sensorPin, INPUT);
    }
    bool Measure() {
      int capacitance = analogRead(SensorPin);
      if (capacitance >= 150) { //change values and logic soon
        return 1;
      }
      return 0;
    }
};
/*USAGE:
  Capacitive capacitive1(capacitive1_sensor_pin); (analog pin for capacitive sensor
  Capacitive capacitive1(capacitive2_sensor_pin); (analog pin for capacitive sensor
  
  capacitive1.Measure(); -> returns 1 or 0
*/

class Inductive {
    int SensorPin;
  public:
    void inductive (int sensorPin) { //if does not work, try removing void
      SensorPin = sensorPin;
      pinMode(sensorPin, INPUT);
    }
    bool Measure() {
      int inductance = analogRead(SensorPin);
      if (inductance >= 150) { //change values and logic soon
        return 1;
      }
      return 0;
    }
};
/*USAGE:
  Inductive inductive1(inductive1_sensor_pin); -> (analog pin for inductive sensor
  inductive1.Measure(); -> returns 1 or 0

*/

class Ir {
    int SensorPin;
  public:
    void ir(int sensorPin) {
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
   Ir ir (ir1_sensor_pin); -> (digital pin for IR sensor)
   Ir.Confirm
*/
