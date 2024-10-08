# pragma once

#include <MatrixComponent.h>

struct WeatherState
{
    byte pic[8];
    CRGB color;
};

WeatherState sanny = {
    {
        0b00000000,
        0b00111100,
        0b01111110,
        0b11111111,
        0b11111111,
        0b01111110,
        0b00111100,
        0b00000000
    },
    CRGB::Yellow
};

WeatherState cloud = {
    {
        0b00000000,
        0b01111110,
        0b11111111,
        0b11111111,
        0b01111110,
        0b00101010,
        0b01010100,
        0b10101000
    },
    CRGB::Blue
};

class MatrixWeather : public MatrixComponent {
    private:
        int startPos;
        WeatherState *state = &sanny;
        float temperature;

    public:
        MatrixWeather() : MatrixComponent() {
            startPos = 0;
        };
        MatrixWeather(int x, int y) : MatrixComponent(x, y) {
            startPos = x + (y-1) * MATRIX_SIZE;
        };
        void draw(CRGB *matrixData);
        void setState(WeatherState *state);
        void setTemperature(float temperature) {};
};

void MatrixWeather::draw(CRGB *matrixData) {
    int i = startPos;
    byte *pic = state->pic;

    for (int r = 0; r < 8; r++) {
        byte row = pic[r];
        for (int b = 7; b >= 0; b--) {
            if (bitRead(row, b) == 1) {
                matrixData[i++] = state->color;        
            } else {
                matrixData[i++] = 0;
            }
        }
        i = i + MATRIX_SIZE - 8;
    }
};

void MatrixWeather::setState(WeatherState *state) {
    this->state = state;
};
