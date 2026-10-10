/**
 * @file main.cpp
 * @brief PSRAM Test with WS2812 RGB LED - handles missing PSRAM gracefully
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
    Serial.println("  ESP32-S3 Board Info + WS2812 RGB LED");
    Serial.println("========================================\n");
    
    // Initialize WS2812
    pixels.begin();
    pixels.show();
    
    Serial.println("WS2812 initialized on GPIO 48");
    
    // Get board info
    Serial.println("\n--- Board Information ---\n");
    
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    
    Serial.printf("Chip: ESP32-%s (revision %d)\n", 
        chip_info.model == CHIP_ESP32S3 ? "S3" : "Unknown",
        chip_info.revision);
    Serial.printf("Cores: %d\n", chip_info.cores);
    
    uint32_t flash_size = 0;
    esp_flash_get_size(NULL, &flash_size);
    Serial.printf("Flash: %d MB\n", flash_size / (1024 * 1024));
    
    // Check PSRAM
    Serial.println("\n--- PSRAM Status ---\n");
    
#if CONFIG_SPIRAM_SUPPORT
    if (psramFound()) {
        size_t psram_size = esp_spiram_get_size();
        Serial.printf("PSRAM: FOUND - %d MB\n", psram_size / (1024 * 1024));
        Serial.println("Status: ✅ PSRAM is available");
    } else {
        Serial.println("PSRAM: NOT FOUND");
        Serial.println("Status: ⚠️ PSRAM pin configured but not detected");
    }
#else
    Serial.println("PSRAM: DISABLED IN BUILD");
    Serial.println("Status: ⚠️ PSRAM support not compiled in");
#endif
    
    Serial.println("\n--- Starting LED cycle ---\n");
}

void loop() {
    // WS2812 color cycle - 3 blinks per color
    for (int i = 0; i < 3; i++) {
        pixels.setPixelColor(0, pixels.Color(255, 0, 0));  // Red
        pixels.show();
        delay(100);
        pixels.setPixelColor(0, pixels.Color(0, 0, 0));    // Off
        pixels.show();
        delay(100);
    }
    Serial.println("[LED] Red");
    
    for (int i = 0; i < 3; i++) {
        pixels.setPixelColor(0, pixels.Color(0, 255, 0));  // Green
        pixels.show();
        delay(100);
        pixels.setPixelColor(0, pixels.Color(0, 0, 0));    // Off
        pixels.show();
        delay(100);
    }
    Serial.println("[LED] Green");
    
    for (int i = 0; i < 3; i++) {
        pixels.setPixelColor(0, pixels.Color(0, 0, 255));  // Blue
        pixels.show();
        delay(100);
        pixels.setPixelColor(0, pixels.Color(0, 0, 0));    // Off
        pixels.show();
        delay(100);
    }
    Serial.println("[LED] Blue");
    
    // 2 second pause before repeating
    delay(1000);
}
