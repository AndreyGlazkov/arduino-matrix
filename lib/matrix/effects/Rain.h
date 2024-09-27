# pragma once

#include <MatrixComponent.h>

#define RAIN_HEIGHT 5 //1-4

DEFINE_GRADIENT_PALETTE(rain_gp) {
    0, 0, 0, 255,
    100, 0, 50, 50,
    255, 0, 0, 0 
};

class RainEffect : public MatrixComponent {
    private:
        CRGBPalette16 palette = rain_gp;
        uint8_t rainMatrix[MATRIX_SIZE];
        void clean();
    public:
        RainEffect() : MatrixComponent(0, 0) {
            clean();
        };
        void draw(LedMatrix* matrix);
};

void RainEffect::clean() {
    for (uint8_t i=0; i<MATRIX_SIZE; i++) {
        rainMatrix[i] = NULL;
    }
}

void RainEffect::draw(LedMatrix* matrix) {
    uint8_t w = matrix->getWigth();
    uint8_t h = matrix->getHeight();

    uint8_t newRainLineNum = random8(w-1);

    for (uint8_t j=0; j<MATRIX_SIZE; j++) {
    // calc altitude rain line 
        if (rainMatrix[j] == NULL) {
            if (random8(50) == 0) {
                rainMatrix[j] = 1;
            }
        } else {
            rainMatrix[j] = rainMatrix[j] + 1;
            if (rainMatrix[j] == h) {
                rainMatrix[j] = NULL;
            } 
        }
    // draw into matrix
        uint8_t l = rainMatrix[j];
        if (l != NULL) {
            for (uint8_t i=0; i<RAIN_HEIGHT; i++) {
                int y = l-i;
                if (y >= 0) {
                    CRGB color = ColorFromPalette(palette, i*50);
                    matrix->setDataXY(j, y, color);
                }
            }
        }
        //Serial.println("rainMatrix[" + String(j) + "] = " + rainMatrix[j]);
    }
}