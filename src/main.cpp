/**
 * @file main.cpp
 * @brief PSRAM Test with WS2812 RGB LED on ESP32-S3 N16R8
 */

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// WS2812 is on GPIO 48
#define LED_PIN     48
#define LED_COUNT   1

Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// PSRAM test
size_t psram_size = 0;
bool psram_works = false;

void setup() {
    delay(100);
    
    Serial.begin(115200, SERIAL_8N1, -1, -1);
    
    unsigned long start = millis();
    while (!Serial && (millis() - start < 2000)) {
        delay(10);
    }
    
    Serial.println("\n========================================");
    Serial.println("  ESP32-S3 N16R8 PSRAM Test + WS2812");
    Serial.println("========================================\n");
    
    // Initialize WS2812
    pixels.begin();
    pixels.show();
    
    Serial.println("WS2812 initialized on GPIO 48");
    
    // Test PSRAM
    Serial.println("\n--- PSRAM Test ---\n");
    
    if (psramFound()) {
        psram_size = esp_spiram_get_size();
        Serial.printf("PSRAM Found: %d bytes (%.2f MB)\n", 
            psram_size, psram_size / (1024.0 * 1024.0));
        
        // Test read/write
        uint32_t* psram_ptr = (uint32_t*)ps_malloc(4096);
        if (psram_ptr) {
            Serial.println("PSRAM allocation: SUCCESS");
            
            // Write test pattern
            for (int i = 0; i < 1024; i++) {
                psram_ptr[i] = 0xDeadBeef | (i << 8);
            }
            
            // Verify
            bool verify_ok = true;
            for (int i = 0; i < 1024; i++) {
                if (psram_ptr[i] != (0xDeadBeef | (i << 8))) {
                    verify_ok = false;
                    break;
                }
            }
            
            if (verify_ok) {
                Serial.println("PSRAM verify: SUCCESS - PSRAM working!");
                psram_works = true;
            } else {
                Serial.println("PSRAM verify: FAILED");
            }
            
            free(psram_ptr);
        } else {
            Serial.println("PSRAM allocation: FAILED - no memory available");
        }
    } else {
        Serial.println("PSRAM not found or not initialized");
        Serial.println("Check board configuration for N16R8 variant");
    }
    
    Serial.println("\n--- Starting LED cycle ---\n");
}

void loop() {
    // WS2812 color cycle
    for (int i = 0; i < 3; i++) {
        pixels.setPixelColor(0, pixels.Color(255, 0, 0));
        pixels.show();
        delay(100);
        pixels.setPixelColor(0, 0);
        pixels.show();
        delay(100);
    }
    Serial.println("[LED] Red");
    
    for (int i = 0; i < 3; i++) {
        pixels.setPixelColor(0, pixels.Color(0, 255, 0));
        pixels.show();
        delay(100);
        pixels.setPixelColor(0, 0);
        pixels.show();
        delay(100);
    }
    Serial.println("[LED] Green");
    
    for (int i = 0; i < 3; i++) {
        pixels.setPixelColor(0, pixels.Color(0, 0, 255));
        pixels.show();
        delay(100);
        pixels.setPixelColor(0, 0);
        pixels.show();
        delay(100);
    }
    Serial.println("[LED] Blue");
    
    // Show PSRAM status with white
    if (psram_works) {
        pixels.setPixelColor(0, pixels.Color(255, 255, 255));
        pixels.show();
        Serial.println("[LED] White - PSRAM Active!");
    } else {
        pixels.setPixelColor(0, pixels.Color(100, 100, 100));
        pixels.show();
        Serial.println("[LED] Dim - No PSRAM");
    }
    
    delay(2000);
}
