#ifndef CONFIG
#define CONFIG

const int SERIAL_BAUD_RATE = 19200;
const int SERIAL_MAX_LENGTH = 200;
const float FRAMETIME = 1000 / 60;

const int BUTTONS_PIN = A0;
const int BUTTONS_COUNT = 5;
const int BUTTONS_ARRAY[5] = {1200, 2500, 3300, 4000, 4800};
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

const int OLED_MENU_COUNT = 9;
const int OLED_LAST_GRAPH = 7;
const char *OLED_MENU[OLED_MENU_COUNT] = {
    "Temperature",
    "Ventilation",
    "CPU Usage",
    "CPU Clock",
    "CPU Temp",
    "CPU Fan",
    "RAM",
    "Disk",
    "Motor Control",
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
    "mot_ctl",
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
    DISK_USAGE,
    MOTOR_CONTROL
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

const int CONTROL_STEP = 5;

const int LED_GREEN_PIN = 4;
const int LED_RED_PIN = 5;
const int LED_GREEN_TRIGGER = 20;
const int LED_RED_TRIGGER = 10;

#endif