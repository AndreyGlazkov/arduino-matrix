#include <Arduino.h>

class ChartData {
    private:
        int currPos;
        int nextPos;
        int size;
        int *data;

    public:
        ChartData(int *data, int size);
        void setNext(int value);
        int getNext();
        bool hasNext();
        void toStart();
        int getSize();
};