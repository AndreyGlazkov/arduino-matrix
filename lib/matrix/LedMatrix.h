# pragma once

#include <FastLED.h>

class LedMatrix {
    private:
       uint8_t wigth;
       uint8_t height;
       int matrixSize;
       CRGB* data;
       bool zigzag = true;

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
            for (int i=0; i<matrixSize; i++)
                data[i] = CRGB::Black;
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
            return getData(x + y*wigth);
        };

        void setDataXY(uint8_t x, uint8_t y, CRGB value) {
            setData(x + y*wigth, value);
        };

        bool isEven(int value) {
            int numRow = value / matrixSize;
            return numRow % 2 == 0;
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