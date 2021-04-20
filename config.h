#ifndef CONFIG
#define CONFIG

const int SERIAL_BAUD_RATE = 9600;

const int BUTTONS_PIN = A0;
const int BUTTONS_COUNT = 5;
const int BUTTONS_ARRAY[5] = {500, 1200, 2500, 3400, 4800};
const int BUTTONS_EPSILON = 200;
enum BUTTONS_NAMES
{
    BTN_MENU = 1,
    BTN_LEFT,
    BTN_DOWN,
    BTN_UP,
    BTN_RIGHT
};

const int TEMP_PIN = A2;
const int TEMP_MIN = 0;
const int TEMP_MAX = 110;
const int TEMP_DIFF_MULTIPLIER = 3;
const int MOTOR_PIN = 3;
const int INITIAL_TEMP_TARGET = 20;

const char *OLED_MENU[] = {
    "Temperature",
    "Ventilation",
    "Processeur",
    "RAM",
    "Stockage",
    "Info",
    "Prix BTC",
};

#endif