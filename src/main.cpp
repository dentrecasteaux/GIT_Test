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
#ifndef LED_BUILTIN
  #define LED_BUILTIN 2  // ESP32 default GPIO
#endif

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
  
  // Wait for serial port to be ready (not needed on ESP32, but good practice)
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
    Serial.print(F("CPU Freq: "));
    Serial.print(ESP.getCpuFreqMHz());
    Serial.println(F(" MHz"));
    Serial.print(F("Free Heap: "));
    Serial.print(ESP.getFreeHeap());
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
    Serial.println(F(" bytes"));
  }
}
