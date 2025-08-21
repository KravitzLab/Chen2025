/********************************************************
  Social Door v1.1 TOUCH - Arduino Control System
  ===============================================
  
  A sophisticated door control system for behavioral research applications,
  featuring touch sensors, proximity detection, and comprehensive data logging.
  
  HARDWARE COMPONENTS:
  - Arduino-compatible microcontroller
  - Adafruit SH1107 OLED display (64x128)
  - Two VL6180X proximity sensors
  - Two Adafruit FreeTouch capacitive touch sensors
  - Servo motor for door actuation
  - SD card for data logging
  - RTC PCF8523 real-time clock
  - Battery monitoring system
  
  KEY FEATURES:
  - Touch-sensitive door activation
  - Proximity-based door control
  - Real-time data logging to SD card
  - Battery level monitoring and display
  - Configurable device numbering
  - Sleep mode for power conservation
  - Comprehensive error handling
  
  DATA LOGGING:
  Records timestamp, device number, battery voltage, proximity readings,
  event counter, door status, and touch sensor states at 10Hz.
  
  TOUCH SENSOR CONFIGURATION:
  - Left touch sensor: Pin A1 (T1 on board)
  - Right touch sensor: Pin A2 (T2 on board)
  - Sensitivity: Maximum (OVERSAMPLE_64, RESISTOR_0)
  - Minimum touch duration: 200ms
  
  PROXIMITY SENSORS:
  - PROX1: I2C address 0x30
  - PROX2: I2C address 0x29 (default)
  - Range detection for door control and animal presence
  
  AUTHORS:
  - Lex Kravitz (Principal Investigator)
  - Yiru Chen (Developer)
  
  VERSION: 1.1 TOUCH
  DATE: August 2025
  
  LICENSE:
  This project is released under the terms of the Creative Commons - 
  Attribution - ShareAlike 3.0 license:
  Human readable: https://creativecommons.org/licenses/by-sa/3.0/
  Legal wording: https://creativecommons.org/licenses/by-sa/3.0/legalcode
  
  Copyright (c) 2024 Lex Kravitz
  
  USAGE:
  - Upload to Arduino-compatible board
  - Ensure SD card is properly formatted and inserted
  - Configure device number via SetDeviceNum.ino
  - System will automatically start logging data
  - Touch sensors or proximity detection will trigger door operations
  
  ********************************************************/

#include "a_Header.h"  //See "a_Header.h" for #defines and other constants

// Touch sensitivity threshold
const int TOUCH_SENSITIVITY_THRESHOLD = 3;

// Timeout duration for touch sensors (in milliseconds)
const unsigned long TOUCH_TIMEOUT_DURATION = 15000;

void setup() {
  StartUpCommands();
}

void loop() {
  checkTouches();
  checkButtons();
  handleSleep();
  delay(100);
}