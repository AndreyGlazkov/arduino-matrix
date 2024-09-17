#include "ChartData.h"

ChartData::ChartData(int *data, int size) {
    this->data = data;
    this->size = size;
    this->currPos = 30;
    this->nextPos = this->currPos + 1;
};

void ChartData::setNext(int value) {
    if (currPos >= size) {
        currPos = 0;
    }
    data[currPos] = value;
};

bool ChartData::hasNext() {
    if (nextPos == currPos) {
        return false;
    } else {
        return true;  
    }
};

int ChartData::getNext() {
    if (nextPos >= size) {
        nextPos = 0;
    }
    return data[nextPos++];
};

void ChartData::toStart() {
    nextPos = currPos;
};

int ChartData::getSize() {
    return size;
}