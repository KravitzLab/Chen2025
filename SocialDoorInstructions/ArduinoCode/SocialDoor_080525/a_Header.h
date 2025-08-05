#include <Wire.h>
#include <SPI.h>
//#include <SD.h>
#include <Adafruit_VL6180X.h>
#include <Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "ArduinoLowPower.h"
#include <SdFat.h>
SdFat SD;  //Make SdFat work with standard SD.h sketches
#include <Adafruit_SH110X.h>
#include <splash.h>
#include "RTClib.h"
RTC_PCF8523 rtc;

//Constants
int open_num = 0;
float screen_time = 0;
int condition = 0;
float door_open = 0;
int button = 0;

//Screen
Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);

// New I2C address for a second VL6180
#define PROX1_ADDRESS 0x30

// set the pins to shutdown each sensor (needed to set I2C address on PROX1)
#define SHT_PROX2 A4

//variables
float Range1;
float Range2;
int SOC;        //This is the unique # of the device
char filename[30];  // make a "char" type variable called "filename" [13]
unsigned long startreading = millis();
float new_trial = millis() / 1000.000;
int event = 0;
int door = 0;

// objects for the VL6180X
Adafruit_VL6180X PROX1 = Adafruit_VL6180X();
Adafruit_VL6180X PROX2 = Adafruit_VL6180X();

//Setup servo
Servo myservo;  // create servo object to control a servo

/********************************************************
  Setup SD Card
********************************************************/
const int chipSelect = 4;
File logfile;     // Create file object
File configfile;  // Create another file object
