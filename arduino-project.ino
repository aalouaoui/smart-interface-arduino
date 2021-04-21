#include "config.h"
#include "AnalogButtons.h"
#include "TempMotor.h"
#include "MyDisplay.h"

AnalogButtons analogButtons;
TempMotor tempMotor;
MyDisplay myDisplay;

void setup()
{
    Serial.begin(SERIAL_BAUD_RATE);
    tempMotor.begin();
    myDisplay.begin();
    delay(1000);
}

void loop()
{
    // Input Handling
    int pressedButton = analogButtons.getState();
    myDisplay.navigate(pressedButton);

    // Read Sensor Data
    int temp = tempMotor.updateTemp();
    int motorSpeed = tempMotor.updateSpeed();
    // Read Serial Data

    // Update States
    myDisplay.updateValue(tempMotor.tempPercent, TEMPERATURE);
    myDisplay.updateValueChar(tempMotor.tempText, TEMPERATURE);
    myDisplay.updateValue(motorSpeed, VENTILATION);
    myDisplay.updateValueChar(tempMotor.speedText, VENTILATION);

    // Render
    myDisplay.render();
    delay(FRAMETIME);
}