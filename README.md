# STM32 Temperature Monitor (DS18B20 + ST7789 TFT + PWM Buzzer)

A compact embedded system built on STM32F1 that reads temperature from a DS18B20 sensor, displays it on a 240×240 ST7789 TFT display, and activates a PWM buzzer when the temperature exceeds a configurable threshold.

This project demonstrates:
- 1‑Wire protocol implementation for DS18B20 (bit‑banging, precise timing)
- ST7789 TFT display driver (SPI, custom font rendering)
- PWM audio alert using TIM1
- Low‑level GPIO configuration (direct CRL/CRH register manipulation)
- Efficient SPI transmission without HAL overhead
- Clean modular structure for sensor, display, and UI logic

---

## 🚀 Features

- Accurate temperature measurement using DS18B20 (12‑bit resolution)
- Real‑time temperature display on ST7789 (240×240)
- Custom 28×34 px font rendering
- Audible alert when temperature exceeds `TEMP_UPPER_LIMIT`
- Optimized SPI communication (manual TX, busy‑flag polling)
- Fully bare‑metal 1‑Wire implementation (no external libraries)
- Modular and easy to extend

---

## 🌡 How It Works

### 1. DS18B20 Temperature Reading
The driver performs:

- Reset pulse  
- Skip ROM (`0xCC`)  
- Start conversion (`0x44`)  
- Wait 750 ms  
- Read scratchpad (`0xBE`)  
- Convert raw value → Celsius  

Temperature formula:

temp = raw / 16.0

### 2. Display Rendering (ST7789)
The display driver:

- Initializes ST7789
- Sets address window for text area
- Renders characters using a custom 28×34 bitmap font
- Draws temperature string at fixed coordinates

### 3. PWM Buzzer Alert
If temperature exceeds:

#define TEMP_UPPER_LIMIT 28

The buzzer plays a frequency sweep:

- 1 kHz  
- 3 kHz  
- 6 kHz  
- 9 kHz  
- 12 kHz  

Each tone lasts 250 ms.

---

## 🖥 Example Output

Display shows:

23.7°C

If temperature > 28°C → buzzer alarm.

---

## 🔧 Requirements

- STM32F103C8T6 (or compatible)
- DS18B20 temperature sensor
- ST7789 240×240 TFT display (SPI)
- Passive buzzer
- STM32CubeIDE or compatible toolchain

---

## 🛠 Build & Flash

1. Open project in STM32CubeIDE  
2. Connect hardware according to pinout  
3. Build and flash  
4. System starts automatically and updates temperature continuously

---

## 📌 Pinout Summary

| Peripheral | STM32 Pin | Notes |
|-----------|-----------|-------|
| DS18B20   | PA1       | 1‑Wire data |
| ST7789 SCK | PA5      | SPI1 |
| ST7789 MOSI | PA7     | SPI1 |
| ST7789 RES | PB0      | Reset |
| ST7789 DC  | PB1      | Data/Command |
| Buzzer (PWM) | PA8    | TIM1 CH1 |

---

## 📄 Notes

- 1‑Wire timing implemented using inline assembly microsecond delay  
- SPI transmission optimized by direct register access  
- Font stored as bitmap array in `fonts.c`  
