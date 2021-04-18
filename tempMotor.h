#ifndef TempMotor_h
#define TempMotor_h
#include "arduino.h"

class TempMotor
{
public:
    int temp;
    int targetTemp = INITIAL_TEMP_TARGET;
    int speed;
    bool autoMode = true;

    void begin()
    {
        pinMode(MOTOR_PIN, OUTPUT);
    }

    int updateTemp()
    {
        int value = analogRead(TEMP_PIN);
        temp = map(value, 0, 1023, TEMP_MIN, TEMP_MAX);
        return temp;
    }

    int updateSpeed()
    {
        if (autoMode)
        {
            speed = (temp - targetTemp) * TEMP_DIFF_MULTIPLIER;
            if (speed > 100)
                speed = 100;
            if (speed < 0)
                speed = 0;
        }
        analogWrite(MOTOR_PIN, speed * 2.5);
        return speed;
    }
};

#endif