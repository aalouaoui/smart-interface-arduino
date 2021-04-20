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

#endif