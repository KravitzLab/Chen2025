/*
 * Simple Timeout Function
 * =======================
 * 
 * Pauses execution for the specified duration in milliseconds.
 * Usage: Timeout(5000); // pauses for 5 seconds
 */

void Timeout(unsigned long duration_ms) {
  unsigned long startTime = millis();
  while (millis() - startTime < duration_ms) {
    read_sensors();  // Read sensors continuously - maintains 10Hz logging rate
    // read_sensors() handles its own timing (124ms minimum between calls)
    // This will result in approximately 10Hz logging during the timeout
  }
} 