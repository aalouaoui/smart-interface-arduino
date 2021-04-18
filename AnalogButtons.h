#ifndef AnalogButtons_H
#define AnalogButtons_H
#include "arduino.h"

class AnalogButtons
{
public:
    int lastButtonState = 0;
    int pin = A0;
    int valuesCount = 5;
    int values[5] = {500, 1200, 2500, 3400, 4800};
    int valueEpsilon = 200;

    int getState()
    {
        int buttonState = 0;
        int value = map(analogRead(pin), 0, 1023, 0, 5000);

        for (int i = 0; i < valuesCount; i++)
        {
            if (value > values[i] - valueEpsilon && value < values[i] + valueEpsilon)
            {
                buttonState = i + 1;
                break;
            }
        }

        int returnValue = buttonState != 0 && lastButtonState == 0 ? buttonState : 0;
        lastButtonState = buttonState;
        return returnValue;
    }
};

#endif