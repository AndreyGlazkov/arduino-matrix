#include "ChartComponent.h"

ChartComponent::ChartComponent(int x, int y, int w, int h, ChartData *cd, Adafruit_SSD1306 *d) {
    posX = x;
    posY = y;
    width = w;
    height = h;
    data = cd;
    display = d;
};

void ChartComponent::draw() {
    display->drawFastHLine(posX, posY+height, width, SSD1306_WHITE);
    display->drawFastVLine(posX, posY, height, SSD1306_WHITE);
    drawData();
}

void ChartComponent::drawData() {
    int xx = posX + 1;
    data->toStart();
    do {
      int value = data->getNext();  
      display->drawFastVLine(xx++, height-value, value, SSD1306_WHITE);  
    } while (data->hasNext());
}