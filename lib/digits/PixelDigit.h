#pragma once

#include <FastLED.h>

#ifndef MATRIX_SIZE
#define MATRIX_SIZE 16
#endif

struct DigitalData
{
    byte pic[3];
};

const DigitalData digitals[] {
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
    },
    //5
    {        
        0b01110100,
        0b01110001,
        0b01010111
    },
    //6
    {        
        0b01110100,
        0b01110101,
        0b01010111
    },
    //7
    {        
        0b01110001,
        0b00100100,
        0b01000100
    },
    //8
    {        
        0b01110101,
        0b01110101,
        0b01010111
    },
    //9
    {        
        0b01110101,
        0b01010111,
        0b00010111
    },
    //+
    {        
        0b00000000,
        0b00100111,
        0b00100000
    },
    //-
    {        
        0b00000000,
        0b00000111,
        0b00000000
    },
    //.
    {        
        0b00000000,
        0b00000000,
        0b00001000
    },
    //c
    {        
        0b01100100,
        0b01100000,
        0b00000000
    }
};

class PixelDigit {
    public:
        PixelDigit() {};
        void draw(int x, int y, short digital, CRGB* matrix, CRGB color);
        void drawSymbol(int x, int y, char symbol, CRGB* matrix, CRGB color);
};

void PixelDigit::draw(int x, int y, short digital, CRGB* matrix, CRGB color) {
    DigitalData data = digitals[digital];
    for (int b=0; b<3; b++) {
        byte bd = data.pic[b];
        for (int n=0; n<8; n++) {
            byte r = bitRead(bd, 7-n);
            int nr = n/4+1;
            int p = x + (b*2+nr)*MATRIX_SIZE + n%4;
            if (r == 1) {
                matrix[p] = color;
            } else {
                matrix[p] = CRGB::Black;
            }
        }
    }
};

void PixelDigit::drawSymbol(int x, int y, char symbol, CRGB* matrix, CRGB color) {
    int digital = 10;
    switch (symbol)
    {
        case '+':
            digital = 10;
            break;
        case '-':
            digital = 11;
            break;
        case '.':
            digital = 12;
            break;        
        case 'c':
            digital = 13;
            break;
        
        default:
            break;
    }
    draw(x, y, digital, matrix, color);
};