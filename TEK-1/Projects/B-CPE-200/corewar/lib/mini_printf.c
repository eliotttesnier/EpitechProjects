/*
** EPITECH PROJECT, 2024
** lib
** File description:
** mini_printf
*/

#include "../include/my_lib.h"

int mini_printf(char *format, ...)
{
    va_list list;

    va_start(list, format);
    for (int i = 0; format[i] != '\0'; i = i + 2) {
        if (format[i] == '%' && format[i + 1] == 'c')
            my_putchar(va_arg(list, int));
        if (format[i] == '%' && format[i + 1] == 's')
            my_putstr(va_arg(list, char *));
        if (format[i] == '%' && format[i + 1] == 'd')
            my_putnbr(va_arg(list, int));
        if (format[i] == '%' && format[i + 1] == '%')
            my_putchar('%');
        if (format[i] != '%' || (format[i + 1] != 's' && format[i + 1] != 'd'
            && format[i + 1] != 'c' && format[i + 1] != '%')) {
            my_putchar(format[i]);
            i--;
        }
    }
    return (0);
}
