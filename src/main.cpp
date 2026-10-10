/**
 * @file main.cpp
 * @brief ESP32-S3 Chip Diagnostic with PSRAM disabled
 */

#include <Arduino.h>

extern "C" {
    #include "esp_chip_info.h"
    #include "esp_err.h"
    #include "esp_flash.h"
}

void setup() {
    // Initialize serial at 115200 baud
    Serial.begin(115200);
    
    // Wait for serial monitor to open
    while (!Serial) {
        delay(100);
    }
    
    Serial.println("\n========================================");
    Serial.println("  ESP32-S3 Chip Diagnostic Report");
    Serial.println("========================================\n");

    // Get chip information
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);

    Serial.println("Chip Information:");
    Serial.printf("  Chip Model: ESP32-%s\n", 
        chip_info.model == CHIP_ESP32S3 ? "S3" : 
        chip_info.model == CHIP_ESP32S2 ? "S2" :
        chip_info.model == CHIP_ESP32C3 ? "C3" :
        chip_info.model == CHIP_ESP32    ? "ESP32" : "Unknown");
    
    Serial.printf("  CPU Cores: %d\n", chip_info.cores);
    Serial.printf("  Revision: %d\n", chip_info.revision);
    Serial.printf("  Features: ");
    if (chip_info.features & CHIP_FEATURE_WIFI_BGN) Serial.print("WiFi/BG ");
    if (chip_info.features & CHIP_FEATURE_BLE) Serial.print("BLE ");
    if (chip_info.features & CHIP_FEATURE_BT) Serial.print("BT ");
    Serial.println();

    // Get flash characteristics using esp_flash API
    uint32_t flash_size = 0;
    esp_flash_get_size(NULL, &flash_size);
    
    Serial.printf("  Flash Size: %d KB (%d MB)\n", flash_size / 1024, flash_size / (1024 * 1024));

    // Check PSRAM availability
    Serial.println("\nPSRAM Status:");
    
    if (psramFound()) {
        size_t psram_size = esp_spiram_get_size();
        Serial.printf("  PSRAM Size: %d KB (%d MB)\n", psram_size / 1024, psram_size / (1024 * 1024));
    } else {
        Serial.println("  PSRAM: Not detected (disabled or not available)");
    }

    // Read unique chip ID
    uint64_t chip_id = ESP.getEfuseMac();
    Serial.println("\nUnique Chip ID:");
    Serial.printf("  %016llx\n", chip_id);

    // Read flash information
    Serial.println("\nFlash Info:");
    uint32_t flash_size_esp = ESP.getFlashChipSize();
    Serial.printf("  Flash Size: %d KB (%d MB)\n", flash_size_esp / 1024, flash_size_esp / (1024 * 1024));
    Serial.printf("  Flash Frequency: %d MHz\n", ESP.getFlashChipSpeed() / 1000000);

    // Board information
    Serial.println("\nBuild Configuration:");
    Serial.printf("  Core SDK Version: %s\n", ESP.getSdkVersion());
    
#if CONFIG_ESP32_S3_REV0_DEFAULT
    Serial.println("  Revision: ESP32-S3 REV0");
#elif CONFIG_ESP32_S3_REV1_DEFAULT
    Serial.println("  Revision: ESP32-S3 REV1");
#elif CONFIG_ESP32_S3_REV2_DEFAULT
    Serial.println("  Revision: ESP32-S3 REV2");
#else
    Serial.println("  Revision: Unknown/Custom");
#endif

#if CONFIG_ESP32_DEFAULT_CPU_FREQ_MHZ == 240
    Serial.println("  CPU Frequency: 240 MHz (default)");
#elif CONFIG_ESP32_DEFAULT_CPU_FREQ_MHZ == 160
    Serial.println("  CPU Frequency: 160 MHz (default)");
#elif CONFIG_ESP32_DEFAULT_CPU_FREQ_MHZ == 80
    Serial.println("  CPU Frequency: 80 MHz (default)");
#endif

#if CONFIG_ESP32_SPIRAM_SUPPORT
    Serial.println("  SPIRAM Support: Enabled in build");
#else
    Serial.println("  SPIRAM Support: Disabled in build");
#endif

#if CONFIG_SPIRAM_IGNORE_NOTFOUND
    Serial.println("  SPIRAM Ignore Not Found: Yes");
#endif

    // Get free heap
    Serial.println("\nMemory Status:");
    Serial.printf("  Free Heap: %d bytes\n", esp_get_free_heap_size());
    Serial.printf("  Minimal Free Heap: %d bytes\n", esp_get_minimum_free_heap_size());

    Serial.println("\n========================================");
    Serial.println("  Diagnostic Complete");
    Serial.println("========================================\n");

    // Blink LED on board (GPIO 46 for most ESP32-S3 boards)
    const int LED_PIN = 46;
    pinMode(LED_PIN, OUTPUT);
    
    Serial.println("Testing LED blink (GPIO 46)...");
    
    int count = 0;
    while (count < 10) {
        digitalWrite(LED_PIN, HIGH);
        Serial.printf("  LED ON - Count: %d\n", count + 1);
        delay(500);
        digitalWrite(LED_PIN, LOW);
        Serial.printf("  LED OFF - Count: %d\n", count + 1);
        delay(500);
        count++;
    }
    
    Serial.println("\nDiagnostic sketch complete!");
}

void loop() {
    // Diagnostic complete - just blink slowly
    const int LED_PIN = 46;
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    delay(3000);
}
