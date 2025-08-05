#define BLACK 0  // Assuming 0 is used for black/off pixels
#define WHITE 1  // Assuming 1 is used for white/on pixels

void DisplayBattery() {
  //  Battery graphic showing bars indicating voltage levels

  //4 bars
  if (measuredvbat > 4.) {
    display.drawRect(0, 0, 19, 10, WHITE);
    display.fillRect(2, 2, 3, 6, WHITE);
    display.fillRect(6, 2, 3, 6, WHITE);
    display.fillRect(10, 2, 3, 6, WHITE);
    display.fillRect(14, 2, 3, 6, WHITE);
  }
  //3 bars
  if (measuredvbat > 3.85) {
    display.drawRect(0, 0, 19, 10, WHITE);
    display.fillRect(2, 2, 3, 6, WHITE);
    display.fillRect(6, 2, 3, 6, WHITE);
    display.fillRect(10, 2, 3, 6, WHITE);
  }

  //2 bars
  else if (measuredvbat > 3.7) {
    display.drawRect(0, 0, 19, 10, WHITE);
    display.fillRect(2, 2, 3, 6, WHITE);
    display.fillRect(6, 2, 3, 6, WHITE);
  }

  //1 bar
  else if (measuredvbat >= 3.6) {
    display.drawRect(0, 0, 19, 10, WHITE);
    display.fillRect(2, 2, 3, 6, WHITE);
  }

  //0 bars
  else if (measuredvbat < 3.6) {
    display.drawRect(0, 0, 19, 10, WHITE);
  }
}
