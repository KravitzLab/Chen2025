// Write data header to file of uSD.
void writeHeader() {
  logfile = SD.open(filename, FILE_WRITE);
  logfile.println("Datetime,Seconds,Device_Number,Battery_Voltage,Prox1,Prox2,Event,DoorOpen,LeftTouch,RightTouch,LeftChange,RightChange");
  logfile.close();
}

// Print data and time followed by pellet count and motorturns to SD card
void logdata() {
  if (!SD.begin(chipSelect, SD_SCK_MHZ(4))) {
    Serial.println("Card failed, or not present");
    Serial.println("Continuing without logging...");
    return; // Don't call error(), just return
  }
  
  digitalWrite(13, HIGH);
  float timer = millis() / 1000.000;
  DateTime now = rtc.now();
  digitalWrite(13, LOW);
  // getFilename(filename);
  logfile = SD.open(filename, FILE_WRITE);
  
  if (!logfile) {
    Serial.println("Failed to open log file");
    Serial.println("Continuing without logging...");
    return; // Don't call error(), just return
  }
  
  logfile.print(now.month());
  logfile.print('/');
  logfile.print(now.day());
  logfile.print('/');
  logfile.print(now.year());
  logfile.print(" ");
  logfile.print(now.hour());
  logfile.print(':');
  logfile.print(now.minute());
  logfile.print(':');
  logfile.print(now.second());
  logfile.print(",");
  logfile.print(timer - new_trial, 3);  // Print time in seconds
  logfile.print(",");
  logfile.print(SOC);  // Print device name
  logfile.print(",");
  logfile.print(measuredvbat);
  logfile.print(",");
  logfile.print(Range1);  // Print range1
  logfile.print(",");
  logfile.print(Range2);  //print range2
  logfile.print(",");
  logfile.print(event);  //print event
  logfile.print(",");
  logfile.print(door);  //print door situation
  logfile.print(",");
  logfile.print(left_touch_active);
  logfile.print(",");
  logfile.print(right_touch_active);
  logfile.print(",");
  logfile.print(left_change);
  logfile.print(",");
  logfile.print(right_change);
  logfile.println();

  if (!logfile) {
    error();
  }
  logfile.close();

  //Fix data rate at 10hz
  while ((millis() - startreading) < 124) {
    delay(1);
  }
}

void writeConfigFile() {
  configfile = SD.open("DoorNumber.csv", FILE_WRITE);
  configfile.rewind();
  configfile.println(SOC);
  configfile.flush();
  configfile.close();
}