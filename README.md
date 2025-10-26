**ESP32 Health Monitor**


This project continuously tracks the ESP32’s internal temperature, displays vital stats on an OLED, and provides LED-based visual alerts. A watchdog timer ensures automatic recovery from crashes or overheating.**

**Features**

Internal Temperature Monitoring – Reads the ESP32’s onboard temperature sensor.

OLED Display (128x64) – Shows temperature, uptime, and system status in real time.

**LED Alerts** (GPIO 26):

1) Critical – Fast blinking (Overheating detected)

2) Warning – Slow blinking (Elevated temperature)

3) Normal – LED off (Temperature stable)

Watchdog Timer – Resets the ESP32 automatically during system freeze or overheat.

FreeRTOS Multitasking – Separate tasks handle sensor reading, display, LED alerts, and watchdog operations smoothly.

**How It Works**

TempMonitor Task-Reads internal temperature and updates system status.

OLED_Disp Task-Displays temperature, uptime, and system status on the OLED.

led_Update Task-Adjusts LED blinking rate based on temperature conditions.

Watchdog_uptime Task	-esets the watchdog timer and tracks system uptime.

**Hardware Used**

ESP32 Development Board

SSD1306 OLED Display (128x64, I2C)

LED + 220Ω Resistor (connected to GPIO 26)

**Libraries Required**

U8g2 – OLED display handling

Wire – I²C communication

esp_task_wdt – Watchdog timer
