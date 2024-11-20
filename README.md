# Offline Embedded Environmental & Navigation Monitor

![Project Status](https://img.shields.io/badge/Status-Completed-success)
![License](https://img.shields.io/badge/License-MIT-blue)
![C++](https://img.shields.io/badge/Language-C++-00599C?logo=c%2B%2B)
![Arduino](https://img.shields.io/badge/Platform-Arduino-00979D?logo=arduino)
![PlatformIO](https://img.shields.io/badge/Environment-PlatformIO%2FAVR-orange?logo=platformio)

## 📌 Overview & Features
This project is an offline, standalone embedded navigation and weather monitoring device designed for remote field exploration where cellular, GPS, and internet connectivity are unavailable. 

**Core Features:**
- **Dynamic Cardinal Direction Mapping:** Converts raw azimuth data into 8-point compass headings (N, NE, E, SE, S, SW, W, NW) using a digital magnetometer.
- **Environmental Tracking:** Continuously monitors ambient temperature (°C) and relative humidity (%) using an AM2302/DHT22 sensor.
- **Manual State Toggle:** Interface is controlled via three momentary push buttons to toggle between Temperature, Humidity, and Compass modes.
- **100% Offline Edge Operation:** Computations and environmental mapping happen entirely on-device, powered independently by a 9V battery with a stepped-down 5V LM7805 voltage regulator.

## 🔌 Hardware Architecture & Wiring Pinout
The system is built around the **Arduino Uno Rev3 (ATmega328P)**. 

### Pin Mapping Table
| Component | Pin Function | Arduino Pin | Description |
| :--- | :--- | :--- | :--- |
| **DHT22 / AM2302** | DATA | `A0` | Temperature and humidity digital data pin |
| **QMC5883L** | SDA | `A4` (I2C) | I2C Data line for magnetometer |
| **QMC5883L** | SCL | `A5` (I2C) | I2C Clock line for magnetometer |
| **Push Button 1** | Signal | `A1` | Toggles interface to **Temperature** display |
| **Push Button 2** | Signal | `A2` | Toggles interface to **Humidity** display |
| **Push Button 3** | Signal | `A3` | Toggles interface to **Compass/Azimuth** display |
| **16x2 LCD** | RS | `13` | Register Select |
| **16x2 LCD** | EN | `11` | Enable |
| **16x2 LCD** | D4 | `6` | Data Line 4 |
| **16x2 LCD** | D5 | `5` | Data Line 5 |
| **16x2 LCD** | D6 | `4` | Data Line 6 |
| **16x2 LCD** | D7 | `3` | Data Line 7 |

*(Note: Push buttons are configured with `HIGH` logic on press, updating the UI state continuously with a 100ms refresh rate delay.)*

## 📦 Firmware Dependencies
The firmware uses the following standard libraries, which must be installed to compile the sketch:
- `#include <QMC5883LCompass.h>` – For interfacing with the I2C magnetometer.
- `#include <AM2302-Sensor.h>` – For the digital temperature and humidity sensor.
- `#include <LiquidCrystal.h>` – For driving the 16x2 character LCD in parallel 4-bit mode.

## 🧭 Compass Calibration & Mapping Logic
The firmware utilizes mathematical offset and remapping to calibrate the compass output. The implementation is located within the `Compass()` subroutine:

1. **Raw Azimuth & Offset:** The raw azimuth is retrieved (`int a = compass.getAzimuth();`), and a static alignment offset of `80` degrees is subtracted (`a - 80`).
2. **Negative Bound Remapping:** If the resulting direction is negative (between `-260` and `0`), it is proportionally remapped into a `100` to `360` degree range using Arduino's `map()` function to correct the continuous rotation scale.
3. **Inversion:** The orientation is inverted by mapping `0 -> 360` to `360 -> 0`, converting counter-clockwise rotation to clockwise (or vice-versa, depending on physical sensor orientation).
4. **Cardinal Slicing:** The normalized 360° heading is split into 45° sectors, mapping the degrees to textual cardinal directions (e.g., `>337.5 || <22.5` maps to `N`).

## ⚙️ Communication & Timing Configurations
- **Serial Baud Rate:** `9600` bps for serial debugging.
- **Sensor Init Delay:** `1000ms` boot delay if the AM2302 is successfully detected.
- **Error State Delay:** `10000ms` loop delay if the temperature/humidity sensor is missing.
- **Main Loop Refresh:** `100ms` delay between interface updates.

## 📂 Project Structure
```text
.
├── firmware/
│   └── CHT_project.ino      # Main application code
├── docs/                    # Datasheets and technical reports
├── schematics/              # Fritzing/Eagle hardware schematics
└── README.md                # Project documentation (this file)
```

## 🎓 Academic Context
This hardware and embedded software system was developed as part of the **CSE5015 Computing Project** at **ICBT Campus**. It demonstrates practical application of edge computing, sensor integration, and standalone UI management using the ATmega328P.
