void WakeUp() {
  digitalWrite(13, HIGH);
}

void handleSleep() {
  if (millis() - screen_time > 20000) {
    //turn off the screen
    display.oled_command(SH110X_DISPLAYOFF);
    digitalWrite(13, LOW);

    //   //If we sleep we won't be sensitive to touches so we need to turn this off
    //   //LowPower.sleep(1000);
    // }
  }
}
