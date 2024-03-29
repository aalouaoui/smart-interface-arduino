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

int getLen(const char *arr)
{
    int i = 0;
    while (arr[i] != '\0')
        i++;
    return i;
}

int getXPos(const char *arr)
{
    return 127 - 6 * getLen(arr);
}

void concatValue(int number, char *unit, char *out, int len)
{
    String value = String(number) + String(unit);
    value.toCharArray(out, len);
}

int getIndexByKey(const char *arr[], const char *key, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (String(arr[i]) == String(key))
            return i;
    }
    return -1;
}

#endif