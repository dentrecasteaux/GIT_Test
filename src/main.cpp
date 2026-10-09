/**
 * @file main.cpp
 * @brief Main entry point for embedded project
 * 
 * This is a starter template for PlatformIO + Arduino projects.
 * Edit this file and the board configuration in platformio.ini
 * to match your target hardware.
 */

#include <Arduino.h>

// ============================================================
// CONFIGURATION - Adjust for your hardware
// ============================================================

// LED pin - ESP32-S3 built-in LED is typically GPIO 48
// Some boards use GPIO 8 or 21 instead
#define LED_PIN 48

// Serial baud rate
#define BAUD_RATE 115200

// ============================================================
// HELPER FUNCTIONS
// ============================================================

/**
 * @brief Print a separator line to serial
 */
void printSeparator(const String& title = "") {
  Serial.println();
  if (!title.isEmpty()) {
    Serial.print("=== ");
    Serial.print(title);
    Serial.println(" ===");
  }
  Serial.println(F("----------------------------------------"));
}

// ============================================================
// SETUP
// ============================================================

void setup() {
  // Initialize serial communication FIRST (no delay)
  Serial.begin(BAUD_RATE);
  
  // Print immediately - if this doesn't show, the board is crashing
  Serial.println(F("HELLO"));
  Serial.println(F("Board is running"));
  
  // Configure LED pin
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);  // Most boards have active-low LEDs
}

// ============================================================
// LOOP
// ============================================================

void loop() {
  // Blink built-in LED
  digitalWrite(LED_PIN, LOW);   // Turn LED ON (active-low)
  delay(500);
  
  digitalWrite(LED_PIN, HIGH);  // Turn LED OFF
  delay(500);
}
