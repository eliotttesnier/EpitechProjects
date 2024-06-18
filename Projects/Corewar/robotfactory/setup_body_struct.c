/*
** EPITECH PROJECT, 2024
** ROBOT
** File description:
** setup_header_struct
*/

#include "include/robot_header.h"

static void fill_size_params(body_t *instru, char **params, int beg)
{
    if (params[beg + 3] == NULL)
        return;
    if (is_a_register(params[beg + 3]) == 1 && instru->bytes3 == -1)
        instru->bytes3 = 1;
    if (is_a_indirect(params[beg + 3]) == 1 && instru->bytes3 == -1)
        instru->bytes3 = 2;
    if (is_a_direct(params[beg + 3]) == 1 && instru->bytes3 == -1)
        instru->bytes3 = 4;
}

static void fill_size_of_param(body_t *instru, char **params, int beg)
{
    if (is_a_register(params[beg + 1]) == 1 && instru->bytes1 == -1)
        instru->bytes1 = 1;
    if (is_a_indirect(params[beg + 1]) == 1 && instru->bytes1 == -1)
        instru->bytes1 = 2;
    if (is_a_direct(params[beg + 1]) == 1 && instru->bytes1 == -1)
        instru->bytes1 = 4;
    if (params[beg + 2] == NULL)
        return;
    if (is_a_register(params[beg + 2]) == 1 && instru->bytes2 == -1)
        instru->bytes2 = 1;
    if (is_a_indirect(params[beg + 2]) == 1 && instru->bytes2 == -1)
        instru->bytes2 = 2;
    if (is_a_direct(params[beg + 2]) == 1 && instru->bytes2 == -1)
        instru->bytes2 = 4;
    fill_size_params(instru, params, beg);
}

void check_param_size(char **params, body_t *instru, int beg)
{
    if (instru->code == 9 || instru->code == 12 || instru->code == 15) {
        instru->bytes1 = 2;
    }
    if (instru->code == 14) {
        instru->bytes1 = 2;
        instru->bytes2 = 2;
    }
    if (instru->code == 11) {
        if (is_a_register(params[beg + 2]) == 1) {
            instru->bytes2 = 1;
        } else
            instru->bytes2 = 2;
        if (is_a_register(params[beg + 3]) == 1) {
            instru->bytes3 = 1;
        } else
            instru->bytes3 = 2;
    }
    if (instru->code == 14 && is_a_register(params[beg + 1]) == 1)
        instru->bytes1 = 1;
    fill_size_of_param(instru, params, beg);
}

int check_param_type(char *param)
{
    if (param == NULL)
        return (-1);
    if (is_a_register(param) == 1)
        return (1);
    if (is_a_direct(param) == 1)
        return (10);
    if (is_a_indirect(param) == 1)
        return (11);
    return (0);
}

body_t *fill_instru(char *line)
{
    body_t *instru = malloc(sizeof(body_t));
    char **params = str_to_array(line, " ,");
    int beg = 0;

    if (params[0][my_strlen(params[0]) - 1] == ':')
        beg = 1;
    for (int i = 0; op_tab[i].nbr_args != 0; i++) {
        if (my_strcmp(params[beg], op_tab[i].mnemonique) == 1)
            instru->code = op_tab[i].code;
    }
    instru->codingbyte = calc_codingbyte(instru, params, beg);
    instru->bytes1 = -1;
    instru->bytes2 = -1;
    instru->bytes3 = -1;
    check_param_size(params, instru, beg);
    return (instru);
}

static int has_label_param(char *line)
{
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == ':' && line[i + 1] != ' ' && line[i + 1] != '\0')
            return (1);
    }
    return (0);
}

static int is_instruction(char *line)
{
    char **temp = str_to_array(line, " ,");

    if (line[0] == '\0') {
        free(temp);
        return (-1);
    }
    if (temp[1] == NULL) {
        free(temp);
        return (-1);
    }
    free(temp);
    return (1);
}

body_t **setup_body_struct(char **body)
{
    body_t **instructions;
    int nb_instru = 0;
    int instru_id = 0;

    for (int i = 0; body[i] != NULL; i++) {
        if (is_instruction(body[i]) != -1)
            nb_instru++;
    }
    instructions = malloc(sizeof(body_t *) * (nb_instru + 1));
    instructions[nb_instru] = NULL;
    for (int i = 0; body[i] != NULL; i++) {
        if (is_instruction(body[i]) != -1 && has_label_param(body[i]) == 1)
            instructions[instru_id] = fill_labeled(body[i]);
        if (is_instruction(body[i]) != -1 && has_label_param(body[i]) != 1)
            instructions[instru_id] = fill_instru(body[i]);
        if (is_instruction(body[i]) != -1)
            instru_id++;
    }
    return (instructions);
}
