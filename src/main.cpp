/**
 * @file main.cpp
 * @brief ESP32-S3 LED on GPIO 48 with Serial output
 */

#include <Arduino.h>

// Using GPIO 48 as requested by user
const int LED_PIN = 48;

void setup() {
    // Wait for USB serial to be ready - critical for ESP32-S3
    delay(1000);
    
    Serial.begin(115200, SERIAL_8N1, -1, -1);
    
    // Wait for serial port to be ready
    unsigned long start = millis();
    while (!Serial && (millis() - start < 2000)) {
        delay(10);
    }
    
    Serial.println("\n[START] ESP32-S3 LED Test - GPIO 48");
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    Serial.println("[LOOP] Blinking GPIO 48");
    
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
    delay(500);
    digitalWrite(LED_PIN, HIGH);
    
    Serial.println("[LOOP] Done blinking");
    delay(500);
}
