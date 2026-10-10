# Cross-Machine Embedded Development Setup
## Bionic + VS Code/PlatformIO + Git/GitHub

**Project:** GIT_Test  
**Target Hardware:** ESP32, Teensy, nRF52840, Arduino  
**Date:** 2026-10-10

---

## Current Status (Machine 1)

| Component | Location | Status |
|-----------|----------|--------|
| Project folder | `/Users/paulrichards/Documents/Projects/GIT_Test` | Ready |
| Git repository | `.git/` initialized | Connected to origin/main |
| PlatformIO Core | `/Users/paulrichards/.platformio/penv/bin/pio` | Installed |
| VS Code extension | PlatformIO IDE | Need to verify |

**Remote Repository:** https://github.com/dentrecasteaux/GIT_Test.git

---

## Overview: 2-Machine Workflow

```
Machine 1 (Current)                    Machine 2 (New)
     - Make changes                         -
     - Build & test                         -
     - git add/commit                       -
     - git push --origin main               -
                                            -
                 <- git pull                -
     --------------------------------------
     - Make changes
     - Build & test
     - git add/commit
     - git push --origin main
```

---

## Step-by-Step Setup

### Step 1: Verify Current Machine Setup

```bash
# Navigate to project
cd /Users/paulrichards/Documents/Projects/GIT_Test

# Check Git status
git status

# View remote configuration
git remote -v

# Test PlatformIO (build current default)
pio run
```

### Step 2: Ensure All Changes Are Committed

```bash
# Check what files have changed
git status

# Add all changes
git add .

# Commit with message
git commit -m "Initial cross-machine setup configuration"

# Push to GitHub
git push origin main
```

### Step 3: Set Up Second MacBook

#### A. Install Required Tools

1. **Install VS Code**
   - Download from: https://code.visualstudio.com/download
   - Install on second MacBook

2. **Install PlatformIO IDE Extension**
   - Open VS Code
   - Go to Extensions (Ctrl+Shift+X or Cmd+Shift+X)
   - Search for "PlatformIO IDE"
   - Click Install

3. **Install Git**
   ```bash
   # Check if Git is installed
   git --version
   
   # If not, install via Xcode command line tools
   xcode-select --install
   ```

#### B. Clone the Repository

```bash
# Navigate to where you want the project
cd ~/Documents/Projects

# Clone from GitHub
git clone https://github.com/dentrecasteaux/GIT_Test.git

# Verify the clone
cd GIT_Test
ls -la
```

#### C. Configure VS Code

1. Open the cloned folder in VS Code (File > Open Folder)
2. PlatformIO IDE will auto-detect the project
3. Wait for initial indexing (status bar shows "PlatformIO: Indexing...")
4. First build will download toolchains automatically

### Step 4: Verify Second Machine Build

```bash
cd ~/Documents/Projects/GIT_Test
pio run
```

This should compile successfully using the same configuration as Machine 1.

---

## Daily Development Workflow

### On Machine 1:

```bash
# 1. Check for updates from Machine 2
cd ~/Documents/Projects/GIT_Test
git pull origin main

# 2. Make your changes (edit code, modify platformio.ini, etc.)

# 3. Build to test
pio run

# 4. If successful, upload to board
pio run --target upload

# 5. Commit and push changes
git add .
git commit -m "Descriptive message about your changes"
git push origin main
```

### On Machine 2:

```bash
# 1. Get latest changes from Machine 1
cd ~/Documents/Projects/GIT_Test
git pull origin main

# 2. Build to ensure everything compiles
pio run

# 3. Make your changes

# 4. Build and test
pio run
pio run --target upload

# 5. Commit and push
git add .
git commit -m "Your change description"
git push origin main
```

---

## PlatformIO Commands Reference

### Building and Upload

| Command | Description |
|---------|-------------|
| `pio run` | Build the project (default environment) |
| `pio run -e esp32-s3` | Build for specific board/environment |
| `pio run --target upload` | Upload firmware to connected board |
| `pio run --target clean` | Clean build artifacts |
| `pio run -t buildprog` | Build and generate binary only |

### Monitoring

```bash
# Serial monitor (after upload)
pio device monitor

# Monitor with specific port
pio device monitor -p /dev/ttyUSB0  # Linux/Windows
pio device monitor -p /dev/cu.usbserial-*  # macOS

# Monitor with specific speed
pio device monitor -p auto -B 115200
```

### Environment Management

```bash
# List all available environments
pio run --list-targets envs

# Build multiple environments
pio run -e esp32dev -e teensy41
```

---

## Board-Specific Configuration

### Current Default: ESP32-S3 N16R8

```ini
[env:esp32-s3]
platform = espressif32
board = esp32-s3-devkitc-1
framework = arduino
monitor_speed = 115200
```

### To Change Target Board

1. Edit `platformio.ini`
2. Comment out current `[env:...]` section
3. Uncomment desired board section
4. Save and rebuild

```bash
pio run --target clean  # Clean old build artifacts
pio run                 # Build with new configuration
```

---

## Security Best Practices

### Never Commit:
- Generated binaries (`.bin`, `.elf`, `.map`)
- Build artifacts (`.pio/build/` - already ignored)
- Local credentials (`secrets.h`, `credentials.h`)
- Machine-specific paths

### Current `.gitignore` covers:
- `.pio/` - Build artifacts
- `*.bin`, `*.elf`, `*.map` - Binaries
- `.vscode/settings.json` - Local settings
- `.vscode/launch.json` - Debug config (ports vary by machine)

---

## Troubleshooting

### Common Issues:

#### 1. PlatformIO not found after clone
```bash
# Reinstall in VS Code: Cmd+Shift+P -> "PlatformIO: Reinstall"
# Or via Homebrew
brew install platformio
```

#### 2. Build fails with "toolchain not found"
```bash
# Clear PlatformIO cache
pio system cleanup

# Rebuild (downloads toolchains)
pio run --target clean
pio run
```

#### 3. Upload fails - port not found
```bash
# List available serial ports
pio device list

# Upload to specific port
pio run --target upload -e esp32-s3 --upload-port /dev/cu.usbserial-XXXX
```

#### 4. Different board selected on second machine
```bash
# Check current default environment
cat platformio.ini | grep -A 10 "\[env:\]"

# Build specific environment
pio run -e teensy41
```

---

## Recommended VS Code Settings

Create `.vscode/settings.json` (NOT committed to Git):

```json
{
    "platformio-ide.recentEnv": "esp32-s3",
    "editor.tabSize": 2,
    "editor.insertSpaces": true,
    "files.eol": "\\n",
    "files.trimTrailingWhitespace": true,
    "editor.formatOnSave": true
}
```

---

## Quick Start Checklist

### Machine 1 (Current):
- [ ] Project cloned/folder exists at `/Users/paulrichards/Documents/Projects/GIT_Test`
- [ ] PlatformIO installed and working
- [ ] All changes committed: `git add . && git commit -m "..." && git push`
- [ ] Remote repository URL: `https://github.com/dentrecasteaux/GIT_Test.git`

### Machine 2 (New Setup):
- [ ] Install VS Code
- [ ] Install PlatformIO IDE extension
- [ ] Clone repository: `git clone https://github.com/dentrecasteaux/GIT_Test.git`
- [ ] Open project in VS Code
- [ ] Test build: `pio run`

---

## Additional Resources

- **PlatformIO Docs:** https://docs.platformio.org/
- **ESP32 Arduino:** https://github.com/espressif/arduino-esp32
- **Teensy Arduino:** https://www.pjrc.com/teensy/duino.html
- **Git Book:** https://git-scm.com/book/en/v2

---

**Last Updated:** 2026-10-10  
**Maintainer:** paulrichards
