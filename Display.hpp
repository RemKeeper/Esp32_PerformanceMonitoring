#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>



Adafruit_SSD1306 display(128, 64, &Wire);
void displayPerformance(float cpu_usage, long long total_memory, long long free_memory) {
  // 计算内存使用情况
  long long used_memory = total_memory - free_memory;
  float memory_usage_percent = 0;
  if (total_memory > 0) {
    memory_usage_percent = (float)used_memory / total_memory * 100;
  }

  // 清除显示
  display.clearDisplay();

  // 显示CPU占用
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("CPU Usage: ");
  display.print(cpu_usage, 2);
  display.println("%");

  // 绘制CPU占用条形图
  int cpu_bar_width = (int)(cpu_usage * 1.28); // 128像素宽度
  display.fillRect(0, 10, cpu_bar_width, 8, SSD1306_WHITE);
  display.drawRect(0, 10, 128, 8, SSD1306_WHITE);

  // 显示内存占用
  display.setCursor(0, 20);
  display.print("Memory Usage: ");
  display.print(memory_usage_percent, 2);
  display.println("%");

  // 绘制内存占用条形图
  int memory_bar_width = (int)(memory_usage_percent * 1.28); // 128像素宽度
  display.fillRect(0, 30, memory_bar_width, 8, SSD1306_WHITE);
  display.drawRect(0, 30, 128, 8, SSD1306_WHITE);

  // 显示总内存和空闲内存
  display.setCursor(0, 40);
  display.print("Total: ");
  display.print(total_memory / (1024 * 1024));  // 转换为MB
  display.println(" MB");

  display.setCursor(0, 50);
  display.print("Free: ");
  display.print(free_memory / (1024 * 1024));  // 转换为MB
  display.println(" MB");

  // 更新显示
  display.display();
}