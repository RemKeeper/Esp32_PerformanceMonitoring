#ifndef EEPROM_SAVE_HPP
#define EEPROM_SAVE_HPP

#include <EEPROM.h>
#include <Arduino.h>

#define EEPROM_SIZE 512  // 定义EEPROM的大小
#define SSID_ADDR 0      // SSID的起始地址
#define PASS_ADDR 100    // 密码的起始地址
#define IP_ADDR 200      // IP地址的起始地址

extern char ssid[100];
extern char pass[100];
extern char ip[100];

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

void readCredentialsFromEEPROM(char* ssid, char* pass, char* ip) {
  // 读取SSID
  for (int i = 0; i < 100; i++) {
    ssid[i] = EEPROM.read(SSID_ADDR + i);
    if (ssid[i] == '\0') break;
  }

  // 读取密码
  for (int i = 0; i < 100; i++) {
    pass[i] = EEPROM.read(PASS_ADDR + i);
    if (pass[i] == '\0') break;
  }

  // 读取IP地址
  for (int i = 0; i < 100; i++) {
    ip[i] = EEPROM.read(IP_ADDR + i);
    if (ip[i] == '\0') break;
  }
}

//擦除EEPROM
void eraseEEPROM() {
  for (int i = 0; i < EEPROM_SIZE; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
}

#endif // EEPROM_SAVE_HPP