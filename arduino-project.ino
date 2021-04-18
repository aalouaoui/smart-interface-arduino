#include "config.h"
#include "AnalogButtons.h"
#include "TempMotor.h"

AnalogButtons analogButtons;
TempMotor tempMotor;

void setup()
{
    Serial.begin(SERIAL_BAUD_RATE);
    tempMotor.begin();
    delay(1000);
}

void loop()
{
    // Input Handling
    int pressedButton = analogButtons.getState();
    pressedButton &&Serial.println(pressedButton);
    // Read Sensor Data
    int temp = tempMotor.updateTemp();
    int motorSpeed = tempMotor.updateSpeed();
    Serial.print(temp);
    Serial.print("C - ");
    Serial.print(motorSpeed);
    Serial.println("%");
    // Serial.print(motorSpeed);
    // Serial.print("% - ");
    // Serial.println(currentTemp);
    // Read Serial Data

    // Update States

    // Output Handling
    // Render
    delay(1000);
}