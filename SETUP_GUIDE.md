# Complete Setup Guide: Bionic + PlatformIO + Git/GitHub

**Project:** GIT_Test  
**Target Hardware:** ESP32, Teensy, nRF52840, Arduino  
**Date:** 2026-10-10

---

## Table of Contents

1. [Current Status](#1-current-status)
2. [Step 1: Install PlatformIO Core](#step-1-install-platformio-core)
3. [Step 2: Install GitHub CLI (gh)](#step-2-install-github-cli-gh)
4. [Step 3: Create a GitHub Repository](#step-3-create-a-github-repository)
5. [Step 4: Connect Local Repo to GitHub](#step-4-connect-local-repo-to-github)
6. [Step 5: Configure VS Code + PlatformIO IDE](#step-5-configure-vs-code--platformio-ide)
7. [Step 6: First Build & Upload](#step-6-first-build--upload)
8. [Step 7: Set Up Second MacBook](#step-7-set-up-second-macbook)
9. [Daily Workflow](#daily-workflow)
10. [Troubleshooting](#troubleshooting)

---

## 1. Current Status

| Component | Status |
|-----------|--------|
| Project folder | ✅ `/Users/paulrichards/Documents/Projects/GIT_Test` |
| Git repository | ✅ Initialized, 1 commit on `main` branch |
| PlatformIO Core | ❌ Not installed |
| GitHub CLI (`gh`) | ❌ Not installed |
| VS Code + PlatformIO IDE extension | ❌ Not configured |
| GitHub remote | ❌ Not connected |

---

## Step 1: Install PlatformIO Core

PlatformIO Core is the command-line build system. The VS Code extension (PlatformIO IDE) uses it under the hood.

### Option A: Install via pip (Recommended)

```bash
pip3 install platformio
```

Verify installation:
```bash
pio --version
```

Expected output: `PlatformIO, version 6.x.x`

### Option B: Install via Homebrew

```bash
brew install platformio
```

### What This Does

- Installs the `pio` command globally
- Downloads toolchains for ESP32, AVR, ARM, etc. on first build
- Takes ~2-5 GB of disk space for all toolchains (you can prune unused ones)

### Verify It Works

```bash
cd /Users/paulrichards/Documents/Projects/GIT_Test
pio run
```

This will:
1. Download the ESP32 toolchain (first time only, ~500MB)
2. Compile `src/main.cpp`
3. Link and create a `.pio/build/esp32dev/firmware.bin`

**⏱ First build takes 3-10 minutes. Subsequent builds take ~10 seconds.**

---

## Step 2: Install GitHub CLI (`gh`)

The GitHub CLI makes it easy to create repos, push, and manage PRs from the terminal.

```bash
brew install gh
```

Authenticate with GitHub:
```bash
gh auth login
```

Follow the prompts:
1. **What is your preferred protocol for Git operations?** → `HTTPS` (easiest with SSH key fallback)
2. **Authenticate Git with your GitHub credentials?** → `Yes`
3. **How would you like to authenticate?** → `Login with a web browser` (follow the URL)

Verify:
```bash
gh auth status
```

---

## Step 3: Create a GitHub Repository

### Option A: Via GitHub CLI (Fastest)

```bash
cd /Users/paulrichards/Documents/Projects/GIT_Test
gh repo create paulrichards/GIT_Test --public --push --source=.
```

This creates a **public** repo named `GIT_Test` under your `paulrichards` GitHub account and pushes the current code.

### Option B: Via GitHub Website

1. Go to https://github.com/new
2. Repository name: `GIT_Test`
3. Visibility: **Public** (or Private if you prefer)
4. **DO NOT** initialize with README, .gitignore, or license (we already have these)
5. Click **Create repository**
6. Copy the HTTPS URL (e.g., `https://github.com/paulrichards/GIT_Test.git`)

Then connect locally:
```bash
cd /Users/paulrichards/Documents/Projects/GIT_Test
git remote add origin https://github.com/paulrichards/GIT_Test.git
git branch -M main
git push -u origin main
```

---

## Step 4: Connect Local Repo to GitHub

If you used Option B above, you're done. If you used Option A, skip this.

Verify the connection:
```bash
cd /Users/paulrichards/Documents/Projects/GIT_Test
git remote -v
```

Expected output:
```
origin  https://github.com/paulrichards/GIT_Test.git (fetch)
origin  https://github.com/paulrichards/GIT_Test.git (push)
```

Check the status:
```bash
git status
git log --oneline
```

Expected:
```
48eee14 Initial project setup: PlatformIO + Arduino template
```

---

## Step 5: Configure VS Code + PlatformIO IDE

### Install the PlatformIO IDE Extension

1. Open VS Code
2. Go to Extensions (`Cmd+Shift+X`)
3. Search for **PlatformIO IDE**
4. Click **Install** (by PlatformIO)
5. Wait for the PlatformIO toolbar to appear at the bottom

### Open the Project

1. In VS Code, go to `File > Open Folder`
2. Navigate to `/Users/paulrichards/Documents/Projects/GIT_Test`
3. Click **Open**

You should see the PlatformIO toolbar at the bottom with icons for:
- ✅ Build (checkmark)
- 🔄 Upload (arrow)
- 📊 Serial Monitor (waveform)
- 🗑 Clean (trash)
- 📁 Explorer (project files)

### Configure Your Board

1. Click the **checkmark icon** (Build) → it will show the current environment
2. Click the **gear icon** (PlatformIO: Select Target Platform)
3. Choose your board from the list, e.g.:
   - **Espressif 32 > ESP32 Dev Module** (for ESP32)
   - **Teensy > Teensy 4.1** (for Teensy)
   - **Nordic nRF52 > nRF52840 DK** (for nRF52840)

This updates `platformio.ini` automatically.

### Configure Serial Port (Machine-Specific)

Serial ports differ between machines. This is a **local** setting:

1. Click the **gear icon** (PlatformIO: Select Serial Monitor Port)
2. Choose your device, e.g.:
   - ESP32: `/dev/cu.SLAB_USBtoUART` or `/dev/cu.usbserial-XXXXX`
   - Teensy: `/dev/cu.usbmodemXXXX`
   - nRF52840: `/dev/cu.usbmodemXXXX`

**This setting is stored in `.vscode/settings.json` which is in `.gitignore` — it won't be committed.**

---

## Step 6: First Build & Upload

### Build the Project

1. Click the **checkmark icon** (Build) in the PlatformIO toolbar
2. Watch the output panel at the bottom
3. Wait for `========================= [SUCCESS] ...`

Or via terminal:
```bash
cd /Users/paulrichards/Documents/Projects/GIT_Test
pio run
```

### Upload to Hardware

1. Connect your board via USB
2. Click the **arrow icon** (Upload) in the PlatformIO toolbar
3. Wait for `========================= [SUCCESS] ...`

Or via terminal:
```bash
pio run --target upload
```

### Open Serial Monitor

1. Click the **waveform icon** (Serial Monitor)
2. Or via terminal:
   ```bash
   pio device monitor
   ```
3. You should see:
   ```
   === System Startup ===
   ----------------------------------------
   Uptime: 0 ms
   Chip Model: ESP32-D0WDQ6
   CPU Freq: 240 MHz
   Free Heap: XXXXXX bytes
   === Setup Complete ===
   ----------------------------------------
   LED ON
   LED OFF
   LED ON
   ...
   ```

4. Press `Ctrl+C` or click the **stop icon** to exit

### Commit Your Changes

If you changed the board configuration:
```bash
cd /Users/paulrichards/Documents/Projects/GIT_Test
git add platformio.ini
git commit -m "Configure board: ESP32 Dev Module"
git push
```

---

## Step 7: Set Up Second MacBook

### On the Second MacBook

#### 1. Install Prerequisites

```bash
# Install Homebrew if not already installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install PlatformIO
pip3 install platformio

# Install GitHub CLI
brew install gh

# Authenticate with GitHub
gh auth login
```

#### 2. Clone the Repository

```bash
cd ~/Documents/Projects   # or your preferred location
git clone https://github.com/paulrichards/GIT_Test.git
cd GIT_Test
```

#### 3. Open in VS Code

```bash
code .
```

#### 4. Install PlatformIO IDE Extension

Same as Step 5 — install the PlatformIO IDE extension in VS Code.

#### 5. Configure Board & Port

Same as Step 5 — select your target board and serial port. These are **local** settings only.

#### 6. Build & Verify

```bash
pio run
```

---

## Daily Workflow

### Working on Machine A (e.g., MacBook 1)

```bash
# 1. Pull latest changes before starting
cd /Users/paulrichards/Documents/Projects/GIT_Test
git pull

# 2. Create a feature branch for your work
git checkout -b feature/new-sensor-driver

# 3. Code... (Bionic can help here!)

# 4. Test locally
pio run
pio run --target upload
pio device monitor

# 5. Commit your changes
git add .
git commit -m "Add new sensor driver for XYZ"

# 6. Push to GitHub
git push -u origin feature/new-sensor-driver

# 7. (Optional) Create a Pull Request
gh pr create --title "Add new sensor driver" --body "Details about the changes..."
```

### Working on Machine B (e.g., MacBook 2)

```bash
# 1. Pull latest changes
cd ~/Documents/Projects/GIT_Test
git pull

# 2. Switch to the feature branch
git checkout feature/new-sensor-driver

# 3. Continue working...

# 4. When done, push
git push
```

### Merging Back to Main

```bash
# On Machine A (or wherever you're merging from)
git checkout main
git pull
git merge feature/new-sensor-driver
git push

# Delete the feature branch (optional)
git branch -d feature/new-sensor-driver
git push origin --delete feature/new-sensor-driver
```

---

## Bionic Collaboration Workflow

### How Bionic Helps

1. **Code Review & Generation** — Describe what you want, and I'll write the code
2. **Debugging** — Paste error messages or serial output, and I'll help diagnose
3. **Architecture** — Ask me to design system architecture or state machines
4. **Documentation** — I can update README, add comments, create diagrams

### Example Prompts for Bionic

```
"Add a WiFi scanner to main.cpp that prints available networks"
"Create a library in lib/ for driving the SSD1306 OLED display"
"Debug this serial output: [paste output]"
"Create a state machine for a traffic light controller"
"Add OTA (Over-The-Air) update support for ESP32"
"Write a unit test for my sensor parsing function"
```

### Best Practices for Bionic-Assisted Development

1. **Commit frequently** — Small, focused commits make it easy to revert
2. **Use feature branches** — Keep `main` always buildable
3. **Test before pushing** — Always build and upload before committing
4. **Clear commit messages** — Explain what and why, not just what

---

## Troubleshooting

### PlatformIO Won't Install

```bash
# Try with --user flag
pip3 install --user platformio

# Or use a virtual environment
python3 -m venv pio-env
source pio-env/bin/activate
pip3 install platformio
```

### ESP32 Won't Upload

1. **Hold BOOT button** while clicking Upload, then release when upload starts
2. **Check the port**: `pio device list`
3. **Try a different USB cable** (some are charge-only)
4. **Try a different USB port** (prefer USB 2.0 ports)

### Teensy Won't Upload

1. **Press the button** on the Teensy board after upload starts
2. **Install Teensy Loader**: `brew install --cask teensy-loader`
3. **Check permissions**: Your user needs access to the USB device

### nRF52840 Won't Upload

1. **Install nRFJProg**: `brew install nrfjprog`
2. **Check J-Link drivers**: https://www.segger.com/downloads/jlink/
3. **Try SWD debug probe** if using a custom board

### Git Merge Conflicts

```bash
# Resolve conflicts manually, then:
git add .
git commit -m "Resolve merge conflicts"
git push
```

### VS Code Can't Find PlatformIO

1. Restart VS Code
2. Open Command Palette (`Cmd+Shift+P`)
3. Type `PlatformIO: Reinstall`
4. Wait for reinstallation to complete

### Serial Monitor Shows Garbage

- Check the **baud rate** matches between code and monitor
- Default is `115200` — verify in `platformio.ini` and monitor settings

### Build Fails with "Toolchain Not Found"

```bash
# Reinstall toolchains
pio upgrade
pio update
```

### Disk Space Issues

PlatformIO toolchains can use 2-5 GB. To prune unused ones:

```bash
# List installed toolchains
ls ~/.platformio/packages/

# Remove unused ones (be careful!)
# For example, if you only use ESP32:
rm -rf ~/.platformio/packages/tool-avr
rm -rf ~/.platformio/packages/toolchain-gccarmnoneeabi
```

---

## Quick Reference Card

| Action | Command |
|--------|---------|
| Build | `pio run` |
| Build specific board | `pio run -e esp32dev` |
| Upload | `pio run --target upload` |
| Upload + Monitor | `pio run --target upload && pio device monitor` |
| Clean build | `pio run --target clean` |
| List devices | `pio device list` |
| Update PlatformIO | `pio upgrade` |
| Git pull | `git pull` |
| Git push | `git push` |
| Create branch | `git checkout -b feature/name` |
| Create PR | `gh pr create --title "..." --body "..."` |

---

## Next Steps

1. ✅ Install PlatformIO Core
2. ✅ Install GitHub CLI and authenticate
3. ✅ Create GitHub repository
4. ✅ Connect local repo to GitHub
5. ✅ Configure VS Code + PlatformIO IDE extension
6. ✅ Build and upload your first firmware
7. ✅ Set up second MacBook
8. 🔄 Start coding!

---

*Generated by Bionic on 2026-10-10*
