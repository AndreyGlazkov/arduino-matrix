# pragma once

#include <FastLED.h>

class LedMatrix {
    private:
        uint8_t wigth;
        uint8_t height;
        int matrixSize;
        CRGB* data;
        bool zigzag = true;

        bool isEven(int value) {
            int numRow = value / matrixSize;
            return numRow % 2 == 0;
        };

    public:
        template<uint8_t WIGTH, uint8_t HEIGHT, uint8_t LED_PORT>
        void init() {
            wigth = WIGTH;
            height = HEIGHT;
            matrixSize = WIGTH*HEIGHT;
            data = new CRGB[matrixSize];
            FastLED.addLeds<NEOPIXEL, LED_PORT>(data, matrixSize);
            FastLED.setBrightness(30);
        };

        void setBrightness(int value) {
            FastLED.setBrightness(value);
        };

        void clean() {
            FastLED.clear();
        };

        void fillColor(CRGB color) {
            for (int i=0; i<matrixSize; i++) {
                data[i] = color;
            }
        };

        uint8_t getWigth() {
            return wigth;
        };

        uint8_t getHeight() {
            return height;
        };

        CRGB *getData() {
            return data;
        };

        CRGB getData(uint8_t index) {
            return data[index];
        };

        void setData(uint8_t index, CRGB value) {
            data[index] = value;
        };

        CRGB getDataXY(uint8_t x, uint8_t y) {
            if (zigzag && y%2 == 0) {
                return getData((wigth-1-x) + y*wigth);
            } else {
                return getData(x + y*wigth);
            }
        };

        void setDataXY(uint8_t x, uint8_t y, CRGB value) {
            if (zigzag && y%2 == 0) {
                setData((wigth-1-x) + y*wigth, value);
            } else {
                setData(x + y*wigth, value);
            }    
        };

        void doZigzag() {
            CRGB serp[matrixSize];
            for (int i = 0; i < matrixSize; i++) {
                if (!isEven(i)) {
                serp[i] = getData(i);
                } else {
                serp[i+matrixSize-1-(i%matrixSize)*2] = getData(i);
                }
            }
            for (int i = 0; i < matrixSize; i++) {
                setData(i, serp[i]);
            }
        };     
}; 