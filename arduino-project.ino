#include "config.h"
#include "AnalogButtons.h"
#include "TempMotor.h"
#include "MyDisplay.h"

AnalogButtons analogButtons;
TempMotor tempMotor;
MyDisplay myDisplay;

String inputString = "";
bool stringComplete = false;

void setup()
{
    Serial.begin(SERIAL_BAUD_RATE);
    inputString.reserve(200);
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
    tempMotor.updateTemp();
    tempMotor.updateSpeed();

    // Read Serial Data
    char serialType[inputString.length()];
    char serialPercent[inputString.length()];
    char serialText[GRAPH_VALUE_MAX_LENGTH];
    if (stringComplete)
    {
        bool sliceSuccess = sliceString(inputString, serialType, serialPercent, serialText);

        Serial.println(serialType);
        Serial.println(serialPercent);
        Serial.println(serialText);

        inputString = "";
        stringComplete = false;
    }

    // Update States
    myDisplay.updateValue(tempMotor.tempPercent, TEMPERATURE);
    myDisplay.updateValueChar(tempMotor.tempText, TEMPERATURE);
    myDisplay.updateValue(tempMotor.speed, VENTILATION);
    myDisplay.updateValueChar(tempMotor.speedText, VENTILATION);

    int screenToUpdate = -1;
    String percent = serialPercent;
    if (strcmp(serialType, "cpu") == 0)
        screenToUpdate = CPU_USAGE;

    if (screenToUpdate != -1)
    {
        myDisplay.updateValue(percent.toInt(), screenToUpdate);
        myDisplay.updateValueChar(serialText, screenToUpdate);
    }

    // Render
    myDisplay.render();
    delay(FRAMETIME);
}

void serialEvent()
{
    while (Serial.available())
    {
        char inChar = (char)Serial.read();
        inputString += inChar;
        if (inChar == '\n')
            stringComplete = true;
    }
}