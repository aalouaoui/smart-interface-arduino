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

bool sliceString(String inputString, char *serialType, char *serialPercent, char *serialText)
{
    int del1 = inputString.indexOf(";");
    int del2 = inputString.indexOf(";", del1 + 1);

    if (del1 == -1 || del2 == -1 || del2 - del1 < 2)
        return false;

    inputString.substring(0, del1).toCharArray(serialType, del1 + 1);
    inputString.substring(del1 + 1, del2).toCharArray(serialPercent, del2 - del1 + 1);
    inputString.substring(del2 + 1, inputString.length() - 1).toCharArray(serialText, GRAPH_VALUE_MAX_LENGTH);

    return true;
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