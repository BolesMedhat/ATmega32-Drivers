# ATmega32-Drivers

![AVR Logo](https://img.shields.io/badge/Platform-AVR-052D42?logo=avr&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-blue.svg)

A modular, lightweight, and well-documented collection of drivers for the ATmega32 AVR microcontroller. The repository follows a layered architecture—separating hardware abstraction, peripheral control, and utility logic—to promote clarity, reusability, and scalability. Perfect for embedded systems development, learning, or production-grade applications.

---

## 📄 Documentation

#### Each driver module generally contains:

- `file_config.h`:  
  User configuration header.  
  *Configurable options are defined here.*

- `file_def.h`:  
  Internal definitions of constants, modes, register bits, and macros.  
  *All options in `file_config.h` are defined and well-documented here.*

- `file.h`:  
  Public interface header with function prototypes and documentation for external use.

- `file.c`:  
  Source file containing the implementation of the driver, written with clarity and inline documentation.

#### File Header Comments:

- Each source/header file starts with a `File Header Comment` that explains the **purpose of the driver**, provides **versioning information**, and may include **important notes or usage tips**.

#### Function Documentation (Doxygen Format):

- All public functions follow Doxygen-style comments for clarity and maintainability:

  ```c
  /**
   * @brief Brief description of what the function does.
   *
   * A detailed explanation of the function's behavior,
   * purpose, and any relevant details for users.
   *
   * @param param1 Description of the first parameter.
   * @param param2 Description of the second parameter.
   *
   * @return uint8 Status or result of the operation.
   */
  uint8 Function_Name(uint8 param1, uint8 param2);
  ````

---

## 🗂️ Drivers Structure

```
ATmega32/
├── HAL/               # Hardware Abstraction Layer (External Components)
│   ├── DC_MOTOR/      # DC Motor Driver
│   ├── DHT11/         # Digital Temperature/Humidity Sensor
│   ├── EXT_EEPROM/    # External I2C EEPROM (24Cxx)
│   ├── JOYSTICK/      # Analog Joystick
│   ├── KEYPAD/        # Keypad (configurable from 2x2 to 8x8)
│   ├── LCD/           # Character LCD
│   ├── LM35/          # Temperature Sensor
│   ├── OLED/          # OLED Display (SSD1306, I2C)
│   ├── RTC/           # Real-Time Clock (DS1307)
│   ├── SEG7/          # 7-Segment Display (Multiplexed)
│   ├── SERVO/         # Servo Motor (Software PWM, up to 9 channels)
│   ├── ShiftRegister/ # Shift Register (74HC595 / 74HC165)
│   └── USONIC/        # Ultrasonic Sensor (HC-SR04, supports multiple units)
│
├── MCAL/              # Microcontroller Abstraction Layer
│   ├── DIO/           # Digital I/O Port Control
│   ├── ADC/           # Analog-to-Digital Converter
│   ├── GIE/           # Global Interrupt Enable
│   ├── EXTI/          # External Interrupts
│   ├── EEPROM/        # Internal EEPROM
│   ├── UART/          # Serial Communication
│   ├── I2C/           # I2C/TWI Interface (Master/Slave)
│   ├── SPI/           # SPI Communication
│   ├── TIMER0/        # 8-bit Timer/Counter0 (PWM Support)
│   ├── TIMER1/        # 16-bit Timer/Counter1 (PWM/ICU Support)
│   ├── TIMER2/        # 8-bit Timer/Counter2 (PWM Support)
│   ├── WDT/           # Watchdog Timer
│   └── AC/            # Analog Comparator
│
└── LIB/               # Common Utility Libraries
    ├── BIT_MATH/      # Bit Manipulation Macros (SET_BIT, CLR_BIT, etc.)
    ├── DataConvert/   # Data Conversion Functions (e.g., ftoa, itoa, dtoh)
    ├── MAPPING/       # Value Scaling and Mapping Utilities
    └── STD_TYPES/     # Standardized Data Type Definitions
```

---

## 📦 Key Features

* **Layered Architecture**
  
  * **APP** (Application Layer): User-defined logic that utilizes drivers to build specific functionality  
  * **HAL** (Hardware Abstraction Layer): Interfaces for external components (e.g., sensors, displays)  
  * **MCAL** (Microcontroller Abstraction Layer): Interfaces for core on-chip peripherals (e.g., GPIO, timers, ADC)  
  * **LIB** (Utility Libraries): Common macros, types, math, and data manipulation helpers

* **Modular and Lightweight**

  * Each driver is self-contained, with minimal dependencies
  * **No use of** `<stdio.h>`, `<stdlib.h>`, or other standard C/AVR libraries — ensuring maximum portability and reduced overhead

* **Polling and Interrupt-Based Support**

  * Drivers support both **polling** and **interrupt-driven** modes
  * **Callback mechanisms** are provided for user-defined ISR handlers, enabling flexible and responsive design

* **Highly Configurable**

  * Peripherals are configured through `*_config.h` headers

* **Well-Documented**

  * Code use Doxygen format for clarity

---

## 🛠️ Usage

1. **Clone the repository:**

   ```bash
   git clone https://github.com/BolesMedhat/ATmega32-Drivers.git
   ```

2. **Add the `HAL/`, `MCAL/`, and `LIB/` folders to your AVR project:**
   Include the following folders:

   ```
   HAL/
   MCAL/
   LIB/
   main.c
   ```

3. **Remove unused drivers** (optional but recommended):  
   Delete peripheral folders from `HAL/`, `MCAL/`, or `LIB/` that your project doesn't need  
   to reduce build time and memory usage.

4. **Include required driver headers in your code:**

   ```c
   #include "HAL/LCD/LCD.h"
   ```

5. **Configure peripherals (if applicable):**  
   Some drivers include a `*_config.h` file for setting pins, modes, resolutions, and interrupts.
   Edit the configuration as needed:

   Example: LCD_config.h
   ```c
   #define LCD_MODE        LCD_4_BIT
   #define LCD_DATA_PORT   DIO_PORTA
   ```

6. **Initialize and use peripherals:**

   ```c
   LCD_Init();
   LCD_PrintString("ATmega32 Ready");
   ```

---

## 💻 Supported IDEs

* **Microchip Studio / Atmel Studio**
* **AVR-GCC (Command Line / Makefile)**
* **Eclipse with AVR Plugin**
* **PlatformIO (VS Code)**

---

## 📜 License

MIT License © 2025 Boles Medhat
Free to use, modify, and distribute for personal or commercial use with attribution.

---
## 👨‍💻 Author

**Poles Medhat** – Embedded Systems Developer
**Contact**:  
[LinkedIn](https://www.linkedin.com/in/boles-medhat)

---





