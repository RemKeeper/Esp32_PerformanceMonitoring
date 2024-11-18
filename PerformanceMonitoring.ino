#include <Arduino.h>

#include "EEPROM_SAVE.hpp"
#include "SetWeb.hpp"
#include "GetSystemInfo.hpp"
#include "Network.hpp"
#include "WifiAp.hpp"

#define SDA_PIN 26
#define SCL_PIN 27

char ssid[100] = "";
char pass[100] = "";
char ip[100] = "";

boolean IsConfigured = false;

void setup() {
  EEPROM.begin(EEPROM_SIZE);  // 初始化EEPROM

  Serial.begin(9600);

  // 尝试从EEPROM中读取相关配置
  readCredentialsFromEEPROM(ssid, pass, ip);

  Serial.println("ssid: ");
  Serial.println(ssid);
  Serial.println("pass: ");
  Serial.println(pass);
  Serial.println("ip: ");
  Serial.println(ip);

  Wire.begin(SDA_PIN, SCL_PIN);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  // 判断是否需要重新配置
  if (strlen(ssid) == 0 || strlen(pass) == 0 || strlen(ip) == 0) {
    Serial.println("未找到配置信息，开始配置");
    startAP();
    setWeb();
  } else {
    IsConfigured = true;
    if (connectWifi()) {
      Serial.println("set up");
    } else {
      eraseEEPROM();
      ESP.restart();
    }
  }



  
}

void loop() {
  if (!IsConfigured) {
    server.handleClient();
  }

  // 调用HTTP请求函数
  fetchAndDisplaySystemInfo();

  // 延迟一段时间
  delay(10000);  // 每10秒请求一次
}