#include <WiFi.h>

extern char ssid[100];
extern char pass[100];
#define MAX_RETRIES 20  // 网络最大连接次数

bool connectWifi() {
  Serial.println("调用WiFi连接函数");
  WiFi.begin(ssid, pass);

  for (int i = 0; i < MAX_RETRIES; i++) {
    delay(500);
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("网络连接成功");
      return true;
    }
  }
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("网络连接超时");
    return false;
  }
}