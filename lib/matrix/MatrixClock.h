# pragma once

#include <MatrixComponent.h>
#include <PixelDigit.h>

class MatrixClock : public MatrixComponent {
    private:
        PixelDigit _digitPrint;
        int _hours;
        int _minuts;

    public:
        MatrixClock() : MatrixComponent() {};
        MatrixClock(int x, int y) : MatrixComponent(x, y) {};
        void draw(LedMatrix *matrix);
        void setTime(int hours, int minuts) {
            _hours = hours;
            _minuts = minuts;
        };
};

void MatrixClock::draw(LedMatrix *matrix) {
    int hh = _hours/10;
    int lh = _hours%10;
    int hm = _minuts/10;
    int lm = _minuts%10;
    _digitPrint.draw(4*0, posY, hh, matrix, CRGB::SkyBlue);
    _digitPrint.draw(4*1, posY, lh, matrix, CRGB::SkyBlue);
    _digitPrint.draw(4*2, posY, hm, matrix, CRGB::YellowGreen);
    _digitPrint.draw(4*3, posY, lm, matrix, CRGB::YellowGreen);
};