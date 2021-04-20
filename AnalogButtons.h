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
        int value = map(analogRead(BUTTONS_PIN), 0, 1023, 0, 5000);

        int buttonState = value < BUTTONS_EPSILON ? 0 : -1;

        for (int i = 0; i < BUTTONS_COUNT && buttonState == -1; i++)
        {
            if (value > (BUTTONS_ARRAY[i] - BUTTONS_EPSILON) && value < (BUTTONS_ARRAY[i] + BUTTONS_EPSILON))
                buttonState = i + 1;
        }

        if (buttonState == -1)
            return 0;

        bool isRisingEdge = lastButtonState == 0 && buttonState != 0;
        lastButtonState = buttonState;
        return isRisingEdge ? buttonState : 0;
    }
};

#endif