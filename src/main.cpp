#include <Arduino.h>

#include <SPI.h>
#include <Adafruit_SSD1306.h>

#include <LedMatrix.h>
#include <MatrixWeather.h>
#include <MatrixClock.h>
#include <MatrixTemperature.h>
#include <effects/Rain.h>
#include <effects/Sky.h>
#include <effects/MultiColor.h>

#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <WeatherService.h>

#define LED_PORT 18
#define BRIGHTNESS 20
#define MATRIX_SIZE 16

#define WIFI_NAME "Xiaomi_1310"
#define WIFI_PASS "Nikita_2009"
#define WEATHER_API_KEY "b6d1ba500e374f5c82254122242409"
#define WEATHER_CITY "Kyiv"

WiFiUDP udp;
NTPClient ntpClient(udp, 3*3600);
WeatherService weatherService(WEATHER_API_KEY);

LedMatrix matrix;
MatrixEnabledComponent components[3];
MatrixClock matrixClock(0, 1);
MatrixTemperature matrixTemterature(0, 9);

RainEffect rainEffect;
SkyEffect skyEffect;
MultiColorEffect multiColorEffect;

unsigned long lastUpdateTime = 0;

void show() {
    matrix.clean();
    for (int i = 0; i < 3; i++) {
        if (components[i].enable) {
            components[i].component->draw(&matrix);
        }
    }
    FastLED.show();
};

void rainbow() {
  for (int i = 0; i < 256; i++)
  {
    fill_rainbow(matrix.getData(), MATRIX_SIZE*MATRIX_SIZE, i, MATRIX_SIZE-1);
      show();
      delay(1000/50);
  }
};

void test() {
  FastLED.show();
  delay(250);
  matrix.clean();
  for (uint8_t k=0; k<16; k++) {
    for (uint8_t j=0; j<16; j++) {
      CRGB color = CHSV(k*j, 255, 255);
      matrix.setDataXY(j, k, color);
      FastLED.show();
      delay(10);
    }
  }
  matrix.clean();
}

void waitConnect() {
  WiFi.begin(WIFI_NAME, WIFI_PASS);
  uint8_t p = 0;
  while (WiFi.status() != WL_CONNECTED) {
    matrix.setDataXY(p++, 0, CRGB::Magenta);
    FastLED.show();
    delay(50);
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

  matrix.init<MATRIX_SIZE, MATRIX_SIZE, LED_PORT>();
  matrix.setBrightness(BRIGHTNESS);

  test();

  waitConnect();

  matrixClock.setTime(00, 00);

  MatrixEnabledComponent c1;
  c1.enable = false;
  c1.component = &matrixClock;

  MatrixEnabledComponent c2;
  c2.enable = false;
  c2.component = &matrixTemterature;

  MatrixEnabledComponent rain_mec;
  rain_mec.enable = true;
//  rain_mec.component = &multiColorEffect; //skyEffect; //rainEffect;
  rain_mec.component = &skyEffect; //rainEffect;

  components[0] = rain_mec;
  components[1] = c1;
  components[2] = c2;
  
  matrix.clean();
}

void loop() {
  EVERY_N_MILLIS(100) {
    show();
    updateTime();
    updateWeather();
  }
}