# GIT_Test

Embedded firmware project using **PlatformIO** + **Arduino** framework.

## Quick Start

### 1. Install PlatformIO Core

```bash
pip3 install platformio
```

Or use the PlatformIO IDE extension in VS Code (recommended for beginners).

### 2. Configure Your Board

Edit `platformio.ini` and uncomment the `[env:...]` section for your target hardware:

| Board | Section | Platform |
|-------|---------|----------|
| ESP32 DevKit | `[env:esp32dev]` | `espressif32` |
| ESP32-S3 | `[env:esp32-s3-devkitc-1]` | `espressif32` |
| ESP32-C3 | `[env:esp32-c3-devkitm-1]` | `espressif32` |
| Teensy 4.1 | `[env:teensy41]` | `teensy` |
| Teensy 4.0 | `[env:teensy40]` | `teensy` |
| nRF52840 DK | `[env:nrf52840dk]` | `nordicnrf52` |
| Arduino Uno | `[env:uno]` | `atmelavr` |

### 3. Common Commands

```bash
# Build the project
pio run

# Build for a specific environment
pio run -e esp32dev

# Upload firmware
pio run --target upload

# Upload and monitor serial
pio run --target upload && pio device monitor

# Clean build artifacts
pio run --target clean

# Update PlatformIO
pio upgrade --upgrade
```

## Project Structure

```
GIT_Test/
├── platformio.ini      # PlatformIO configuration
├── src/
│   └── main.cpp        # Main application code
├── include/            # Header files
├── lib/                # Local libraries
├── test/               # Unit tests
├── data/               # Static data files (SPIFFS/LittleFS)
├── scripts/            # Build/automation scripts
└── .gitignore          # Git ignore rules
```

## Multi-Machine Workflow

This project is designed to work across multiple machines:

1. **Share via Git/GitHub** — commit and push changes from either machine
2. **Never commit** — `.pio/` build artifacts, local VS Code settings, or credentials
3. **Use `platformio.ini`** for board configuration (this IS shared)
4. **Use local VS Code settings** for port selection (this is NOT shared)

## Supported Platforms

- ESP32 (all variants)
- Teensy (4.x, 3.x)
- nRF52 (Adafruit, DK)
- AVR (Arduino Uno, Nano, Mega)
- STM32 (via STM32duino)
- RP2040 (Raspberry Pi Pico)

## Resources

- [PlatformIO Documentation](https://docs.platformio.org/)
- [Arduino Framework](https://www.arduino.cc/)
- [ESP32 Arduino Core](https://github.com/espressif/arduino-esp32)
- [Teensy PlatformIO](https://docs.platformio.org/en/latest/boards/teensy/)
