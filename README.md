ESP32 Health Monitor

**This project monitors the ESP32’s internal temperature, displays system information on an OLED, blinks an LED based on temperature levels, and uses a watchdog timer for crash recovery.
It’s built using FreeRTOS tasks for real-time multitasking.**

Features

Reads internal ESP32 temperature sensor.
Displays temperature, uptime, and system status on a 128x64 OLED.

LED Alerts:

1)Critical – Fast blinking
2)Warning – Slow blinking
3)Normal – Off

Watchdog Timer: Automatically resets the ESP32 on system freeze or overheating.

Built using FreeRTOS for smooth multitasking.

Hardware Used

1)ESP32 development board
2)SSD1306 128x64 OLED (I2C)
3)LED + 220Ω resistor (connected to GPIO 26)

Libraries Required

1)U8g2-For OLED
2)Wire (I2C communication)
3)esp_task_wdt (Watchdog, part of ESP32 Arduino core)

How It Works

TempMonitor Task: Reads internal temperature and updates system status.
OLED_Disp Task: Displays readings and uptime on OLED.
led_Update Task: Changes LED blinking speed based on temperature level.
Watchdog_uptime Task: Resets watchdog and tracks system uptime.
