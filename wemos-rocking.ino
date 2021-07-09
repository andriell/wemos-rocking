#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <Wire.h>
#include "SH1106Wire.h" // Library: ESP8266 and ESP32 OLED driver for SSD1306 displays
#include <ArduinoJson.h> // Library: ArduinoJson
#include <Servo.h>
#include "const.h"

#define MAX_UL       0xFFFFFFFFUL

#define WEMOS_A0     17
#define WEMOS_D0     16
#define WEMOS_D1     5
#define WEMOS_D2     4
#define WEMOS_D3     0
#define WEMOS_D4_LED 2
#define WEMOS_D5     14
#define WEMOS_D6     12
#define WEMOS_D7     13
#define WEMOS_D8     15
#define WEMOS_TX     1
#define WEMOS_RX     3



struct Settings {
  int mode; // m
  int speed; // s
  int pause; // p
  int a0; // a0
  int a1; // a1
};

// s6s is settings like i18n is internationalization
Settings s6s;

unsigned long mainMillis() {
  return  millis() + (MAX_UL - 30000UL);
}

void setup() {
  wemosSetup();
  dbgSetup();
  dbgLn(1, "Setup");
  if (!SPIFFS.begin()) {
    dbgLn(1, "An Error has occurred while mounting SPIFFS");
    return;
  }
  wifiSetup();
  ledSetup();
  wsSetup();
  settingsLoadFile();
  rockingSetup();
}

int alarmCount = 0;

void loop() {
  srLoop();
  dbgLoop();
  wifiLoop();
  wsLoop();
  if (s6s.mode == 1 || s6s.mode == 3) {
    rockingLoop();
  }
  delay(20);
}
