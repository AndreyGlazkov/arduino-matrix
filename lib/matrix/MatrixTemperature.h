# pragma once

#include <MatrixComponent.h>
#include <Arduino.h>
#include <PixelDigit.h>

DEFINE_GRADIENT_PALETTE(temper_gp) {
    0, 102, 0, 102,
    100, 0, 0, 255,
    180, 0, 255, 0,
    255, 255, 0, 0
};

class MatrixTemperature : public MatrixComponent {
    private:
        PixelDigit _digitPrint;
        CRGBPalette16 palette = temper_gp;
        int8_t _temperature;

    public:
        MatrixTemperature();
        MatrixTemperature(uint8_t x, uint8_t y);
        void setTemperature(float temperature);
        void draw(LedMatrix* matrix);    
};

MatrixTemperature::MatrixTemperature() : MatrixComponent() {};

MatrixTemperature::MatrixTemperature(uint8_t x, uint8_t y) : MatrixComponent(x, y) {};

void MatrixTemperature::setTemperature(float temerature) {
    _temperature = temerature;
};

void MatrixTemperature::draw(LedMatrix* matrix) {
    char lev = _temperature < 0 ? '-' : '+';
    uint8_t t1 = abs8(_temperature)/10;    
    uint8_t t2 = abs8(_temperature)%10;
    CRGB color = ColorFromPalette(palette, map(_temperature, -20, 40, 0, 255));
    _digitPrint.drawSymbol(posX + 4*0, posY, lev, matrix, color);
    _digitPrint.draw(posX + 4*1, posY, t1, matrix, color);
    _digitPrint.draw(posX + 4*2, posY, t2, matrix, color);
    _digitPrint.drawSymbol(posX + 4*3, posY, 'c', matrix, color);
};