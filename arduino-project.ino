#include "config.h"
#include "AnalogButtons.h"
#include "tempMotor.h"

AnalogButtons analogButtons;
int tempTarget = INITIAL_TEMP_TARGET;

void setup()
{
    Serial.begin(SERIAL_BAUD_RATE);
    pinMode(MOTOR_PIN, OUTPUT);
    delay(1000);
}

void loop()
{
    // Input Handling
    int pressedButton = analogButtons.getState();
    pressedButton &&Serial.println(pressedButton);
    // Read Sensor Data
    int currentTemp = readTemp(TEMP_PIN);
    int motorSpeed = adjustMotorSpeed(currentTemp, tempTarget, MOTOR_PIN);
    // Serial.print(motorSpeed);
    // Serial.print("% - ");
    // Serial.println(currentTemp);
    // Read Serial Data

    // Update States

    // Output Handling
    // Render
    delay(50);
}