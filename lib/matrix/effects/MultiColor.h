# pragma once

#include <MatrixComponent.h>

DEFINE_GRADIENT_PALETTE(multi_gp) {
    0, 255, 0, 0,
    84, 0, 255, 0,
    168, 0, 0, 255,
    255, 255, 0, 0
};

class MultiColorEffect : public MatrixComponent {
    private:
        CRGBPalette16 palette = multi_gp;
        uint8_t colorIndex = 0;
    public:
        void draw(LedMatrix* matrix);
};

void MultiColorEffect::draw(LedMatrix* matrix) {
    matrix->fillColor(ColorFromPalette(palette, colorIndex));
};