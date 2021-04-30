#ifndef SerialHandler_h
#define SerialHandler_h
#include <ArduinoJson.h>
#include "config.h"

class SerialHandler
{
private:
    char inputString[SERIAL_MAX_LENGTH];
    int inputIndex = 0;
    bool stringComplete = false;

public:
    void init()
    {
        Serial.begin(SERIAL_BAUD_RATE);
    }
    void update()
    {
        if (!stringComplete)
            return;

        StaticJsonDocument<SERIAL_MAX_LENGTH> doc;
        DeserializationError error = deserializeJson(doc, inputString);

        if (error)
        {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
        }

        else
        {
            const char *type = doc["type"];
            Serial.println(type);
        }

        strlcpy(inputString, "", SERIAL_MAX_LENGTH);
        stringComplete = false;
    }
    void listen()
    {
        while (Serial.available())
        {
            char inChar = (char)Serial.read();
            inputString[inputIndex] = inChar;
            inputIndex++;
            if (inChar == '\n')
                stringComplete = true;
        }
    }
};

#endif