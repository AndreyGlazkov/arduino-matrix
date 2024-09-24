#include <Arduino.h>

#include <SPI.h>
#include <Adafruit_SSD1306.h>
#include <LedMatrix.h>
#include <MatrixWeather.h>
#include <MatrixClock.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

#define LED_PORT 18
#define BRIGHTNESS 40
#define MATRIX_SIZE 16

#define WIFI_NAME "Xiaomi_1310"
#define WIFI_PASS "Nikita_2009"
#define WEATHER_API_KEY "b6d1ba500e374f5c82254122242409"

const int LINE_SIZE = MATRIX_SIZE*MATRIX_SIZE;

LedMatrix<MATRIX_SIZE, MATRIX_SIZE, LED_PORT> matrix;

WiFiUDP udp;
NTPClient ntpClient(udp, 3*3600);

unsigned long lastUpdateTime = 0;

MatrixWeather matrixWeatherSanny(8, 8);
MatrixClock matrixClock(0, 5);

void rainbow() {
  for (int i = 0; i < 256; i++)
  {
    fill_rainbow(matrix.getData(), LINE_SIZE, i, MATRIX_SIZE-1);
      matrix.show();
      delay(1000/50);
  }
}

void waitConnect() {
  CRGB * matrixData = matrix.getData();
  WiFi.begin(WIFI_NAME, WIFI_PASS);
  int p = 0;
  while (WiFi.status() != WL_CONNECTED) {
    *matrixData + p++ = CRGB::Orange;
    delay(200);
  }
  ntpClient.begin();
}

void updateTime() {
  if (millis() - lastUpdateTime > 1000) {
    ntpClient.update();
    matrixClock.setTime(ntpClient.getHours(), ntpClient.getMinutes());
    lastUpdateTime = millis();
  }
}

void setup() {
  Serial.begin(9600);
  matrix.setBrightness(BRIGHTNESS);

  waitConnect();

  matrixClock.setTime(00, 00);

  matrix.setBrightness(BRIGHTNESS);

  MatrixEnabledComponent c1;
  c1.enable = false;
  c1.component = &matrixWeatherSanny;

  MatrixEnabledComponent c2;
  c2.enable = true;
  c2.component = &matrixClock;

  matrix.addComponent(0, &c1);
  matrix.addComponent(1, &c2);
  matrix.show();
}

void loop() {
  //rainbow();
  updateTime();
}