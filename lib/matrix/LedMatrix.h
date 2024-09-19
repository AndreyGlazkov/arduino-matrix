# pragma once

#include <FastLED.h>

template<int WIGTH, int HEIGHT, int LED_PORT>
class LedMatrix {
    private:
       int wigth = WIGTH;
       int height = HEIGHT;
       CRGB data[WIGTH*HEIGHT];
       bool zigzag; 
    public:
        LedMatrix() {
            FastLED.addLeds<NEOPIXEL, LED_PORT>(data, WIGTH*HEIGHT);
            FastLED.setBrightness(30);
        };

        void setBrightness(int value) {
            FastLED.setBrightness(value);
        };

        void show() {
            FastLED.show();
        }

        CRGB *getData() {
            return data;
        };

        CRGB getData(int index) {
            return data[index];
        };

        void setData(int index, CRGB value) {
            data[index] = value;
        };

        void doZigzag() {
            CRGB serp[LINE_SIZE];
            for (int i = 0; i < LINE_SIZE; i++) {
                if (!isEven(i)) {
                serp[i] = matrix.getData(i);
                } else {
                serp[i+MATRIX_SIZE-1-(i%MATRIX_SIZE)*2] = matrix.getData(i);
                }
            }
            for (int i = 0; i < LINE_SIZE; i++) {
                matrix.setData(i, serp[i]);
            }
        }     
};