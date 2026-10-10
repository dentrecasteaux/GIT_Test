/**
 * @file main.cpp
 * @brief WS2812 RGB LED test on ESP32-S3
 */

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// WS2812 is on GPIO 48
#define LED_PIN     48
#define LED_COUNT   1

Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
    delay(1000);
    
    Serial.begin(115200, SERIAL_8N1, -1, -1);
    
    unsigned long start = millis();
    while (!Serial && (millis() - start < 2000)) {
        delay(10);
    }
    
    Serial.println("\n========================================");
    Serial.println("  WS2812 RGB LED Test");
    Serial.println("========================================\n");
    
    pixels.begin();  // Initialize NeoPixel library
    pixels.show();   // Turn all LEDs off
    
    Serial.println("WS2812 initialized on GPIO 48");
}

void loop() {
    Serial.println("[LOOP] Cycle colors...");
    
    // Red
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    pixels.show();
    Serial.println("Red");
    delay(500);
    
    // Green
    pixels.setPixelColor(0, pixels.Color(0, 255, 0));
    pixels.show();
    Serial.println("Green");
    delay(500);
    
    // Blue
    pixels.setPixelColor(0, pixels.Color(0, 0, 255));
    pixels.show();
    Serial.println("Blue");
    delay(500);
    
    // White
    pixels.setPixelColor(0, pixels.Color(255, 255, 255));
    pixels.show();
    Serial.println("White");
    delay(500);
    
    // Off
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.show();
    Serial.println("Off");
    delay(500);
}
