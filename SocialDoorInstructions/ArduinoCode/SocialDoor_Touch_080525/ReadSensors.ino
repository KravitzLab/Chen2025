void read_sensors() {
  // This function takes ~135ms to complete! (timed empirically)
  startreading = millis();
  //Read PROX1

  uint8_t range = PROX1.readRange();
  uint8_t status = PROX1.readRangeStatus();
  if (status == VL6180X_ERROR_NONE) {
    Range1 = range;
  } else {
    Range1 = 200;
  }

  //Read PROX2
  range = PROX2.readRange();
  status = PROX2.readRangeStatus();
  if (status == VL6180X_ERROR_NONE) {
    Range2 = range;
  } else {
    Range2 = 200;
  }

  update_display();
  logdata();
  if (digitalRead(5) == LOW) {
    screen_time = millis();
    // update_display();
  }
}

void updateBaselines() {
  // Update the baseline values for touch sensors
  // This function should be called periodically to maintain accurate baseline readings
  
  // Take multiple readings and average them for more stable baselines
  int left_sum = 0;
  int right_sum = 0;
  const int num_readings = 10;
  
  for (int i = 0; i < num_readings; i++) {
    left_sum += left.measure();
    right_sum += right.measure();
    delay(10); // Small delay between readings
  }
  
  left_baseline = left_sum / num_readings;
  right_baseline = right_sum / num_readings;
  
  // Update the timestamp
  last_baseline_update = millis();
  
  // Optional: Log baseline updates
  Serial.print("Baselines updated - Left: ");
  Serial.print(left_baseline);
  Serial.print(", Right: ");
  Serial.println(right_baseline);
}
