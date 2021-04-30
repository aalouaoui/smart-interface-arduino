#include "config.h"
#include "AnalogButtons.h"
#include "TempMotor.h"
#include "MyDisplay.h"
#include "SerialHandler.h"

AnalogButtons analogButtons;
TempMotor tempMotor;
MyDisplay myDisplay;
SerialHandler serialHandler;

void setup()
{
    tempMotor.begin();
    myDisplay.begin();
    serialHandler.init();
    delay(1000);
}

int cycles = 0;

void loop()
{
    // Input Handling
    int pressedButton = analogButtons.getState();
    myDisplay.navigate(pressedButton);

    // Read Sensor Data
    if (cycles == 0)
    {
        tempMotor.updateTemp();
        tempMotor.updateSpeed();
    }
    cycles++;
    cycles %= 4;

    // Read Serial Data
    serialHandler.update(myDisplay);

    // Update States
    myDisplay.updateValue(tempMotor.tempPercent, TEMPERATURE);
    myDisplay.updateValueChar(tempMotor.tempText, TEMPERATURE);
    myDisplay.updateValue(tempMotor.speed, VENTILATION);
    myDisplay.updateValueChar(tempMotor.speedText, VENTILATION);

    // Render
    myDisplay.render();
    delay(FRAMETIME);
}

void serialEvent()
{
    serialHandler.listen();
}