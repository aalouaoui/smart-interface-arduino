#include "AnalogButtons.h"

int AnalogButtons::getState()
{
    int buttonState = 0;
    int value = map(analogRead(A0), 0, 1023, 0, 5000);

    if (value > 300 && value < 700)
        buttonState = 1;
    if (value > 1000 && value < 1400)
        buttonState = 2;
    if (value > 2300 && value < 2700)
        buttonState = 3;
    if (value > 3200 && value < 3600)
        buttonState = 4;
    if (value > 4600)
        buttonState = 5;

    int returnValue = 0;
    if (buttonState != 0 && lastButtonState == 0)
        returnValue = buttonState;
    lastButtonState = buttonState;
    return returnValue;
}