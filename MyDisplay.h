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
    int state = 0;
    void begin()
    {
        OLED.begin();
        OLED.setFixedFont(ssd1306xled_font6x8);
        OLED.clear();
    }

    void navigate(int button)
    {
        switch (button)
        {
        case BTN_DOWN:
            mainMenu.down();
            break;
        case BTN_UP:
            mainMenu.up();
            break;
        }
    }

    void render()
    {
        if (state == 0)
            mainMenu.show(OLED);
    }
};

#endif