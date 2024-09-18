#pragma once

#include <FastLED.h>

class PixelDigit {
    private:
        int width;
        int height;
    public:
        PixelDigit(int w, int h) {};
        void draw(int x, int y, CRGB * matrix) {};
};