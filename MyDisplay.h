#ifndef MyDisplay_h
#define MyDisplay_h

#include <Arduino.h>
#include <lcdgfx.h>
#include <lcdgfx_gui.h>
#include "config.h"
#include "utils.h"

DisplaySH1106_128x64_SPI OLED(8, {-1, 10, 9, 0, -1, -1});
LcdGfxMenu mainMenu(OLED_MENU, OLED_MENU_COUNT);

class MyDisplay
{
public:
    int state = -1;
    int motorScreenState = 0;
    int values[OLED_MENU_COUNT][GRAPH_X_COUNT + 1] = {{0}};
    char valuesChar[OLED_MENU_COUNT][GRAPH_VALUE_MAX_LENGTH];

    void begin()
    {
        OLED.begin();
        OLED.setFixedFont(ssd1306xled_font6x8);
        OLED.clear();
        for (int i = 0; i < OLED_MENU_COUNT; i++)
        {
            strlcpy(valuesChar[i], "No Val", GRAPH_VALUE_MAX_LENGTH);
        }
    }

    void navigate(int button, TempMotor &tempMotor)
    {
        if (button == BTN_MENU)
        {
            state = -1;
            return;
        }

        int x = button == BTN_RIGHT ? 1 : (button == BTN_LEFT ? -1 : 0);
        int y = button == BTN_DOWN ? 1 : (button == BTN_UP ? -1 : 0);

        if (state <= OLED_LAST_GRAPH)
        {
            if (y == 1)
                mainMenu.down();
            else if (y == -1)
                mainMenu.up();
            state = x == 1 || state != -1 ? mainMenu.selection() : state;
        }

        else if (state == 8)
        {
            motorScreenState += y;
            motorScreenState = motorScreenState > 2 ? 0 : motorScreenState;
            motorScreenState = motorScreenState < 0 ? 2 : motorScreenState;

            if (motorScreenState == 0 && x != 0)
                tempMotor.autoMode = !tempMotor.autoMode;
            else if (motorScreenState == 1 && !tempMotor.autoMode)
                tempMotor.speed = constrain(tempMotor.speed + 5 * x, 0, 100);
            else if (motorScreenState == 2)
                tempMotor.targetTemp = constrain(tempMotor.targetTemp + 5 * x, 0, 100);
        }
    }

    void updateValue(int value, int where)
    {
        shiftArrayRight(values[where], GRAPH_X_COUNT + 1);
        values[where][0] = value;
    }

    void updateValueChar(char value[], int where)
    {
        strlcpy(valuesChar[where], value, GRAPH_VALUE_MAX_LENGTH);
    }

    void renderGraph()
    {
        char *text = valuesChar[state];
        OLED.printFixed(0, GRAPH_LABEL_Y, OLED_MENU[state], STYLE_NORMAL);
        OLED.printFixed(getXPos(text), GRAPH_LABEL_Y, text, STYLE_NORMAL);
        for (int i = 0; i < GRAPH_X_COUNT; i++)
        {
            int x1 = min(GRAPH_X_START - GRAPH_X_STEP * i, GRAPH_MAX_X);
            int y1 = min(GRAPH_MAX_Y - values[state][i] * GRAPH_Y_MULTIPLIER, GRAPH_MAX_Y);
            int x2 = min(x1 - GRAPH_X_STEP, GRAPH_MAX_X);
            int y2 = min(GRAPH_MAX_Y - values[state][i + 1] * GRAPH_Y_MULTIPLIER, GRAPH_MAX_Y);
            OLED.drawLine(x1, y1, x2, y2);
        }
    }

    void printControlLine(int line, const char *name, const char *value, bool inverted)
    {
        OLED.printFixed(0, line * 16, name, STYLE_NORMAL);
        if (inverted)
            OLED.invertColors();
        OLED.printFixed(getXPos(value), line * 16, value, STYLE_NORMAL);
        if (inverted)
            OLED.invertColors();
    }

    void renderMotorControl(TempMotor &tempMotor)
    {
        OLED.printFixed(getXPos("Motor Control") / 2, 4, "Motor Control", STYLE_NORMAL);

        const char *mode = tempMotor.autoMode ? "<AUTO>" : "<MANUEL>";
        printControlLine(1, "Mode:", mode, motorScreenState == 0);

        String speed = (tempMotor.autoMode ? "" : "<") + String(tempMotor.speedText) + (tempMotor.autoMode ? "" : ">");
        printControlLine(2, "Speed:", speed.c_str(), motorScreenState == 1);

        String tempTarget = "<" + String(tempMotor.targetTemp) + "C" + ">";
        printControlLine(3, "Temp Target:", tempTarget.c_str(), motorScreenState == 2);
    }

    void render(TempMotor &tempMotor)
    {
        OLED.clear();
        if (state == -1)
            mainMenu.show(OLED);
        else if (state <= OLED_LAST_GRAPH)
            renderGraph();
        else
            renderMotorControl(tempMotor);
    }
};

#endif