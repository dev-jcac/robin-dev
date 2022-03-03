String deviceID = "sensors";
//Set of sensors on the z-axis and near the chute
int ultrasonic1_echo_pin = 2;
int ultrasonic1_trig_pin = 3;
int capacitive1_sensor_pin = A0;
int inductive1_sensor_pin = A1;

//Set of sensors on the z-axis and near the gate
int capacitive2_sensor_pin = A2;
int inductive2_sensor_pin = A3;

//Sensor for Door status
int door_sensor_pin = 4;

//Sensor for verifying bin's insertion status
int ultrasonic3_trig_pin = 5; // for PET
int ultrasonic3_echo_pin = 6; // for PET
int ultrasonic4_trig_pin = 7; // for CAN
int ultrasonic4_echo_pin = 8; // for CAN
