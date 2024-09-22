#include <Arduino.h>

#include <SPI.h>
#include <Adafruit_SSD1306.h>
#include <LedMatrix.h>
#include <MatrixWeather.h>
#include <MatrixClock.h>

#define LED_PORT 18
#define BRIGHTNESS 150
#define MATRIX_SIZE 16

const int LINE_SIZE = MATRIX_SIZE*MATRIX_SIZE;

LedMatrix<MATRIX_SIZE, MATRIX_SIZE, LED_PORT> matrix;

MatrixWeather matrixWeatherSanny(8, 8);
//MatrixWeather matrixWeatherCloud(0, 8);
MatrixClock matrixClock(0, 0);

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

  //matrixWeatherCloud.setState(&cloud);
  matrixClock.setTime(12, 34);

  matrix.setBrightness(BRIGHTNESS);

  MatrixEnabledComponent c1;
  c1.enable = true;
  c1.component = &matrixWeatherSanny;

  MatrixEnabledComponent c2;
  c2.enable = true;
  c2.component = &matrixClock;

  matrix.addComponent(0, &c1);
  matrix.addComponent(1, &c2);
  matrix.show();
}

void loop() {
  rainbow();
}