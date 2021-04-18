#include "AnalogButtons.h"

AnalogButtons analogButtons;

void setup()
{
    Serial.begin(9600);
    delay(1000);
}

void loop()
{
    // Input Handling
    int button = analogButtons.getState();
    if (button != 0)
        Serial.println(button);
    delay(10);
    // Read Sensor Data
    // Read Serial Data

    // Update States

    // Output Handling
    // Render
}