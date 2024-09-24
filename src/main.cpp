#include <Arduino.h>

#include <SPI.h>
#include <Adafruit_SSD1306.h>
#include <LedMatrix.h>
#include <MatrixWeather.h>
#include <MatrixClock.h>
#include <MatrixTemperature.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <WeatherService.h>

#define LED_PORT 18
#define BRIGHTNESS 40
#define MATRIX_SIZE 16

#define WIFI_NAME "Xiaomi_1310"
#define WIFI_PASS "Nikita_2009"
#define WEATHER_API_KEY "b6d1ba500e374f5c82254122242409"
#define WEATHER_CITY "Kyiv"

const int LINE_SIZE = MATRIX_SIZE*MATRIX_SIZE;

LedMatrix<MATRIX_SIZE, MATRIX_SIZE, LED_PORT> matrix;

WiFiUDP udp;
NTPClient ntpClient(udp, 3*3600);
WeatherService weatherService(WEATHER_API_KEY);
MatrixClock matrixClock(0, 1);
MatrixTemperature matrixTemterature(2, 9);

unsigned long lastUpdateTime = 0;

void rainbow() {
  for (int i = 0; i < 256; i++)
  {
    fill_rainbow(matrix.getData(), LINE_SIZE, i, MATRIX_SIZE-1);
      matrix.show();
      delay(1000/50);
  }
};

void waitConnect() {
  CRGB * matrixData = matrix.getData();
  WiFi.begin(WIFI_NAME, WIFI_PASS);
  int p = 0;
  while (WiFi.status() != WL_CONNECTED) {
    *(matrixData + p++) = CRGB::Orange;
    matrix.show();
    delay(100);
  }
  ntpClient.begin();
};

void updateTime() {
  if (millis() - lastUpdateTime > 1000) {
    ntpClient.update();
    matrixClock.setTime(ntpClient.getHours(), ntpClient.getMinutes());
    lastUpdateTime = millis();
  }
};

void updateWeather() {
  matrixTemterature.setTemperature(weatherService.getTemperature());
};


void setup() {
  Serial.begin(9600);

  weatherService.setCity(WEATHER_CITY);

  matrix.setBrightness(BRIGHTNESS);

  waitConnect();

  matrixClock.setTime(00, 00);

  matrix.setBrightness(BRIGHTNESS);

  MatrixEnabledComponent c1;
  c1.enable = true;
  c1.component = &matrixClock;

  MatrixEnabledComponent c2;
  c2.enable = true;
  c2.component = &matrixTemterature;

  matrix.addComponent(0, &c1);
  matrix.addComponent(1, &c2);
  
  matrix.show();
}

void loop() {
  rainbow();
  updateTime();
  updateWeather();
  delay(100);
}