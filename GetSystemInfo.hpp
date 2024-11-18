#include <ArduinoJson.h>
#include <HTTPClient.h>

extern char ip[100];

#include <Display.hpp>

HTTPClient http;

void fetchAndDisplaySystemInfo() {
  if (WiFi.status() == WL_CONNECTED) {
    http.begin("http://" + String(ip) + ":8080/systeminfo");
    int httpCode = http.GET();
    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);
        // 解析JSON数据
        StaticJsonDocument<256> doc;
        DeserializationError error = deserializeJson(doc, payload);
        if (!error) {
          long long total_memory = doc["total_memory"];
          long long free_memory = doc["free_memory"];
          float cpu_usage = doc["cpu_usage"];
          Serial.println("解析JSON成功");
          Serial.print("CPU Usage: ");
          Serial.println(cpu_usage);
          Serial.print("Total Memory: ");
          Serial.println(total_memory);
          Serial.print("Free Memory: ");
          Serial.println(free_memory);
          Serial.println("显示性能数据");
          // 调用显示函数
          displayPerformance(cpu_usage, total_memory, free_memory);
        } else {
          Serial.print("JSON解析错误: ");
          Serial.println(error.c_str());
        }
      } else {
        Serial.print("HTTP请求错误: ");
        Serial.println(httpCode);
      }
      http.end();
    } else {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      display.println("HTTP请求失败");
      display.println("请检查上位软件是否开启");
      display.display();
    }
  }
}