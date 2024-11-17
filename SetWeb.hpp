#include <WiFi.h>
#include <WebServer.h>
#include <EEPROM.h>



WebServer server(80);

void writeCredentialsToEEPROM(const char* ssid, const char* pass, const char* ip) {
  // 写入SSID
  for (int i = 0; i < strlen(ssid); i++) {
    EEPROM.write(SSID_ADDR + i, ssid[i]);
  }
  EEPROM.write(SSID_ADDR + strlen(ssid), '\0');  // 写入字符串结束符

  // 写入密码
  for (int i = 0; i < strlen(pass); i++) {
    EEPROM.write(PASS_ADDR + i, pass[i]);
  }
  EEPROM.write(PASS_ADDR + strlen(pass), '\0');  // 写入字符串结束符

  // 写入IP地址
  for (int i = 0; i < strlen(ip); i++) {
    EEPROM.write(IP_ADDR + i, ip[i]);
  }
  EEPROM.write(IP_ADDR + strlen(ip), '\0');  // 写入字符串结束符

  EEPROM.commit();  // 提交更改
}

void handleRoot() {
  server.send(200, "text/html", "<h1>Welcome to Performance Monitoring</h1>");
}

void handleSet() {
  if (server.hasArg("ssid") && server.hasArg("pass") && server.hasArg("ip")) {
    String ssid = server.arg("ssid");
    String pass = server.arg("pass");
    String ip = server.arg("ip");

    writeCredentialsToEEPROM(ssid.c_str(), pass.c_str(), ip.c_str());

    server.send(200, "text/html", "<h1>Settings Saved</h1>");
  } else {
    server.send(400, "text/html", "<h1>Missing Parameters</h1>");
  }
}