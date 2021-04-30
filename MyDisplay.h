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
        if (button == BTN_MENU)
        {
            state = -1;
            return;
        }
        if (state == -1)
        {
            switch (button)
            {
            case BTN_DOWN:
                mainMenu.down();
                break;
            case BTN_UP:
                mainMenu.up();
                break;
            case BTN_RIGHT:
                state = mainMenu.selection();
                break;
            }
        }
        else if (state <= OLED_LAST_GRAPH)
        {
            switch (button)
            {
            case BTN_UP:
                mainMenu.up();
                state = mainMenu.selection();
                break;
            case BTN_DOWN:
                mainMenu.down();
                state = mainMenu.selection();
                break;
            }
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
        if (state == -1)
            mainMenu.show(OLED);
        else if (state <= OLED_LAST_GRAPH)
            renderGraph();
        else
            OLED.printFixed(0, 0, "Not Yet", STYLE_NORMAL);
    }
};

#endif