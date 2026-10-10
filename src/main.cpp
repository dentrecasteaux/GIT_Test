/**
 * @file main.cpp
 * @brief Minimal blink test with Serial output
 */

#include <Arduino.h>

void setup() {
  // Initialize serial FIRST
  Serial.begin(115200);
  
  // Wait for serial to be ready
  delay(100);
  
  Serial.println();
  Serial.println("=== System Startup ===");
  Serial.println("Board is running");
  
  // Configure LED pin
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);  // Start with LED off
}

void loop() {
  // Blink built-in LED
  digitalWrite(LED_BUILTIN, LOW);   // Turn LED ON (active-low)
  Serial.println("LED ON");
  delay(500);
  
  digitalWrite(LED_BUILTIN, HIGH);  // Turn LED OFF
  Serial.println("LED OFF");
  delay(500);
}
