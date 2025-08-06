/********************************************************
  Button Functions
  Written by Lex Kravitz and Yiru Chen
  August 2025
********************************************************/

void checkButtons() {
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
}
