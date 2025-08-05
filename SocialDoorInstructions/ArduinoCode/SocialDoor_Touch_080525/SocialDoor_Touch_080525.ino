/********************************************************
  Social Door v1.0
  Written by Lex Kravitz and Yiru Chen
  March 2024

  Events:
  1) Pulse detected
  2) Start door opening
  3) Door opened
  4) Start door closing
  5) Door closed

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
  // When input pulse is received
  if (digitalRead(12) == HIGH) {
    button = 0;
    open_num++;
    open_door();
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
    LowPower.sleep(1000);
  }
}
