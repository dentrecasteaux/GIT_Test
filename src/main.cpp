/**
 * @file main.cpp
 * @brief Main entry point for embedded project
 * 
 * This is a starter template for PlatformIO + Arduino projects.
 * Edit this file and the board configuration in platformio.ini
 * to match your target hardware.
 */

#include <Arduino.h>

// ============================================================
// CONFIGURATION - Adjust for your hardware
// ============================================================

// LED pin - change to match your board
// ESP32-S3 DevKitC typically uses GPIO 48 for built-in LED
// The Arduino framework defines LED_BUILTIN for your board

// Serial baud rate
#define BAUD_RATE 115200

// ============================================================
// HELPER FUNCTIONS
// ============================================================

/**
 * @brief Print a separator line to serial
 */
void printSeparator(const String& title = "") {
  Serial.println();
  if (!title.isEmpty()) {
    Serial.print("=== ");
    Serial.print(title);
    Serial.println(" ===");
  }
  Serial.println(F("----------------------------------------"));
}

// ============================================================
// SETUP
// ============================================================

void setup() {
  // Initialize serial communication
  Serial.begin(BAUD_RATE);
  
  // Wait for serial port to be ready
  while (!Serial && millis() < 5000) {
    // Wait for serial port initialization
  }

  printSeparator("System Startup");
  
  // Print system info
  Serial.print(F("Uptime: "));
  Serial.print(millis());
  Serial.println(F(" ms"));
  
  #ifdef ESP32
    Serial.print(F("Chip Model: "));
    Serial.println(ESP.getChipModel());
    Serial.print(F("Chip Revision: "));
    Serial.println(ESP.getChipRevision());
    Serial.print(F("CPU Freq: "));
    Serial.print(ESP.getCpuFreqMHz());
    Serial.println(F(" MHz"));
    Serial.print(F("Flash Size: "));
    Serial.print(ESP.getFlashChipSize() / 1024 / 1024);
    Serial.println(F(" MB"));
    Serial.print(F("PSRAM Size: "));
    Serial.print(ESP.getPsramSize() / 1024 / 1024);
    Serial.println(F(" MB"));
    Serial.print(F("Free Heap: "));
    Serial.print(ESP.getFreeHeap());
    Serial.println(F(" bytes"));
    Serial.print(F("Free PSRAM: "));
    Serial.print(ESP.getFreePsram());
    Serial.println(F(" bytes"));
  #endif

  // Configure LED pin
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);  // Most boards have active-low LEDs
  
  printSeparator("Setup Complete");
}

// ============================================================
// LOOP
// ============================================================

void loop() {
  // Blink built-in LED
  digitalWrite(LED_BUILTIN, LOW);   // Turn LED ON (active-low)
  Serial.println(F("LED ON"));
  delay(500);
  
  digitalWrite(LED_BUILTIN, HIGH);  // Turn LED OFF
  Serial.println(F("LED OFF"));
  delay(500);
  
  // Print uptime periodically
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint >= 5000) {
    lastPrint = millis();
    printSeparator("Heartbeat");
    Serial.print(F("Uptime: "));
    Serial.print(millis() / 1000);
    Serial.print(F("s | "));
    Serial.print(F("Free Heap: "));
    #ifdef ESP32
      Serial.print(ESP.getFreeHeap());
    #else
      Serial.print(freeMemory());
    #endif
    Serial.print(F(" | "));
    Serial.print(F("Free PSRAM: "));
    #ifdef ESP32
      Serial.print(ESP.getFreePsram());
    #else
      Serial.print(0);
    #endif
    Serial.println(F(" bytes"));
  }
}
