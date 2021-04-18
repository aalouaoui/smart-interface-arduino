#include "AnalogButtons.h"
#include "tempMotor.h"

AnalogButtons analogButtons;
const int TEMP_PIN = A1;
const int MOTOR_PIN = 3;
int tempTarget = 20;

void setup()
{
    Serial.begin(9600);
    pinMode(MOTOR_PIN, OUTPUT);
    delay(1000);
}

void loop()
{
    // Input Handling
    int pressedButton = analogButtons.getState();
    // Read Sensor Data
    int currentTemp = readTemp(TEMP_PIN);
    int motorSpeed = adjustMotorSpeed(currentTemp, tempTarget, MOTOR_PIN);
    Serial.print(motorSpeed);
    Serial.print("% - ");
    Serial.println(currentTemp);
    // Read Serial Data

    // Update States

    // Output Handling
    // Render
    delay(500);
}