#include <Arduino.h>

#include <SPI.h>
#include <Adafruit_SSD1306.h>
#include <MatrixComponents.h>
//#include <FastLED.h>

#define LED_PORT 18
#define BRIGHTNESS 50

const int LINE_SIZE = MATRIX_SIZE*MATRIX_SIZE;
CRGB matrixData[LINE_SIZE];

MatrixWeather matrixWeatherSanny(8, 8, matrixData);
MatrixWeather matrixWeatherCloud(0, 8, matrixData);

bool isEven(int value) {
    int numRow = value / MATRIX_SIZE;
    return numRow % 2 == 0;
}

void doZigzag() {
  CRGB serp[LINE_SIZE];
  for (int i = 0; i < LINE_SIZE; i++) {
    if (!isEven(i)) {
      serp[i] = matrixData[i];
    } else {
      serp[i+MATRIX_SIZE-1-(i%MATRIX_SIZE)*2] = matrixData[i];
    }
  }
  for (int i = 0; i < LINE_SIZE; i++) {
    matrixData[i] = serp[i];
  }
}


void rainbow() {
  for (int i = 0; i < 256; i++)
  {
    fill_rainbow(matrixData, LINE_SIZE, i, MATRIX_SIZE-1);
      doZigzag();
      FastLED.show();
      delay(1000/50);
  }
}


void setup() {
  Serial.begin(9600);
  Serial.println("Start testing.......");
  FastLED.addLeds<NEOPIXEL, LED_PORT>(matrixData, LINE_SIZE);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  rainbow();
}