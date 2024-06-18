/*
** EPITECH PROJECT, 2023
** call_put_octal
** File description:
** used to call put octal
*/

#include <stdarg.h>
#include "../../include/my.h"

int call_put_base(char *current_flag, va_list list, int i)
{
    for (int j = 0; current_flag[j] != '\0'; j++) {
        if (current_flag[j] == 'X')
            call_hexa_up(current_flag, list, i);
        if (current_flag[j] == 'x')
            call_hexa_down(current_flag, list, i);
        if (current_flag[j] == 'o')
            call_octal(current_flag, list, i);
        if (current_flag[j] == 'b')
            call_binary_down(current_flag, list, i);
        if (current_flag[j] == 'B')
            call_binary_up(current_flag, list, i);
    }
}
