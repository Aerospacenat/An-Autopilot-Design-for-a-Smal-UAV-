//627 lines of code so far 22/01/21
//1142 lines of code so far 19/02/21
//982 lines of code 22/02/21
#include <Servo.h>//Using servo library to control ESC
#include <Wire.h>  //i2c libary
#include <math.h>
#include <Scheduler.h> // multiple loops libary
#include <MPU6050_light.h> // IMU libary

#include "TFMini.h" // Lidar libary
//#define GND0  0 // define pin 0 as ground
//#define GND1  1
#define GND2  2
#define GND3  3
#define GND4  37
#define GND5  39
#define GND6  41
#define GND7  43


TFMini tfmini; //Lidar libary
MPU6050 mpu(Wire); // IMU declaring

Servo m1; //Creating a servo class with name as m1
Servo m2; //Creating a servo class with name as m2
Servo m3; //Creating a servo class with name as m3
Servo m4; //Creating a servo class with name as m4
long DistDown; // ultrasonic sensor down
long DistLeft; // ultrasonic sensor left
long DistRight; // ultrasonic sensor right
long DistBack; // ultrasonic sensor back
/////////Ultrasonic sensors from pico //////////////
bool Left;
bool Down;
bool Right;
bool Behind;
bool TOHeightR; //Take off Height Reached
bool LDGNDR; // Landing Ground Reached
String data; // data from the PI Pico
String lastData; // last data from Pi Pico
////////////////////////////////////////////////////
long accelX;
long accelY;
long accelZ;
long gyroX;
long gyroY;
long gyroZ;

////////lidar//////////////////////////////////////
bool LidarOB; // ;Lidar Object
////////////////////////////////////////////////
/////////////booleans for movement //////////////
bool Bright;
bool Bleft;
bool Bforward;
bool Bbackward;
////////////////////////////////////////////////
bool throttleCheck;
uint16_t dist ;
uint16_t strength;

bool xpos;
bool xneg;
bool ypos;
bool yneg;
bool zpos;
bool zneg;

bool check_throttle;

long previousMillis = 0;
long interval = 1000;
unsigned long currentMillis = 0;

///////////////////////////////////////////////////////////////////////////////////
//1 = motor 1 (right front CCW).
//2 = motor 2 (right rear CW).
//3 = motor 3 (left rear CCW).
//4 = motor 4 (left front CW).
////////////////////////////////////////////////////////////////////////////////////
////Take off RPM about 1400 1450
//// MAX is 1800
///////////////////////////////////
int speed1 = 1000; //Creating a variable speed for each motor that makes the motors stop too
int speed2 = 1000;
int speed3 = 1000;
int speed4 = 1000; // was 1000
int fadeAmount = 2; // how many points to fade the m1 by
int throttle = 1200; // starting throttle amount
int land_throttle; //
int ultra_th = 1450; // ultrasonic landing or TO throttle

char blueToothVal;           //value sent over via bluetooth
char lastValue;             // last value of bluetooth

int rad_to_deg = 180 / 3.141592654; // rad to degrees

int PID_Activated = 0;  // variable for if the PID has been used
/////////////////////IMU and PID //////new///////////////////////////////////////////////////////////////////////////
//double x_kp = 0.01, x_ki = 0.005, x_kd = 0.2; //values for PID X axis
//int x_kp = 5, x_ki = 0, x_kd = 1; //values for PID X axis
int x_p_out, x_i_out, x_d_out, x_output; //outputs for PID
int x_now, x_lasttime = 0, x_timechange;
int x_input, x_lastinput = 0, x_setpoint = 0;
int x_error, x_errorsum = 0, x_d_error, x_lasterror;

int max_pid = 150;
//////////////////////////Axis PID//////////////to be found in PID CLASS
//double x_kp = 1, x_ki = 0.5, x_kd = 1; //values for PID X axis
//double y_kp = 1, y_ki = 0.5, y_kd = 1; //values for PID Y axis
//double z_kp = 1, z_ki = 0.0001, z_kd = 0.0001; //values for PID Z axis
////////////////////////////////////////////


//values = 5, 0.02, 1100 was just 1.25, 0.0005 and 1100
//int y_kp = 0.01, y_ki = 0.005, y_kd = 0.2; //values for PID Y axis
//int y_kp = 5, y_ki = 0, y_kd = 1; //values for PID Y axis
int y_p_out, y_i_out, y_d_out, y_output; //outputs for PID
int y_now, y_lasttime = 0, y_timechange;
int y_input, y_lastinput = 0, y_setpoint = 0;
int y_error, y_errorsum = 0, y_d_error, y_lasterror;
// prev values kp 2
//int z_kp = 5, z_ki = 0, z_kd = 0; //values for PID Z axis
int z_p_out, z_i_out, z_d_out, z_output; //outputs for PID
int z_now, z_lasttime = 0, z_timechange;
int z_input, z_lastinput = 0, z_setpoint = 0;
int z_error, z_errorsum = 0, z_d_error, z_lasterror;

int x_level_error = 0;
int y_level_error = 0;

int rotation[3];
int x_rotation, y_rotation, z_rotation;
//////////////////////////////////////////////////
int Gyr_rawX, Gyr_rawY, Gyr_rawZ, Gyro_raw_error_x, Gyro_raw_error_y, Gyro_raw_error_z, gyro_error; // GYRO EEROR CHECK
int Acc_rawX, Acc_rawY, Acc_rawZ, Acc_angle_error_x, Acc_angle_error_y, acc_error, Acc_angle_error_z; // ACC ERROR CHECK

int gyroX_raw; // gyro x axis raw data
int gyroY_raw;
int gyroZ_raw;

int timer_counter = 0; // time counter

int switchCase = 0; // making a switchcase and starting it at 0
int previousCase = 0;

uint32_t timer;

int main_power = 0;



/////////////////////////////////////////////////////////////////////////////////////////
// the setup routine runs once when you press reset:
void setup()
{

  Serial.begin(9600);// being in the Serial monitor with the Baudrate
  pinMode(13, OUTPUT);
  Serial1.begin(9600);// serial for bluetooth channel
  Serial2.begin(9600); // serial for Pi Pico
  Serial3.begin(TFMINI_BAUDRATE); // serial for LiDAR
  tfmini.begin(&Serial3); //initate the Lidar unit
  ///////////////////////////////////////////////////
  m1.attach(9); //Specify the esc signal pin,Here as D6 || m1 is front right
  m2.attach(8); // m2 is back right
  m3.attach(6); // m3 is back left
  m4.attach(5); // m4 is front left

  motors_stop();  // calling the motors stop where a they are sent 1000
  Wire.begin(); //begin i2c
  IMU_init(); // initialise the IMU
  gyro_error_check(); // checking the error rate on the gyro which is then applied to the IMU data
  gyro_error_check();
  acc_error_check(); // checking the error rate on the accel which is then applied to the IMU data
  acc_error_check();
  LiDARinit();
  previousCase = 0;
  delay(6000); //delay by 6 seconds to make sure the ESC know that 1000 is the stop signal

  // pinMode(GND0, OUTPUT); //define a digital pin as output
  // pinMode(GND1, OUTPUT);
  pinMode(GND2, OUTPUT);
  pinMode(GND3, OUTPUT);
  pinMode(GND4, OUTPUT); //define a digital pin as output
  pinMode(GND5, OUTPUT);
  pinMode(GND6, OUTPUT);
  pinMode(GND7, OUTPUT);
  // digitalWrite(GND0, LOW);// setting the pin to LOW to asct an an additional ground
  //digitalWrite(GND1, LOW);
  digitalWrite(GND2, LOW);
  digitalWrite(GND3, LOW);
  digitalWrite(GND4, LOW);// setting the pin to LOW to asct an an additional ground
  digitalWrite(GND5, LOW);
  digitalWrite(GND6, LOW);
  digitalWrite(GND7, LOW);
  Scheduler.startLoop(loop1); // run loop1 in the background
}

// the loop routine runs over and over again forever:
void loop() {

  if (Serial1.available()) { // check to see if the bluetooth is available
    blueToothVal = Serial1.read(); //read bluetooth
    Serial.println("Bluetooth Connected");
    Serial1.println("Bluetooth Connected");
  }
  /////////////////////////////////////////////////////////////////////////////////////////
  if (blueToothVal == 's')
  { //if value from bluetooth serial is n for normal mode
    digitalWrite(13, HIGH);
    autonomousMode_1();
    if (lastValue != 's') {
      Serial.println("Auto mode 1"); //print LED is on
      Serial1.println("Auto mode 1"); //print LED is on
    }
    lastValue = blueToothVal;
  }


  else if (blueToothVal == 'a')
  { //if value from bluetooth serial is n for normal mode
    digitalWrite(13, HIGH);
    autonomousMode_2();
    if (lastValue != 'a') {
      //Serial.println(F("Landing Safely")); //print LED is on
      Serial.println("Auto mode 2"); //print LED is on
      Serial1.println("Auto mode 2"); //print LED is on
    }
    lastValue = blueToothVal;
  }

  else if (blueToothVal == 'l')
  { //if value from bluetooth serial is n for normal mode
    digitalWrite(13, HIGH);
    Emergency_land();
    if (lastValue != 'l') {
      Serial.println("LANDING EMER"); //print LED is on
      Serial1.println("LANDING EMER"); //print LED is on
    }
    lastValue = blueToothVal;
  }
  else if (blueToothVal == 'o')
  { //if value from bluetooth serial is n for normal mode
    digitalWrite(13, HIGH);
    off();
    if (lastValue != 'o') {
      Serial.println("Turning off"); //print LED is on
      Serial1.println("Turning off"); //print LED is on
    }
    lastValue = blueToothVal;
  }

  else {
    //neutral_bal();
    //stabilize();
    digitalWrite(13, LOW);
    speed1 = 1100 ;
    speed2 = 1100 ;
    speed3 = 1100 ;
    speed4 = 1100 ;
    delay(50);
    throttle = 1200;
    ultra_th = 1450;
    currentMillis = 0;

  }
  delay(10);
  motors();
}
