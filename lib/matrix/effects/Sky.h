# pragma once

#include <MatrixComponent.h>

class SkyEffect : public MatrixComponent {
    private:
        uint16_t x = 0;
    public:
        void draw(LedMatrix* matrix);
};

void SkyEffect::draw(LedMatrix* matrix) {
    x+=10;
    for (uint8_t i=0; i<MATRIX_SIZE; i++) {
        for (uint8_t j=0; j<MATRIX_SIZE; j++) {
            uint8_t c = inoise8(15*i, 60*j, x);
            Serial.println(c);
            matrix->setDataXY(i, j, CHSV(map(c, 50, 200, 150, 230), 255-c, 255));
        };
    };
};