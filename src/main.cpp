/**
 * @file main.cpp
 * @brief ESP32-S3 with onboard LED detection and status reporting
 */

#include <Arduino.h>

// Based on common ESP32-S3 boards:
// - GPIO 46: Most DevKitC-1 boards (active-high)
// - GPIO 38: Some boards (active-low)  
// - GPIO 17/18: Other variants

const int LED_PIN = 46;  // Try the most common pin first
bool ledState = false;

void setup() {
    delay(100);
    
    Serial.begin(115200);
    while (!Serial && millis() < 2000) delay(10);
    
    Serial.println("\n========================================");
    Serial.println("  ESP32-S3 Board Test - PSRAM Disabled");
    Serial.println("========================================\n");
    
    // Initialize LED pin
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);  // Start with LED off (likely active-low)
    
    Serial.printf("LED configured on GPIO %d\n", LED_PIN);
    Serial.println("\nRunning 30-second test cycle...\n");
}

void loop() {
    static unsigned long lastBlink = 0;
    static int blinkCount = 0;
    
    // Blink LED every second to show we're alive
    if (millis() - lastBlink >= 1000) {
        lastBlink = millis();
        
        // Toggle LED - if it doesn't work, we'll know from serial
        digitalWrite(LED_PIN, ledState ? LOW : HIGH);
        ledState = !ledState;
        
        blinkCount++;
        
        if (blinkCount % 5 == 0) {
            Serial.printf("[HEARTBEAT] Blink #%d - LED on GPIO %d\n", blinkCount, LED_PIN);
        }
    }
    
    // Print system info every 10 seconds
    if (blinkCount % 10 == 0 && blinkCount > 0) {
        Serial.printf("[INFO] Free heap: %d bytes\n", esp_get_free_heap_size());
    }
}
