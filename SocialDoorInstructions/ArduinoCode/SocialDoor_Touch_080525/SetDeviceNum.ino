void set_device_num() {
  // create files if they dont exist and grab device name and ratio
  configfile = SD.open("DoorNumber.csv", FILE_WRITE);
  configfile = SD.open("DoorNumber.csv", FILE_READ);
  SOC = configfile.parseInt();
  configfile.close();

  unsigned long functiontime = millis();
  while (millis() - functiontime < 4000) {
    display.clearDisplay();
    display.display();
    delay(100);

    ReadBatteryLevel();
    DisplayBattery();
    display.setCursor(21, 2);
    display.print(measuredvbat);
    display.setCursor(0, 15);
    display.println("Device #");
    display.println(SOC);
    display.display();
    delay(200);

    if (digitalRead(6) == LOW) {
      SOC++;
      delay(250);
      functiontime = millis();
      if (SOC > 99) {
        SOC = 0;
      }
    }

    if (digitalRead(5) == LOW) {
      SOC--;
      delay(250);
      functiontime = millis();
      if (SOC < 0) {
        SOC = 99;
      }
    }
  }
  writeConfigFile();
}