#ifndef MyDisplay_h
#define MyDisplay_h

#include <Arduino.h>
#include <lcdgfx.h>
#include <lcdgfx_gui.h>
#include "config.h"
#include "utils.h"

DisplaySH1106_128x64_SPI OLED(8, {-1, 10, 9, 0, -1, -1});
LcdGfxMenu mainMenu(OLED_MENU, sizeof(OLED_MENU) / sizeof(char *));

class MyDisplay
{
public:
    int state = -1;
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

    void navigate(int button)
    {
        switch (button)
        {
        case BTN_DOWN:
            mainMenu.down();
            if (state != -1)
                state = mainMenu.selection();
            break;
        case BTN_UP:
            mainMenu.up();
            if (state != -1)
                state = mainMenu.selection();
            break;
        case BTN_RIGHT:
            state = mainMenu.selection();
            break;
        case BTN_MENU:
            state = -1;
            break;
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

    void render()
    {
        OLED.clear();
        state == -1 ? mainMenu.show(OLED) : renderGraph();
    }
};

#endif