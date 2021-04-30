#ifndef SerialHandler_h
#define SerialHandler_h
#include <ArduinoJson.h>
#include "config.h"
#include "utils.h"

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
    void update(MyDisplay &display)
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
            const char *dataType = doc["type"];
            if (String(dataType) == String("graph"))
            {
                const char *name = doc["name"];
                const int newValue = doc["val"];
                char *label = doc["label"];
                int stateIndex = getIndexByKey(MENU_ABBR, name, OLED_MENU_COUNT);
                if (stateIndex != -1)
                {
                    display.updateValue(newValue, stateIndex);
                    display.updateValueChar(label, stateIndex);
                }
            }
        }

        strlcpy(inputString, "", SERIAL_MAX_LENGTH);
        stringComplete = false;
        inputIndex = 0;
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