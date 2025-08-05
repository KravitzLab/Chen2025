/********************************************************
  Social Door v1.0
  Written by Lex Kravitz and Yiru Chen
  March 2024

  This project is released under the terms of the Creative Commons - Attribution - ShareAlike 3.0 license:
  human readable: https://creativecommons.org/licenses/by-sa/3.0/
  legal wording: https://creativecommons.org/licenses/by-sa/3.0/legalcode
  Copyright (c) 2024 Lex Kravitz
  ********************************************************/

#include "a_Header.h"  //See "a_Header.h" for #defines and other constants

void setup() {
  StartUpCommands();
}

void loop() {
  int counter, result = 0;

  // Check if it's time to update baselines
  if (millis() - last_baseline_update >= BASELINE_INTERVAL) {
    updateBaselines();
  }

  result = left.measure();
  int left_change = result - left_baseline;
  Serial.print("Left sensor: ");
  Serial.print(result);
  Serial.print(", baseline: ");
  Serial.print(left_baseline);
  Serial.print(", change: ");
  Serial.println(left_change);
  
  result = right.measure();
  int right_change = result - right_baseline;
  Serial.print("Right sensor: ");
  Serial.print(result);
  Serial.print(", baseline: ");
  Serial.print(right_baseline);
  Serial.print(", change: ");
  Serial.println(right_change);

  // Touch duration logic for left sensor
  if (left_change > 25) {
    if (!left_touch_active) {
      // Touch just started
      left_touch_active = true;
      left_touch_start = millis();
      Serial.println("Left touch started");
    }
    // Check if touch has lasted long enough
    if (left_touch_active && (millis() - left_touch_start >= TOUCH_DURATION_THRESHOLD)) {
      Serial.println("Left pulse detected - open door");
      button = 0;
      open_num++;
      open_door();
      left_touch_active = false; // Reset to prevent multiple triggers
    }
  } else {
    // Touch ended or below threshold
    if (left_touch_active) {
      Serial.println("Left touch ended");
      left_touch_active = false;
    }
  }

  // Touch duration logic for right sensor
  if (right_change > 25) {
    if (!right_touch_active) {
      // Touch just started
      right_touch_active = true;
      right_touch_start = millis();
      Serial.println("Right touch started");
    }
    // Check if touch has lasted long enough
    if (right_touch_active && (millis() - right_touch_start >= TOUCH_DURATION_THRESHOLD)) {
      Serial.println("Right pulse detected - no door");
      Timeout(5000);
      right_touch_active = false; // Reset to prevent multiple triggers
    }
  } else {
    // Touch ended or below threshold
    if (right_touch_active) {
      Serial.println("Right touch ended");
      right_touch_active = false;
    }
  }

  // When button is pushed
  if (digitalRead(6) == LOW) {
    open_door_button();
  }

  if (digitalRead(5) == LOW) {
    screen_time = millis();
    int origin_door = door;
    door = -99;
    read_sensors();
    update_display();
    door = origin_door;
  }

  if (millis() - screen_time > 20000) {
    //turn off the screen
    display.oled_command(SH110X_DISPLAYOFF);
    digitalWrite(13, LOW);

    //   //If we sleep we won't be sensitive to touches so we need to turn this off
    //   //LowPower.sleep(1000);
    // }
  }
  delay(100);
}
