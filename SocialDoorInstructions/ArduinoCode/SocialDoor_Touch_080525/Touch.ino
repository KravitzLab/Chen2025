/********************************************************
  Touch Sensor Functions
  Written by Lex Kravitz and Yiru Chen
  August 2025
********************************************************/

void checkTouches() {
  int result = 0;

  // Check if it's time to update baselines
  if (millis() - last_baseline_update >= BASELINE_INTERVAL) {
    updateBaselines();
  }

  result = left.measure();
  int left_change = result - left_baseline;
  
  result = right.measure();
  int right_change = result - right_baseline;
  
  // Human readable for Serial Monitor
  Serial.print("Left: "); Serial.print(left_change);
  Serial.print(" Right: "); Serial.println(right_change);

  // Touch duration logic for left sensor
  if (left_change > TOUCH_SENSITIVITY_THRESHOLD) {
    if (!left_touch_active) {
      // Touch just started
      left_touch_active = true;
      read_sensors();
      left_touch_start = millis();
    }
    // Check if touch has lasted long enough
    if (left_touch_active && (millis() - left_touch_start >= TOUCH_DURATION_THRESHOLD)) {
      Serial.println("Left pulse detected - open door");
      button = 0;
      event++;
      event_L++;
      left_touch_active = false; // Reset to prevent multiple triggers
      open_door();
    }
  } else {
    // Touch ended or below threshold
    if (left_touch_active) {
      left_touch_active = false;
    }
  }

  // Touch duration logic for right sensor
  if (right_change > TOUCH_SENSITIVITY_THRESHOLD) {
    if (!right_touch_active) {
      // Touch just started
      right_touch_active = true;
      read_sensors();
      right_touch_start = millis();
    }
    // Check if touch has lasted long enough
    if (right_touch_active && (millis() - right_touch_start >= TOUCH_DURATION_THRESHOLD)) {
      Serial.println("Right pulse detected - timeout");
      event++;
      event_R++;
      right_touch_active = false; // Reset to prevent multiple triggers
      Timeout(TOUCH_TIMEOUT_DURATION);
    }
  } else {
    // Touch ended or below threshold
    if (right_touch_active) {
      right_touch_active = false;
    }
  }
}
