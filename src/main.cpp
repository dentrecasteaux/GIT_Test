/**
 * @file main.cpp
 * @brief Simple ESP32-S3 Boot Test with PSRAM disabled
 */

#include <Arduino.h>

void setup() {
    // Add small delay before any initialization to avoid reset loop
    delay(100);
    
    // Initialize serial at 115200 baud
    Serial.begin(115200);
    
    // Wait for serial to be ready - use timeout to avoid hanging
    unsigned long start = millis();
    while (!Serial && (millis() - start < 2000)) {
        delay(10);
    }
    
    Serial.println("\n[BOOT] Starting up...");
    Serial.println("[BOOT] Serial initialized");

    // Simple LED test
    const int LED_PIN = 46;
    pinMode(LED_PIN, OUTPUT);
    
    Serial.println("[BOOT] LED pin configured (GPIO 46)");
    
    // Blink LED a few times to show we're alive
    for (int i = 0; i < 5; i++) {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("[BOOT] LED ON");
        delay(100);
        digitalWrite(LED_PIN, LOW);
        Serial.println("[BOOT] LED OFF");
        delay(100);
    }
    
    Serial.println("\n[BOOT] Setup complete - entering loop");
}

void loop() {
    const int LED_PIN = 46;
    
    digitalWrite(LED_PIN, HIGH);
    Serial.println("[LOOP] LED ON");
    delay(1000);
    
    digitalWrite(LED_PIN, LOW);
    Serial.println("[LOOP] LED OFF");
    delay(1000);
}
