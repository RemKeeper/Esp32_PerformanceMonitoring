#include <WiFi.h>
#include <WebServer.h>
#include <EEPROM.h>
#include "EEPROM_SAVE.hpp"

extern char ssid[100];
extern char pass[100];
extern char ip[100];

WebServer server(80);

void handleRoot() {
  const char* html = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Set Parameters</title>
</head>
<body>
    <h1>Set Parameters</h1>
    <form id="setForm" action="/set" method="get">
        <label for="ssid">SSID:</label>
        <input type="text" id="ssid" name="ssid" required><br><br>
        
        <label for="pass">Password:</label>
        <input type="password" id="pass" name="pass" required><br><br>
        
        <label for="ip">IP Address:</label>
        <input type="text" id="ip" name="ip" required><br><br>
        
        <button type="submit">Set</button>
    </form>
</body>
</html>
)rawliteral";

  server.send(200, "text/html", html);
}

void handleSet() {
  if (server.hasArg("ssid") && server.hasArg("pass") && server.hasArg("ip")) {
    String ssidStr = server.arg("ssid");
    String passStr = server.arg("pass");
    String ipStr = server.arg("ip");

    writeCredentialsToEEPROM(ssidStr.c_str(), passStr.c_str(), ipStr.c_str());

    server.send(200, "text/html", "<h1>Settings Saved</h1>");

    delay(1000);
    ESP.restart();
  } else {
    server.send(400, "text/html", "<h1>Missing Parameters</h1>");
  }
}

void setWeb() {
  server.on("/", handleRoot);
  server.on("/set", handleSet);

  server.begin();
  Serial.println("HTTP server started");
}