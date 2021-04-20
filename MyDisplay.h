#ifndef MyDisplay_h
#define MyDisplay_h

#include <Arduino.h>
#include <lcdgfx.h>
#include <lcdgfx_gui.h>
#include "config.h"

DisplaySH1106_128x64_SPI OLED(8, {-1, 10, 9, 0, -1, -1});
LcdGfxMenu mainMenu(OLED_MENU, sizeof(OLED_MENU) / sizeof(char *));

class MyDisplay
{
public:
    int state = -1;
    bool shouldRefresh = true;
    void begin()
    {
        OLED.begin();
        OLED.setFixedFont(ssd1306xled_font6x8);
        OLED.clear();
    }

    void update(int button)
    {
        shouldRefresh |= button != 0;
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
        case BTN_MENU:
            state = -1;
            break;
        }
    }

    void render()
    {
        if (!shouldRefresh)
            return;
        OLED.clear();
        if (state == -1)
            mainMenu.show(OLED);
        else
        {
            char numChar[4];
            String(state).toCharArray(numChar, 4);
            OLED.printFixed(0, 8, numChar, STYLE_NORMAL);
        }
        shouldRefresh = false;
    }
};

#endif