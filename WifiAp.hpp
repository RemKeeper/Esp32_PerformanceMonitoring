

#include <WiFi.h>


extern Adafruit_SSD1306 display;

void startAP() {
  const char* ssid = "PerformanceMonitoring";
  const char* password = "12345678";
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("AP IP address: ");
  display.println(IP);
  display.println("Please connect to this AP");
  display.println("to configure the device");
  display.display();
}
