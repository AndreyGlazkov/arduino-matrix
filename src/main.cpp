#include <Arduino.h>

#include <SPI.h>
#include <Adafruit_SSD1306.h>
#include <LedMatrix.h>
//#include <MatrixComponents.h>
//#include <FastLED.h>

#define LED_PORT 18
#define BRIGHTNESS 50
#define MATRIX_SIZE 16

const int LINE_SIZE = MATRIX_SIZE*MATRIX_SIZE;

LedMatrix<MATRIX_SIZE, MATRIX_SIZE, LED_PORT> matrix;

MatrixWeather matrixWeatherSanny(8, 8);
MatrixWeather matrixWeatherCloud(0, 8);

bool isEven(int value) {
    int numRow = value / MATRIX_SIZE;
    return numRow % 2 == 0;
}

void rainbow() {
  for (int i = 0; i < 256; i++)
  {
    fill_rainbow(matrix.getData(), LINE_SIZE, i, MATRIX_SIZE-1);
      matrix.show();
      delay(1000/50);
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Start testing.......");
  matrix.setBrightness(BRIGHTNESS);
  matrix.addComponent(0, &matrixWeatherSanny);
  matrix.addComponent(1, &matrixWeatherCloud);
}

void loop() {
  rainbow();
}