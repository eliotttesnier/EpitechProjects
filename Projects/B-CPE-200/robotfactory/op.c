/*
** EPITECH PROJECT, 2024
** ROBOT
** File description:
** op
*/

#include "include/robot_header.h"

extern const op_t op_tab[] = {
    {"live", 1, {T_DIR}, 1, 10, "alive"},
    {"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load"},
    {"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store"},
    {"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition"},
    {"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction"},
    {"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
        "et (and  r1, r2, r3   r1&r2 -> r3"},
    {"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
        "ou  (or   r1, r2, r3   r1 | r2 -> r3"},
    {"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
        "ou (xor  r1, r2, r3   r1^r2 -> r3"},
    {"zjmp", 1, {T_DIR}, 9, 20, "jump if zero"},
    {"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
        "load index"},
    {"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
        "store index"},
    {"fork", 1, {T_DIR}, 12, 800, "fork"},
    {"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load"},
    {"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
        "long load index"},
    {"lfork", 1, {T_DIR}, 15, 1000, "long fork"},
    {"aff", 1, {T_REG}, 16, 2, "aff"},
    {0, 0, {0}, 0, 0, 0}
};

int is_a_register(char *param)
{
    if (my_strlen(param) > 3)
        return (0);
    if (param[0] == 'r' && IS_BTWN(my_getnbr(param, 1), 0, 17) == 1)
        return (1);
    return (0);
}

int is_a_direct(char *param)
{
    if (param[0] == '%' && param[1] != ' ')
        return (1);
    return (0);
}

int is_a_indirect(char *param)
{
    if (param[0] != '%' && param[0] != 'r')
        return (1);
    return (0);
}

int check_params_type(char **params, int scheme)
{
    int right_param = 0;
    int type_list = 0;

    for (int i = 0; op_tab[scheme].type[i] != '\0'; i++) {
        type_list = op_tab[scheme].type[i];
        if (type_list % 2 != 0) {
            right_param += is_a_register(params[i + 1]);
            type_list--;
        }
        if (type_list > 3) {
            right_param += is_a_indirect(params[i + 1]);
            type_list -= 4;
        }
        if (type_list > 0)
            right_param += is_a_direct(params[i + 1]);
        if (right_param > 0)
            return (1);
    }
    return (-1);
}

int check_all_params(char *instruction, int scheme)
{
    char **params = str_to_array(instruction, " ,");
    int nb_params = my_arrlen(params) - 1;

    if (nb_params != op_tab[scheme].nbr_args)
        return my_perror("Too many arguments given to the instruction.\n", -1);
    if (check_params_type(params, scheme) == -1)
        return my_perror("Invalid argument given to the instruction.\n", -1);
    return (1);
}
