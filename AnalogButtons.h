#ifndef AnalogButtons_H
#define AnalogButtons_H
#include "arduino.h"
#include "config.h"

class AnalogButtons
{
public:
    int lastButtonState = 0;
    int getState()
    {
        int buttonState = 0;
        int value = map(analogRead(BUTTONS_PIN), 0, 1023, 0, 5000);

        for (int i = 0; i < BUTTONS_COUNT; i++)
        {
            if (value > (BUTTONS_ARRAY[i] - BUTTONS_EPSILON) && value < (BUTTONS_ARRAY[i] + BUTTONS_EPSILON))
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