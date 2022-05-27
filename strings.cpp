#include <string.h>
#include <Arduino.h>
#include "strings.h"

void getPar(char *str, char *param, int number) // number is number of elemet of massage (starts from 1)
{
    int i = 1;
    char *dot = strchr(str, ',');
    char *temp = dot;
    strncpy(param, str, 2);

    while (i < number)
    {
        temp++;
        dot = strchr(temp, ',');
        strncpy(param, temp, 4);
        temp = dot;
        i++;
    }
}
