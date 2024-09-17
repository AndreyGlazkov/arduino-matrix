#include "ChartData.h"
#include <Arduino.h>
#include <Adafruit_SSD1306.h>

class ChartComponent {
    private:
        int posX;
        int posY;
        int width;
        int height;
        ChartData *data;
        Adafruit_SSD1306 *display;

        void drawData();

    public:
        ChartComponent(int x, int y, int w, int h, ChartData *cd, Adafruit_SSD1306 *d);
        void draw();
};