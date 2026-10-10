/**
 * @file main.cpp
 * @brief Simple LED blink without serial - just for testing
 */

#include <Arduino.h>

const int LED_PIN = 48;

void setup() {
    // Just set up the pin - no serial
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    digitalWrite(LED_PIN, LOW);   // ON
    delay(100);
    digitalWrite(LED_PIN, HIGH);  // OFF
    delay(100);
    
    delay(400);  // Total cycle: 500ms
}
