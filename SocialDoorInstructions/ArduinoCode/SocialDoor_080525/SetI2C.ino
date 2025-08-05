void setI2C() {
  // Reset both VL6180s
  Serial.println("Setting Sensor 1 address");
  digitalWrite(SHT_PROX2, LOW);
  delay(10);

  // Initialize PROX1 and set new I2C address
  PROX1.begin();
  PROX1.setAddress(PROX1_ADDRESS);
  delay(10);

  //Initialize PROX2 (no need to change address from 0x29)
  Serial.println("Setting Sensor 2 address");
  digitalWrite(SHT_PROX2, HIGH);
  PROX2.begin();
  delay(10);
}
