/*
** EPITECH PROJECT, 2023
** my_getnbr
** File description:
** returns a number sent as a string
*/

#include "../header.h"

int multi_res(char const *str, int i)
{
    int a = i;
    int mult = 1;

    while (i < my_strlen(str)) {
        if (str[a] < 48 || str[a] > 57) {
            i = my_strlen(str);
        } else {
            mult = mult * 10;
        }
        a = a + 1;
    }
    return (mult);
}

int my_getnbr2(char const *str, int i)
{
    int a = i;
    int result = 0;
    int mult = multi_res(str, a);

    if (mult < 0 || mult > 1000000000) {
        return (0);
    }
    while (a < my_strlen(str)) {
        if (str[a] < 48 || str[a] > 57) {
            i = my_strlen(str);
        } else {
            result = result + ((str[a] - 48) * mult);
            mult = mult / 10;
        }
        a = a + 1;
    }
    return (result / 10);
}

int my_getnbr(char const *str, int a)
{
    int i = a;
    int result = -1;
    int beg = 0;

    while (i < my_strlen(str)) {
        if (str[i] < 48 || str[i] > 57) {
            i = i + 1;
        } else {
            beg = i;
            result = my_getnbr2(str, i);
            i = my_strlen(str);
        }
    }
    if (beg != 0 && beg != a) {
        if (str[beg - 1] == '-') {
            result = result * (- 1);
        }
    }
    return (result);
}
