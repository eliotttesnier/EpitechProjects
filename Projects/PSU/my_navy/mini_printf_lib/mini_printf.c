/*
** EPITECH PROJECT, 2023
** mini_printf
** File description:
** desc
*/

#include "../include/navy_header.h"

int is_allowed(const char *format, int i)
{
    if (i != 0) {
        if (format[i - 1] == '%')
            return (1);
    }
    if (format[i + 1] == 'c')
        return (1);
    if (format[i + 1] == 's')
        return (1);
    if (format[i + 1] == 'i')
        return (1);
    if (format[i + 1] == 'd')
        return (1);
    if (format[i + 1] == '%')
        return (1);
}

int find_single_perctg(const char *format)
{
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%' && is_allowed(format, i) != 1) {
            return (84);
        }
    }
}

int get_flag(const char *format, va_list list, int *i)
{
    int len = 0;

    if (format[*i + 1] == 'd' || format[*i + 1] == 'i') {
        len = my_put_nbr(va_arg(list, int));
    }
    if (format[*i + 1] == 's') {
        len = my_putstr(va_arg(list, char *));
    }
    if (format[*i + 1] == 'c') {
        my_putchar(va_arg(list, int));
        len = len + 1;
    }
    if (format[*i + 1] == '%') {
        my_putchar('%');
        len = len + 1;
    }
    *i = *i + 1;
    return (len);
}

int mini_printf(const char *format, ...)
{
    va_list list;
    int len = 1;

    if (find_single_perctg(format) == 84) {
        return (84);
    }
    va_start(list, format);
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            len = len + get_flag(format, list, &i);
        } else {
            my_putchar(format[i]);
            len = len + 1;
        }
    }
    va_end(list);
    return (len);
}
