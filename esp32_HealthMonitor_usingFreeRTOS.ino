#include <Arduino.h>
#include <U8g2lib.h>       //Specifying OLED Library we are using
#include <Wire.h>          //I2C Communication Protcol for OLED..
#include <esp_task_wdt.h>  //initialising watchdog timer..
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);  //specifying OLED Parameters..//
#define LED_PIN 26
#define WDT_TIMEOUT 7
float current_temp = 0;
int uptime = 0;
float getTemp() {
  return temperatureRead();  //Initialising Esp-32 Internal temperature sensor and getting the reading..
}
//Task1:Reading Temperature..
void TempMonitor(void *temperature) {
  while (true) {
    current_temp = getTemp();
    if (current_temp >= 75) {
      Serial.println("STATUS: CRITICAL");
    } else if (current_temp >= 75) {
      Serial.println("STATUS:WARNING");
    } else
      Serial.println("STATUS:NORMAL");

    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}
//Task 2:Displaying on OLED....
void OLED_Disp(void *display) {
  while (true) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.drawStr(2, 10, "ESP32 Health Monitor");
    //display internal temperature....
    char temp[20];
    sprintf(temp, "Temp:%.1fC", current_temp);
    u8g2.drawStr(2, 25, temp);
    //display data uploadtime....
    char uptimestr[25];
    sprintf(uptimestr, "Uptime:%d min", uptime/60);
    u8g2.drawStr(2, 55, uptimestr);
    //display Status...
    if (current_temp >= 75)
      u8g2.drawStr(2, 40, "Status: CRITICAL!");
    else if (current_temp >= 60)
      u8g2.drawStr(2, 40, "Status: WARNING");
    else
      u8g2.drawStr(2, 40, "Status: NORMAL");
    u8g2.sendBuffer();
    vTaskDelay(100000 / portTICK_PERIOD_MS);
  }
}
//Task3:updating LED
void led_Update(void *updating_LED) {
  while (true) {
    if (current_temp >= 75) {
      digitalWrite(LED_PIN, HIGH);
      vTaskDelay(300 / portTICK_PERIOD_MS);
      digitalWrite(LED_PIN, LOW);
      vTaskDelay(300 / portTICK_PERIOD_MS);
    } else if (current_temp >= 60) {
      digitalWrite(LED_PIN, HIGH);
      vTaskDelay(600 / portTICK_PERIOD_MS);
      digitalWrite(LED_PIN, LOW);
      vTaskDelay(600 / portTICK_PERIOD_MS);
    } else
      digitalWrite(LED_PIN, LOW);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
//Task 4:Watchdog setup and track uptime..
void Watchdog_uptime(void *watchdog_uptime) {
  while (true) {
    esp_task_wdt_reset();  //if any crash occurs due to overheating we will reset watchdog (means restart if overheating/freezing is still persistent).
    uptime++;
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawStr(2, 10, "Initialising....");
  u8g2.sendBuffer();


  // Initialize Watchdog Timer (ESP32 Arduino Core 3.x)
  esp_task_wdt_config_t wdt_config = {
    .timeout_ms = WDT_TIMEOUT * 1000,
    .idle_core_mask = 0,
    .trigger_panic = true
  };
  esp_task_wdt_init(&wdt_config);
  esp_task_wdt_add(NULL);

  //Create freeRTOS Tasks
  xTaskCreate(TempMonitor, "Temperature Monitor", 2048, NULL, 2, NULL);  //2048-No of bits,2 means-priority...
  xTaskCreate(OLED_Disp, "OLED_Disp", 2048, NULL, 1, NULL);
  xTaskCreate(led_Update, "led_Update", 2048, NULL, 2, NULL);
  xTaskCreate(Watchdog_uptime, "Watchdog_uptime", 2048, NULL, 3, NULL);
  Serial.println("System Setup Done");
}
void loop() {
  //Nothing here Since FreeRTOS will handle everything
}