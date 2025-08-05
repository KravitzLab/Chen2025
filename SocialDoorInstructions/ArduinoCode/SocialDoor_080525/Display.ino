void update_display() {
  if (millis() - screen_time <= 20000) {
    //need to activate the screen first
    display.oled_command(SH110X_DISPLAYON);
    display.clearDisplay();
    ReadBatteryLevel();
    DisplayBattery();
    display.setCursor(21, 2);
    display.print(measuredvbat);
    display.setCursor(0, 13);
    DateTime nowprint = rtc.now();
    display.print(nowprint.year());
    display.print('-');
    display.print(nowprint.month());
    display.print('-');
    display.println(nowprint.day());
    // display.print(' ');
    display.print(nowprint.hour());
    display.print(':');
    display.println(nowprint.minute());
    display.setCursor(0, 30);
    display.print("Device# ");
    display.println(SOC);
    display.println();
    display.println("Sensor1");
    display.println(Range1);
    display.println();
    display.println("Sensor2");
    display.println(Range2);
    display.println();
    display.println("Openings");
    display.println(open_num);
    display.println();
    display.println((millis() - door_open) / 1000, 0);
    display.display();
  }
}

/********************************************************
  If any errors are detected with the SD card print on the screen
********************************************************/
void error() {
  digitalWrite(13, HIGH);
  display.clearDisplay();
  ReadBatteryLevel();
  DisplayBattery();
  display.setCursor(21, 2);
  display.print(measuredvbat);
  display.setCursor(0, 13);
  DateTime nowprint = rtc.now();
  display.print(nowprint.year());
  display.print('-');
  display.print(nowprint.month());
  display.print('-');
  display.println(nowprint.day());
  display.print(nowprint.hour());
  display.print(':');
  display.println(nowprint.minute());
  display.setCursor(0, 30);
  display.print("Device # ");
  display.println(SOC);
  display.println();
  display.println();
  display.println("Check Card");
  display.println();
  display.println("   Not");
  display.println(" Recording");
  display.display();
  if ((digitalRead(12) == HIGH) or (digitalRead(5) == LOW)) {
    open_door();
  }
  error();
  delay(100);
}