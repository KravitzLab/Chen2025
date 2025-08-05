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
