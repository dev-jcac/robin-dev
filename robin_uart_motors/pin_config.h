String deviceID = "00-motors";
int conveyorMotor1Positive = 2;
int conveyorMotor1Negative = 3;
int conveyorMotor2Positive = 4;
int conveyorMotor2Negative = 5;
int zAxisDirPin = 5;
int zAxisStepPin = 6;
int gateServoPin = 7;
int serterServoPin = 8;

//Set of sensors for top limit, bottom limit, and home of z-axis
int ir1_sensor_pin = 24; // top limit
int ir2_sensor_pin = 25; // bottom limit
int ir3_sensor_pin = 26; // home

//Set of sensors for conveyor movement verification
int ir4_sensor_pin = 27; // left  conveyor
int ir5_sensor_pin = 28; // right conveyor

//Sensor for gate open/close status
int ultrasonic_trig_pin = 22;
int ultrasonic_echo_pin = 23;
int ultrasonic1_trig_pin = 29;
int ultrasonic1_echo_pin = 30;

//Sensor for Paddle position/status
int hall1_sensor_pin = 31;
int hall2_sensor_pin = 32;
