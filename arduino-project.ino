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
    // Read Sensor Data
    int temp = tempMotor.updateTemp();
    int motorSpeed = tempMotor.updateSpeed();
    // Read Serial Data

    // Update States
    myDisplay.navigate(pressedButton);

    // Render
    myDisplay.render();
}