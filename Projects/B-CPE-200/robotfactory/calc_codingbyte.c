/*
** EPITECH PROJECT, 2024
** calc_codingbyte
** File description:
** codingbyte
*/

#include "include/robot_header.h"

int binary_to_decimal(char *binary)
{
    int res = 0;

    for (int i = 0; binary[i] != '\0'; i++) {
        res <<= 1;
        if (binary[i] == '1')
            res |= 1;
    }
    return (res);
}

int codingbyte(body_t *instru)
{
    char *p1 = (instru->param1 == -1 ? "00" : my_int_to_str(instru->param1));
    char *p2 = (instru->param2 == -1 ? "00" : my_int_to_str(instru->param2));
    char *p3 = (instru->param3 == -1 ? "00" : my_int_to_str(instru->param3));
    char *binary = NULL;

    if (instru->param1 == 1)
        p1 = my_strcat("0", "1");
    if (instru->param2 == 1)
        p2 = my_strcat("0", "1");
    if (instru->param3 == 1)
        p3 = my_strcat("0", "1");
    binary = my_strcat(my_strcat(p1, p2), my_strcat(p3, "00"));
    return (binary_to_decimal(binary));
}

int calc_codingbyte(body_t *instru, char **params, int beg)
{
    int coding = 0;

    instru->param1 = check_param_type(params[beg + 1]);
    instru->param2 = check_param_type(params[beg + 2]);
    instru->param3 = -1;
    if (params[beg + 2] != NULL)
        instru->param3 = check_param_type(params[beg + 3]);
    coding = codingbyte(instru);
    instru->param1 = my_getnbr(params[beg + 1], 0);
    if (params[beg + 2] != NULL)
        instru->param2 = my_getnbr(params[beg + 2], 0);
    if (params[beg + 2] != NULL)
        if (params[beg + 3] != NULL)
            instru->param3 = my_getnbr(params[beg + 3], 0);
    return (coding);
}
