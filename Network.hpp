#include <WiFi.h>

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