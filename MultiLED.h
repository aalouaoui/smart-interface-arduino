#ifndef MULTILED_H
#define MULTILED_H
#include "config.h"

class MultiLED
{
public:
    void init()
    {
        pinMode(LED_RED_PIN, OUTPUT);
        pinMode(LED_GREEN_PIN, OUTPUT);
    }

    void update(int temp, int targetTemp)
    {
        int tempDelta = temp - targetTemp;
        digitalWrite(LED_RED_PIN, tempDelta > LED_RED_TRIGGER ? HIGH : LOW);
        digitalWrite(LED_GREEN_PIN, tempDelta < LED_GREEN_TRIGGER ? HIGH : LOW);
    }
};

#endif