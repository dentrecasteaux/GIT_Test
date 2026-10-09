/**
 * @file main.cpp
 * @brief Minimal blink test - no Serial, no PSRAM, no config
 */

#include <Arduino.h>

void setup() {
  // Configure LED pin
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);  // Start with LED off
}

void loop() {
  // Blink built-in LED
  digitalWrite(LED_BUILTIN, LOW);   // Turn LED ON (active-low)
  delay(500);
  
  digitalWrite(LED_BUILTIN, HIGH);  // Turn LED OFF
  delay(500);
}
