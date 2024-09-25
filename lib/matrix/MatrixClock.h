# pragma once

#include <MatrixComponent.h>
#include <PixelDigit.h>

class MatrixClock : public MatrixComponent {
    private:
        PixelDigit _digitPrint;
        int startPos;
        int _hours;
        int _minuts;

    public:
        MatrixClock() : MatrixComponent() {
            startPos = 0;
        };
        MatrixClock(int x, int y) : MatrixComponent(x, y) {
            startPos = x + (y-1) * MATRIX_SIZE;
        };
        void draw(CRGB *matrixData);
        void setTime(int hours, int minuts) {
            _hours = hours;
            _minuts = minuts;
        };
};

void MatrixClock::draw(CRGB *matrixData) {
    int hh = _hours/10;
    int lh = _hours%10;
    int hm = _minuts/10;
    int lm = _minuts%10;
    _digitPrint.draw(startPos + 4*0, posY, hh, matrixData, CRGB::SkyBlue);
    _digitPrint.draw(startPos + 4*1, posY, lh, matrixData, CRGB::SkyBlue);
    _digitPrint.draw(startPos + 4*2, posY, hm, matrixData, CRGB::YellowGreen);
    _digitPrint.draw(startPos + 4*3, posY, lm, matrixData, CRGB::YellowGreen);
};