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
        uint8_t _startPos;
        int8_t _temperature;

    public:
        MatrixTemperature();
        MatrixTemperature(uint8_t x, uint8_t y);
        void setTemperature(float temperature);
        void draw(LedMatrix* matrix);    
};

MatrixTemperature::MatrixTemperature() : MatrixComponent() {
    _startPos = 0;
};

MatrixTemperature::MatrixTemperature(uint8_t x, uint8_t y) : MatrixComponent(x, y) {
    _startPos = x + (y-1) * MATRIX_SIZE;
};

void MatrixTemperature::setTemperature(float temerature) {
    _temperature = temerature;
};

void MatrixTemperature::draw(LedMatrix* matrix) {
    char lev = _temperature < 0 ? '-' : '+';
    uint8_t t1 = abs8(_temperature)/10;    
    uint8_t t2 = abs8(_temperature)%10;
    CRGB color = ColorFromPalette(palette, map(_temperature, -20, 40, 0, 255));
    _digitPrint.drawSymbol(_startPos + 4*0, posY, lev, matrix, color);
    _digitPrint.draw(_startPos + 4*1, posY, t1, matrix, color);
    _digitPrint.draw(_startPos + 4*2, posY, t2, matrix, color);
    _digitPrint.drawSymbol(_startPos + 4*3, posY, 'c', matrix, color);
};