int startMove = 0;

/********************************************************************/
/******************** VLX Variables and Pins ************************/
/********************************************************************/
#include "Adafruit_VL53L0X.h"
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
#define LOX3_ADDRESS 0x32
#define SHT_LOX1 PA8
#define SHT_LOX2 PA10
#define SHT_LOX3 PA9
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;
VL53L0X_RangingMeasurementData_t measure3;

int leftVlx, centreVlx, rightVlx;
#define LOWER_LEFT_VLX_VALUE  30
#define UPPER_LEFT_VLX_VALUE  130

#define LOWER_RIGHT_VLX_VALUE  30
#define UPPER_RIGHT_VLX_VALUE  130

#define LOWER_FRONT_VLX_VALUE  10
#define UPPER_FRONT_VLX_VALUE  140

/********************************************************************/
/******************** MPU Variables and Pins ************************/
/********************************************************************/
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "MPU_biasing.hpp"
#define FILTER_DEFAULT MPU6050_BAND_21_HZ
Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;
Position P;
float time2;
float ax_avg = 0, ay_avg = 0, gz_avg = 0;


/***********************************************************/
/******************** Motors Pins  *************************/
/***********************************************************/
#define MR1 PA0
#define MR2 PC15
#define ML1 PC14
#define ML2 PC13
#define ENR PA2
#define ENL PA3

/*************************************************************************/
/******************** Encoders Variables and Pins  ***********************/
/*************************************************************************/
#define ENCA  PB9 // YELLOW
#define ENCB  PB8 // WHITE
#define ENCA1 PB0 // YELLOW
#define ENCB1 PB1 // WHITE
#define DistanceCM(x)  (((x-5)*398)/21)
int pos_l = 0;
int ReadingL;
int pos_r = 0;
int ReadingR;
int FirstStep = 1;

/*************************************************************************/
/**************************** PID Variables  *****************************/
/*************************************************************************/
#include <util/atomic.h> // For the ATOMIC_BLOCK macro
int spd = 60;
int error;
volatile int posi = 0; // specify posi as volatile: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
long prevT = 0;
float eprev = 0;
float eintegral = 0;
// PID
float kp = 0.9;
float ki = 0;
float kd = 0.01;

/******************************************************************************/
/******************** Algorithm Macros and Variables  *************************/
/******************************************************************************/
#define FORWARD_HEADING     0
#define RIGHT_HEADING       1
#define LEFT_HEADING        2
#define BACK_HEADING        3

#define MOST_LEFT           1
#define MOST_RIGHT          0

#define SHORTEST_PATH_ON     0
#define SHORTEST_PATH_OFF    1

#define DirectionSwitch     PA6 // if =1 .....most left //if =0 .....most right
#define StopMapping         PA5 // the 2ed push button at 0 creat the array ....at 1 make the shortest round (not completed )
char directions[100];
int pathSize = 0 ;      //IN MAIN CODE PUT IT 0

int x = 0;
int y = 0;
int robotHeading = FORWARD_HEADING;

/***********************************************************/
/***********************  Setup  ***************************/
/***********************************************************/
void setup()
{
  Serial.begin(9600);
  /***********************************************************/
  /******************** Switches Setup  **********************/
  /***********************************************************/
  pinMode(DirectionSwitch, INPUT_PULLUP);
  pinMode(StopMapping, INPUT_PULLUP);

  /***********************************************************/
  /******************** Motors Setup  ************************/
  /***********************************************************/
  pinMode( MR1 , OUTPUT);
  pinMode( MR2 , OUTPUT);
  pinMode( ML1 , OUTPUT);
  pinMode( ML2 , OUTPUT);
  pinMode( ENR , OUTPUT);
  pinMode( ENL , OUTPUT);

  /***********************************************************/
  /******************** Encoders Setup  **********************/
  /***********************************************************/
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  pinMode(ENCA1, INPUT);
  pinMode(ENCB1, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoderR, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCA1), readEncoderL, RISING);

  /***********************************************************/
  /****************       VLX Setup      *********************/
  /***********************************************************/
  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);
  pinMode(SHT_LOX3, OUTPUT);
  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  setID();

  /***********************************************************/
  /****************       MPU Setup      *********************/
  /***********************************************************/
  pinMode(PB6, INPUT_PULLUP);
  pinMode(PB7, INPUT_PULLUP);
  // Try to initialize!
  mpu.begin();
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);

  //getting the most accurate DC Value for the filter
  //setOffset();
}


/***********************************************************/
/***********************  MAIN  ***************************/
/***********************************************************/
void loop()
{
  //  stepNextCell();
  //  delay(1000);
  //  right_90();
  //  delay(1000);


  /*************************************************************************/
  /******************************** Testing ********************************/
  /*************************************************************************/
  //    testReadingVlx();
  //    testMotionWithVlx();
  //    testShortestPath();
  //    testAlgorithm();
  //    testSwitches();
  //    testTurn();

  /*************************************************************************/
  /****************************** Algorithm ********************************/
  /*************************************************************************/
  //  while (!(abs(x) == 1 && abs(y) == 4))
  while (((abs(x) != 5 && abs(y) != 5) && (abs(x) != 5 && abs(y) != 6) && (abs(x) != 6 && abs(y) != 5) && (abs(x) != 6 && abs(y) != 6)))
  {
    Creating_array ();
  }
  STOP();

  if (digitalRead(DirectionSwitch) == MOST_RIGHT)
  {
    SHORTEST_PATH_right();
  }
  else
  {
    SHORTEST_PATH_left();
  }

  while (digitalRead(StopMapping) == SHORTEST_PATH_OFF);
  delay(3000);

  Serial.println("Shortest Path is on");

  x = 0;
  y = 0;
  //  while (!(abs(x) == 1 && abs(y) == 4))
  while (((abs(x) != 5 && abs(y) != 5) && (abs(x) != 5 && abs(y) != 6) && (abs(x) != 6 && abs(y) != 5) && (abs(x) != 6 && abs(y) != 6)))
  {
    Second_trail();
  }
  STOP();
  delay(50000);

}
