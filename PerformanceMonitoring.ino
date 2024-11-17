#include <Arduino.h>

#include "EEPROM_SAVE.hpp"
#include "SetWeb.hpp"
#include "GetSystemInfo.hpp"
#include "Network.hpp"
#include "Display.hpp"




#define SDA_PIN 26
#define SCL_PIN 27

#define MAX_RETRIES 20  // 网络最大连接次数

String ssid = "";
String pass = "";
String ip = "";

HTTPClient http;


void setup() {
  EEPROM.begin(EEPROM_SIZE);  // 初始化EEPROM

  Serial.begin(9600);

  if (connectWifi()) {
    Serial.println("set up");
  }

  Wire.begin(SDA_PIN, SCL_PIN);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  Serial.println("初始化完成");
  display.display();
}

void loop() {
  // 调用HTTP请求函数
  fetchAndDisplaySystemInfo();

  // 延迟一段时间
  delay(10000);  // 每10秒请求一次
}



