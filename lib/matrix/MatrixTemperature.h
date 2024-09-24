# pragma once

#include <Arduino.h>

class MatrixTemperature {
    private:
        float* _temperature;

    public:
        void setTemperature(float* temperature);    
};