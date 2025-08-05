/*
 * Touch Sensor Troubleshooting Tool
 * ================================
 * 
 * This Arduino sketch provides a highly sensitive touch sensor monitoring system
 * using the Adafruit FreeTouch library. It's designed for troubleshooting and
 * testing capacitive touch sensors with maximum sensitivity.
 * 
 * Hardware Setup:
 * - Left sensor: Pin A1 (labeled "T1" on board)
 * - Right sensor: Pin A2 (labeled "T2" on board)
 * 
 * Features:
 * - Maximum sensitivity configuration (0K resistor, 64x oversampling)
 * - Automatic baseline tracking and adjustment
 * - Real-time change detection from baseline
 * - Compatible with Arduino Serial Monitor and Serial Plotter
 * - Rebaselines every minute to account for environmental changes
 * 
 * Output Formats:
 * - Serial Monitor: "Left: [change] Right: [change]"
 * - Serial Plotter: CSV format with left_change,right_change
 * 
 * Usage:
 * 1. Upload to Arduino board
 * 2. Open Serial Monitor (115200 baud) for text output
 * 3. Open Serial Plotter for real-time graphing
 * 4. Touch sensors to see changes from baseline
 * 
 * Baseline System:
 * - Automatically establishes baseline readings on startup
 * - Recalculates baseline every minute
 * - Uses 3-sample averaging for stable baseline
 * - Shows changes relative to baseline (positive = touch detected)
 * 
 * Sensitivity Settings:
 * - RESISTOR_0: Maximum sensitivity (can detect proximity)
 * - OVERSAMPLE_64: High signal-to-noise ratio
 * - FREQ_MODE_NONE: Standard frequency mode
 */

#include "Adafruit_FreeTouch.h"

// Maximum sensitivity configuration

//Left is on pin A1, named "T1" on the board
Adafruit_FreeTouch left = Adafruit_FreeTouch(A1, OVERSAMPLE_64, RESISTOR_0, FREQ_MODE_NONE);
//Right is on pin A2, named "T2" on the board
Adafruit_FreeTouch right = Adafruit_FreeTouch(A2, OVERSAMPLE_64, RESISTOR_0, FREQ_MODE_NONE);

// Baseline tracking variables
int left_baseline = 0;
int right_baseline = 0;
unsigned long last_baseline_update = 0;
const unsigned long BASELINE_INTERVAL = 60000; // 1 minute in milliseconds

void setup() {
  Serial.begin(115200);
  
  while (!Serial);
  Serial.println("FreeTouch test - Enhanced Sensitivity");
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  if (! left.begin())  
    Serial.println("Failed to begin left sensor on pin A1");
  if (! right.begin())  
    Serial.println("Failed to begin right sensor on pin A2");
    
  // Initialize baselines
  updateBaselines();
  Serial.println("Baselines initialized");

}

void loop() {
  int counter, result = 0;
  
  // Check if it's time to update baselines
  if (millis() - last_baseline_update >= BASELINE_INTERVAL) {
    updateBaselines();
  }
  
  // Clean output for Serial Monitor and Plotter
  counter = millis();
  result = left.measure(); 
  int left_change = result - left_baseline;
  
  counter = millis();
  result = right.measure(); 
  int right_change = result - right_baseline;
  
  // CSV format for Serial Plotter
  Serial.print(left_change);
  Serial.print(",");
  Serial.print(right_change);
  Serial.println();
  
  // Human readable for Serial Monitor
  Serial.print("Left: "); Serial.print(left_change);
  Serial.print(" Right: "); Serial.println(right_change);
  
  delay(100); // Reduced delay for more responsive readings
}

void updateBaselines() {
  // Take multiple readings and average them for stable baseline
  int left_sum = 0;
  int right_sum = 0;
  const int baseline_samples = 3;
  
  for (int i = 0; i < baseline_samples; i++) {
    left_sum += left.measure();
    right_sum += right.measure();
    delay(10);
  }
  
  left_baseline = left_sum / baseline_samples;
  right_baseline = right_sum / baseline_samples;
  last_baseline_update = millis();
  
  // Clean baseline update message
  Serial.println("--- Baseline Update ---");
  Serial.print("Left baseline: "); Serial.println(left_baseline);
  Serial.print("Right baseline: "); Serial.println(right_baseline);
  Serial.println("----------------------");
}