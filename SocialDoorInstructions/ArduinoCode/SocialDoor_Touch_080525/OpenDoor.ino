void open_door() {
  //Trigger the door with input on audio jack or button push
  //only open door if pulse is still high (Left poke should make a long pulse, Right poke makes a short pulse)
  // event++;
  read_sensors();
  digitalWrite(A1, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  int k = 0;
  open_the_door(k);

  door_wait_open();
  int j = 0;
  close_door();                                                 // v2: can have another close_door(); when pausing for a few seconds.                                                   //v2
  while ((door == 1 or door == -2 or door == 418) and j < 2) {  //v2
    delay(3000);                                                //v2
    close_door();                                              //v2
    j++;                                                        //v2
  }                                                             //v2
}

void open_the_door(int &k) {
  myservo.attach(A0);  // attaches the servo on pin A0 to the servo object
  myservo.write(104);  // tell servo to go to position in variable 'pos'
  //wait for door to open
  for (int i = 0; i < 4; i++) {
    read_sensors();
  }
  //read while door opening
  door_open = millis();
  unsigned long startopening = millis();
  digitalWrite(A1, LOW);
  int last_door_sensor_state = LOW;  // global or static variable
  if (digitalRead(A3) == LOW) {
    while (last_door_sensor_state == LOW) {
      read_sensors();
      int current_door_sensor_state = digitalRead(A3);

      // Detect rising edge
      if (last_door_sensor_state == LOW && current_door_sensor_state == HIGH) {
        // The door sensor changed from LOW to HIGH
        if (button == 0 or door == 1) {
          door = 1;
        } else if (button == -1 or door == -2) {
          door = -2;
        };  // or your appropriate handling
        break;
      }

      last_door_sensor_state = current_door_sensor_state;

      if (millis() - startopening > 6000) {
        door = 418;
        break;
      }
    }
  } else if (k < 2) {
    k++;
    delay(1000);
    open_the_door(k);
  }

  digitalWrite(10, LOW);
}

void door_wait_open() {
  //Stop
  myservo.write(90);
  myservo.detach();
  digitalWrite(11, LOW);

  //wait 12s for door to close
  unsigned long startTime = millis();
  while (millis() - startTime < TOUCH_TIMEOUT_DURATION) {
    read_sensors();  // Read sensors continuously
    // Optionally, add a short delay to prevent overwhelming the sensor readings
    delay(10);  // Delay 10 milliseconds to ease the loop
  }

  //leave the door open when the test mouse stays at the door
  while ((Range2 <= 50) and (millis() - startTime <= 60000)) {
    read_sensors();
  }

  //wait for ~1.3 second with Range2 < 50 before closing door
  for (int i = 0; i < 10; i++) {
    read_sensors();
    if ((Range2 <= 50) and (millis() - startTime <= 60000)) {
      i = 0;
    }
  }
}


void close_door() {
  //Close
  digitalWrite(11, HIGH);
  myservo.attach(A0);
  myservo.write(68);   // tell servo to go to position in variable 'pos'
  delay(300);          //version 2 - to alert the mouse
  myservo.write(103);  //v2
  delay(400);
  myservo.write(69);  //v2


  if (button == 0) {
    door = 0;
  } else if (button == -1) {
    door = -1;
  }

  //wait 0.5s for door to start closing
  for (int i = 0; i < 4; i++) {
    read_sensors();
  }

  unsigned long startclosing = millis();
  int last_door_sensor_state = LOW;  // global or static variable
  if (digitalRead(A3) == LOW) {
    while (last_door_sensor_state == LOW) {
      read_sensors();
      int current_door_sensor_state = digitalRead(A3);

      // Detect rising edge
      if (last_door_sensor_state == LOW && current_door_sensor_state == HIGH) {
        if (button == 0) {
          door = 0;
        } else if (button == -1) {
          door = -1;
        }
        break;
      }

      last_door_sensor_state = current_door_sensor_state;

      if (millis() - startclosing > 4500) {
        myservo.write(90);
        door = 418;
        break;
      }
    }
  } else {
    if (button == 0) {
      door = 1;
    } else if (button == -1) {
      door = -2;
    } else if (button == 414) {
      door = 0;
    }
    read_sensors();
  }

  myservo.write(90);  // tell servo to go to position in variable 'pos'
  myservo.detach();
  digitalWrite(11, LOW);
}

void open_door_startup() {
  digitalWrite(A1, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  myservo.attach(A0);  // attaches the servo on pin A0 to the servo object
  unsigned long startopening = millis();
  myservo.write(105);  // tell servo to go to position in variable 'pos'

  //wait 1s for door to start opening
  for (int i = 0; i < 10; i++) {
    delay(100);
  }

  digitalWrite(A1, LOW);

  //read while door opening
  while (digitalRead(A3) == LOW) {
    read_sensors();
    if (millis() - startopening > 5000) {
      break;
    }
  }

  digitalWrite(10, LOW);
}

void open_door_button() {
  // screen_time = millis();
  // door = -99;
  if (door == 0) {
    door = -1;
  }
  button = -1;  //5/17/24 moved here
  event++;
  new_trial = millis() / 1000.000;
  read_sensors();
  // update_display();  // For a press shorter than 1.2 s, screen will show up. Longer than 1.2 s, door will open.
  // delay(1000);
  // if (digitalRead(5) == LOW) {
  open_door();
  if (door == -1) {
    door = 0;
  }

  // }
  // door = 0;
}
