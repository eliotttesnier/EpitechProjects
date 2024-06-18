/*
** EPITECH PROJECT, 2023
** my.h
** File description:
** contains exposed funtons by my libmy.a
*/

#include <stdarg.h>

#ifndef TEST
    #define TEST

int call_hexa_up(char *current_flag, va_list list, int i);
char what_char_it(char *current_flag);
int plus_sign(char *current_flag, int nb);
int display_hexa(void *ptr);
int call_binary_up(char *current_flag, va_list list, int i);
int call_binary_down(char *current_flag, va_list list, int i);
int call_octal(char *current_flag, va_list list, int i);
int call_hexa_down(char *current_flag, va_list list, int i);
int call_put_adress(char *current_flag, va_list list, int i);
int call_put_unsigned(char *current_flag, va_list list, int i);
int call_put_in_var(char *current_flag, va_list list, int i);
int call_put_g(char *current_flag, va_list list, int i);
int call_put_scientific(char *current_flag, va_list list, int i);
int call_put_base(char *fcurrent_flag, va_list list, int i);
int call_put_float(char *current_flag, va_list list, int i);
int call_getnbr(char *current_flag, va_list list, int i);
int call_put_nbr(char *current_flag, va_list list, int i);
int call_putchar(char *current_flag, va_list list, int i);
int call_putstr(char *current_flag, va_list list, int i);
int call_put_dot(char *current_flag, va_list list, int i);
int my_printf(const char *format, ...);
int my_put_g(double nb, int decimals, char cap);
void pfmy_putchar(char);
int pfmy_put_nbr(int);
int my_len_nbr(int);
int pfmy_putstr(char const *str);
int my_len_str(char const *str);
int pfmy_strlen(char const *str);
int pfmy_getnbr(char const *str, int a);
int pfmy_compute_power_rec(int, int);
int my_put_octal(unsigned int nb);
int my_len_octal(unsigned int nb);
int my_put_hexa(unsigned int nb, int cap);
int my_len_hexa(unsigned int nb, int cap);
int my_put_binary(unsigned int nb);
int my_len_binary(unsigned int nb);
int my_put_float(double nb, int decimals);
int my_g_float(float nb, int decimals);
int my_len_float(double nb, int decimals);
int my_put_scientific(double nb, int decimals, char cap, int alt);
int my_len_scientific(float nb, int decimals, char cap);
int my_put_unsigned(unsigned int nb);
int my_len_unsigned(unsigned int nb);

#endif /* TEST */
