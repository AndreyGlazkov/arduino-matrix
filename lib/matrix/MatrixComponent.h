# pragma once

#include <Arduino.h>
#include <LedMatrix.h>

#define MATRIX_SIZE 16

class MatrixComponent {
    protected:
        int posX;
        int posY;

    public:
        MatrixComponent() {
            posX = 0;
            posY = 0;
        };
        MatrixComponent(int x, int y) {
            posX = x;
            posY = y;
        };
        virtual void draw(LedMatrix* matrix) {};    
};

struct MatrixEnabledComponent {
    bool enable;
    MatrixComponent *component;
};
