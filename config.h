#ifndef CONFIG
#define CONFIG

const int SERIAL_BAUD_RATE = 9600;
const int SERIAL_MAX_LENGTH = 200;
const float FRAMETIME = 1000 / 15;

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

const int OLED_MENU_COUNT = 8;
const char *OLED_MENU[OLED_MENU_COUNT] = {
    "Temperature",
    "Ventilation",
    "CPU Usage",
    "CPU Clock",
    "CPU Temp",
    "CPU Fan",
    "RAM",
    "Disk Usage",
};
const char *MENU_ABBR[OLED_MENU_COUNT] = {
    "tmp",
    "vent",
    "cpu_usage",
    "cpu_frq",
    "cpu_tmp",
    "cpu_fan",
    "ram_usage",
    "disk_usage",
};
enum MENU_ITEMS
{
    TEMPERATURE = 0,
    VENTILATION,
    CPU_USAGE,
    CPU_CLOCK,
    CPU_TEMP,
    CPU_FAN,
    RAM,
    DISK_USAGE
};

const int OLED_CHAR_WIDTH = 4;

const float GRAPH_Y_MULTIPLIER = 0.5;
const int GRAPH_X_STEP = 8;
const int GRAPH_X_START = 114;
const int GRAPH_X_COUNT = GRAPH_X_START / GRAPH_X_STEP;
const int GRAPH_MAX_X = 123;
const int GRAPH_MAX_Y = 63;
const int GRAPH_LABEL_Y = 4;
const int GRAPH_VALUE_X = 100;
const int GRAPH_VALUE_MAX_LENGTH = 16;

#endif