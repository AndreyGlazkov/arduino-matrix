# pragma once

#include <MatrixComponent.h>

struct DigitalData
{
    byte pic[3];
};

const DigitalData digitals[10] = {
    //0
    {        
        0b01110101,
        0b01010101,
        0b01010111
    },
    //1
    {        
        0b00100110,
        0b00100010,
        0b00100111
    },
    //2
    {        
        0b01110101,
        0b00010010,
        0b01000111
    },
    //3
    {        
        0b01110101,
        0b00010010,
        0b00010111
    },
    //4
    {        
        0b01000101,
        0b01010111,
        0b00010001
    }
};

class MatrixClock : public MatrixComponent {
    private:
        int startPos;
        int _hours;
        int _minuts;
        void drawDigital(int x, int y, int digital, CRGB *matrixData, CRGB color);

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

void MatrixClock::drawDigital(int x, int y, int digital, CRGB *matrixData, CRGB color) {
    DigitalData data = digitals[digital];
    // for (int b = 0; b < 6; b++) {
    //     for (int r = 0; r < 4; r++) {
    //         // y*16+x - Розташування числа на матриці
    //         // b*16+r - Поточний піксель числа, який заповнюється на матриці
    //         // (int)(r*b/8) - Ділення з округленням вниз. Потрібно для визначення потрібного байту, який ми вичитуємо
    //         // r*b%8 - Ділення з остатком. Потрібно для визначення поточного біту, який ми вичитуємо
    //         if (bitRead(data.pic[b/2], r+4*b%2) == 1) {
    //             matrixData[y*16+x+b*16+r] = CRGB::White;
    //         } else {
    //             matrixData[y*16+x+b*16+r] = CRGB::Black;
    //         }
    //     }
    // }
    
    for (int b=0; b<3; b++) {
        byte bd = data.pic[b];
        for (int n=0; n<8; n++) {
            byte r = bitRead(bd, 7-n);
            int nr = n/4+1;
            int p = x + (b*2+nr)*MATRIX_SIZE + n%4;
            if (r == 1) {
                matrixData[p] = color;
            } else {
                matrixData[p] = CRGB::Black;
            }
        }
    }
}

void MatrixClock::draw(CRGB *matrixData) {
    for (int d = 0; d < 4; d++) {
        CRGB color = d < 2 ? CRGB::Blue : CRGB::Yellow;
        drawDigital(startPos + 4*d, posY, d, matrixData, color);
    }
};