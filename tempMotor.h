#ifndef tempMotor_h
#define tempMotor_h
#include "arduino.h"

int readTemp(int pin)
{
    int value = analogRead(pin);
    return map(value, 0, 1023, 0, 110);
}

int adjustMotorSpeed(int temp, int targetTemp, int pin)
{
    int speed = (temp - targetTemp) * 10;
    if (speed > 250)
        speed = 250;
    if (speed < 10)
        speed = 0;
    // analogWrite(pin, speed);
    return speed * 0.4;
}

#endif