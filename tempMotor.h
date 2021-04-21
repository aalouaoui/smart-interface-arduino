#ifndef TempMotor_h
#define TempMotor_h
#include "arduino.h"
#include "utils.h"

class TempMotor
{
public:
    int temp;
    int tempPercent;
    char tempText[10];
    int targetTemp = INITIAL_TEMP_TARGET;
    int speed;
    char speedText[10];
    bool autoMode = true;

    void begin()
    {
        pinMode(MOTOR_PIN, OUTPUT);
    }

    int updateTemp()
    {
        int value = analogRead(TEMP_PIN);
        temp = map(value, 0, 1023, TEMP_MIN, TEMP_MAX);
        tempPercent = map(value, 0, 1023, 0, 100);
        concatValue(temp, "C", tempText, 10);
        return temp;
    }

    int updateSpeed()
    {
        if (autoMode)
        {
            speed = (temp - targetTemp) * TEMP_DIFF_MULTIPLIER;
            speed = constrain(speed, 0, 100);
        }
        concatValue(speed, "%", speedText, 10);
        analogWrite(MOTOR_PIN, speed * 2.5);
        return speed;
    }
};

#endif