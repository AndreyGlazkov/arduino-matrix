# pragma once

#include <MatrixComponent.h>
#include <Arduino.h>
#include <PixelDigit.h>

class MatrixTemperature : public MatrixComponent {
    private:
        PixelDigit _digitPrint;
        CRGB palette[10] = {
            CRGB::Red,
            CRGB::Orange,
            CRGB::YellowGreen,
            CRGB::Yellow,
            CRGB::Green,
            CRGB::DarkSeaGreen,
            CRGB::Blue,
            CRGB::DarkBlue,
            CRGB::Coral,
            CRGB::Chocolate
        };
        int _startPos;
        float _temperature;

    public:
        MatrixTemperature();
        MatrixTemperature(int x, int y);
        void setTemperature(float temperature);
        void draw(CRGB *matrixData);    
};

MatrixTemperature::MatrixTemperature() : MatrixComponent() {
    _startPos = 0;
};

MatrixTemperature::MatrixTemperature(int x, int y) : MatrixComponent(x, y) {
    _startPos = x + (y-1) * MATRIX_SIZE;
};

void MatrixTemperature::setTemperature(float temerature) {
    _temperature = temerature;
};

void MatrixTemperature::draw(CRGB *matrixData) {
    char lev = _temperature < 0 ? '-' : '+';
    int t1 = (int)_temperature/10;    
    int t2 = (int)_temperature%10;
    int t3 = (int)_temperature*10%10;
    CRGB color = palette[t1];
    _digitPrint.drawSymbol(_startPos + 4*0, posY, lev, matrixData, color);
    _digitPrint.draw(_startPos + 4*1, posY, t1, matrixData, color);
    _digitPrint.draw(_startPos + 4*2, posY, t2, matrixData, color);
    _digitPrint.drawSymbol(_startPos + 4*3, posY, lev, matrixData, CRGB::Green);
    _digitPrint.draw(_startPos + 4*3+1, posY, t3, matrixData, color);
};