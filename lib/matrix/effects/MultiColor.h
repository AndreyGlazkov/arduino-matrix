# pragma once

#include <MatrixComponent.h>

DEFINE_GRADIENT_PALETTE(multi_gp) {
    0, 50, 0, 0,
    84, 0, 50, 0,
    168, 0, 0, 50,
    255, 50, 0, 0
};

class MultiColorEffect : public MatrixComponent {
    private:
        CRGBPalette16 palette = multi_gp;
        uint8_t colorIndex = 0;
    public:
        void draw(LedMatrix* matrix);
};

void MultiColorEffect::draw(LedMatrix* matrix) {
    matrix->fillColor(ColorFromPalette(palette, colorIndex++));
};