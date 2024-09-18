# pragma once

#include <FastLED.h>

template<int WIGTH, int HEIGHT>
class LedMatrix {
    private:
       int wigth = WIGTH;
       int height = HEIGHT;
       CRGB data[WIGTH*HEIGHT];
    public:
        CRGB *getData() {
            return data;
        }

        CRGB getData(int index) {
            return data[index];
        };

        void setData(int index, CRGB value) {
            data[index] = value;
        };
        
        void draw() {};     
};