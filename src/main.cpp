#include <Arduino.h>

#include <SPI.h>
#include <Adafruit_SSD1306.h>
#include <MatrixComponents.h>
//#include <FastLED.h>

CRGB matrixData[MATRIX_SIZE*MATRIX_SIZE];

MatrixWeather matrixWeatherSanny(8, 8, matrixData);
MatrixWeather matrixWeatherCloud(0, 8, matrixData);

void setup() {
  Serial.begin(9600);
  Serial.println("Start testing.......");

  matrixWeatherSanny.draw();

  matrixWeatherCloud.setState(&cloud);
  matrixWeatherCloud.draw();

  FastLED.addLeds<NEOPIXEL, 18>(matrixData, MATRIX_SIZE*MATRIX_SIZE);
  FastLED.show();
}

void loop() {
  // put your main code here, to run repeatedly:
}