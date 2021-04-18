#ifndef AnalogButtons_H
#define AnalogButtons_H
#include "arduino.h"

class AnalogButtons
{
public:
    int lastButtonState;
    int getState();
};

#endif