void setup()
{
    Serial.begin(9600);
    delay(1000);
}

int lastButtonState = 0;

int getAnalogButton()
{
    // 0.5V 1.2V 2.5V 3.4V 4.9V
    int value = map(analogRead(A0), 0, 1023, 0, 5000);

    if (value > 300 && value < 700)
        return 1;
    if (value > 1000 && value < 1400)
        return 2;
    if (value > 2300 && value < 2700)
        return 3;
    if (value > 3200 && value < 3600)
        return 4;
    if (value > 4600)
        return 5;

    return 0;
}

void loop()
{
    // Input Handling
    int buttonState = getAnalogButton();
    if (buttonState != 0 && lastButtonState == 0)
    {
        Serial.println(buttonState);
    }
    lastButtonState = buttonState;
    delay(10);
    // Read Sensor Data
    // Read Serial Data

    // Update States

    // Output Handling
    // Render
}