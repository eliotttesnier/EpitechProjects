/*
** EPITECH PROJECT, 2024
** fill_labeled
** File description:
** fill labeled
*/

#include "include/robot_header.h"

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

static void actualise_param(body_t *instru, int oct)
{
    if (instru->param1 == -9) {
        instru->param1 = oct;
        return;
    }
    if (instru->param2 == -9) {
        instru->param2 = oct;
        return;
    }
    if (instru->param3 == -9) {
        instru->param3 = oct;
        return;
    }
}

void watch_above(body_t **instru)
{
    return;
}

void watch_under(body_t **instru)
{
    return;
}

static char *get_label(char *line, body_t *instru)
{
    char **params = str_to_array(line, " ,");
    char *label;
    int beg = 0;

    if (params[0][my_strlen(params[0]) - 1] == ':')
        beg = 1;
    if (instru->param1 == -9)
        return (my_strcut(params[beg + 1], 2, my_strlen(params[beg + 1]) + 1));
    if (instru->param2 == -9)
        return (my_strcut(params[beg + 2], 2, my_strlen(params[beg + 1]) + 1));
    if (instru->param3 == -9)
        return (my_strcut(params[beg + 3], 2, my_strlen(params[beg + 1]) + 1));
    return (NULL);
}

void set_label_var(body_t **instru, int ind, char **body, int i)
{
    char *label = get_label(body[i], instru[ind]);
    int nb_instru = ind;
    int oct = 0;

    actualise_param(instru[ind], oct);
}

void set_label_args(body_t **tab, char **body)
{
    int nb = 0;

    for (int i = 0; body[i] != NULL; i++) {
        if (is_instruction(body[i]) == 1 && tab[nb]->param1 == -9)
            set_label_var(tab, nb, body, i);
        if (is_instruction(body[i]) == 1 && tab[nb]->param2 == -9)
            set_label_var(tab, nb, body, i);
        if (is_instruction(body[i]) == 1 && tab[nb]->param3 == -9)
            set_label_var(tab, nb, body, i);
        if (is_instruction(body[i]) == 1)
            nb++;
    }
}

body_t *fill_labeled(char *line)
{
    body_t *instru = malloc(sizeof(body_t));
    char **params = str_to_array(line, " ,");
    int beg = 0;

    if (params[0][my_strlen(params[0]) - 1] == ':')
        beg = 1;
    for (int i = beg; op_tab[i].nbr_args != 0; i++) {
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
