#ifndef utils_h
#define utils_h
#include "config.h"

void shiftArrayRight(int *arr, int len)
{
    for (int i = len - 1; i > 0; i--)
    {
        arr[i] = arr[i - 1];
    }
}

int getLen(char *arr)
{
    int i = 0;
    while (arr[i] != '\0')
        i++;
    return i;
}

int getXPos(char *arr)
{
    return 127 - 6 * getLen(arr);
}

void concatValue(int number, char *unit, char *out, int len)
{
    String value = String(number) + String(unit);
    value.toCharArray(out, len);
}

#endif