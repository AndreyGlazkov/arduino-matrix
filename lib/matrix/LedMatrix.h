# pragma once

#include <FastLED.h>
#include <MatrixComponent.h>

template<int WIGTH, int HEIGHT, int LED_PORT>
class LedMatrix {
    private:
       int wigth = WIGTH;
       int height = HEIGHT;
       CRGB data[WIGTH*HEIGHT];
       bool zigzag = true;
       MatrixEnabledComponent components[2];

    public:
        LedMatrix() {
            FastLED.addLeds<NEOPIXEL, LED_PORT>(data, WIGTH*HEIGHT);
            FastLED.setBrightness(30);
        };

        void setBrightness(int value) {
            FastLED.setBrightness(value);
        };

        void addComponent(int index, MatrixEnabledComponent *component) {
            components[index] = *component;
        };

        void delComponent(int index) {
            addComponent(index, NULL);
        };

        void show() {
            for (int i = 0; i < 2; i++) {
                if (components[i].enable) {
                    components[i].component->draw(data);
                }
            }
            if (zigzag) {
                doZigzag();
            }
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

        bool isEven(int value) {
            int numRow = value / MATRIX_SIZE;
            return numRow % 2 == 0;
        }

        void doZigzag() {
            CRGB serp[WIGTH*HEIGHT];
            for (int i = 0; i < WIGTH*HEIGHT; i++) {
                if (!isEven(i)) {
                serp[i] = getData(i);
                } else {
                serp[i+MATRIX_SIZE-1-(i%MATRIX_SIZE)*2] = getData(i);
                }
            }
            for (int i = 0; i < WIGTH*HEIGHT; i++) {
                setData(i, serp[i]);
            }
        }     
};