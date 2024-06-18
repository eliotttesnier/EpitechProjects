/*
** EPITECH PROJECT, 2023
** call_put_dot
** File description:
** used to call every times there's a dot
*/

#include <math.h>
#include <stdarg.h>
#include "../../include/my.h"

int call_put_dot(char *current_flag, va_list list, int i)
{
    int j = 0;

    while (current_flag[j] != '\0') {
        if (current_flag[j] == 'f' || current_flag[j] == 'F')
            return (call_put_float(current_flag, list, i));
        if (current_flag[j] == 'e' || current_flag[j] == 'E')
            return (call_put_scientific(current_flag, list, i));
        if (current_flag[j] == 'g' || current_flag[j] == 'G')
            return (call_put_g(current_flag, list, i));
        j += 1;
    }
}
