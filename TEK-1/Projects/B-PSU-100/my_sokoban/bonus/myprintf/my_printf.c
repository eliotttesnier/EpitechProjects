/*
** EPITECH PROJECT, 2023
** myprintf
** File description:
** reproduces the function printf
*/

#include <stdlib.h>
#include <stdarg.h>
#include "include/my.h"

const char list_flag[17] = {'%', 'd', 'i', 's', 'c', 'o', 'u', 'x', 'X', 'f',
    'F', 'p', 'g', 'G', 'e', 'E', 'n'};
const int (*function[17]) (char *current_flag, va_list list, int i) = {
    call_putchar,
    call_put_nbr,
    call_put_nbr,
    call_putstr,
    call_putchar,
    call_put_base,
    call_put_unsigned,
    call_put_base,
    call_put_base,
    call_put_dot,
    call_put_dot,
    call_put_dot,
    call_put_dot,
    call_put_dot,
    call_put_dot,
    call_put_dot,
    call_put_in_var
};

int what_flag(char *current_flag, va_list list, int i, int len)
{
    char specifier = current_flag[len - 1];
    int flag = 0;

    for (int j = 0; list_flag[j] != '\0'; j++) {
        if (current_flag[len - 1] == list_flag[j]) {
            flag = j;
            return (flag);
        }
    }
}

int flag_to_str(const char *format, va_list list, int i, int len)
{
    int j = 0;
    char current_flag[len + 1];
    int flag = 0;

    for (j = 0 ; j < len ; j++) {
        current_flag[j] = format[i + j];
    }
    current_flag[len] = '\0';
    flag = what_flag(current_flag, list, i, len);
    if (flag == 0) {
        pfmy_putchar('%');
        return (1);
    }
    function[flag](current_flag, list, i);
}

int get_flag(const char *format, va_list list, int i)
{
    int j = 0;
    int len = i;

    i++;
    while (format[i] != '\0') {
        if (format[i] == list_flag[j]) {
            len = i - len;
            break;
        } else {
            j++;
        }
        if (j > 17) {
            j = 0;
            i++;
        }
    }
    flag_to_str(format, list, i - len + 1, len);
    return (len);
}

int my_printf(const char *format, ...)
{
    va_list list;
    int i = 0;
    int flag_len;

    va_start(list, format);
    while (format[i] != '\0') {
        if (format[i] == '%') {
            i = i + get_flag(format, list, i);
        } else {
            pfmy_putchar(format[i]);
        }
        i += 1;
    }
    va_end(list);
}
