#include <Wire.h>
#include <SPI.h>
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
#include "Adafruit_FreeTouch.h"

//Constants
int event = 0;
float screen_time = 0;
int condition = 0;
float door_open = 0;
int button = 0;
int event_L = 0;
int event_R = 0;
int left_change;
int right_change;

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

// FreeTouch sensors with maximum sensitivity configuration
// Left is on pin A1, named "T1" on the board
// Adafruit_FreeTouch left = Adafruit_FreeTouch(A1, OVERSAMPLE_64, RESISTOR_0, FREQ_MODE_NONE);
Adafruit_FreeTouch left = Adafruit_FreeTouch(A1, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_HOP);
// Right is on pin A2, named "T2" on the board
// Adafruit_FreeTouch right = Adafruit_FreeTouch(A2, OVERSAMPLE_64, RESISTOR_0, FREQ_MODE_NONE);
Adafruit_FreeTouch right = Adafruit_FreeTouch(A2, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_HOP);

// Baseline tracking variables
int left_baseline = 0;
int right_baseline = 0;
unsigned long last_baseline_update = 0;
const unsigned long BASELINE_INTERVAL = 60000; // Update baselines every 60 seconds

// Touch duration tracking variables
unsigned long left_touch_start = 0;
unsigned long right_touch_start = 0;
bool left_touch_active = false;
bool right_touch_active = false;
const unsigned long TOUCH_DURATION_THRESHOLD = 200; // Minimum touch duration in milliseconds

// Function declaration for baseline updates
void updateBaselines();
