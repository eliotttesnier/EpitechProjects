/*
** EPITECH PROJECT, 2024
** ROBOT
** File description:
** check_compilation_error
*/

#include "include/robot_header.h"

int has_correct_data(char *line)
{
    int i = 0;

    for (i = 0; line[i] != ' ' && line[i] != '\0'; i++);
    for (i = i; line[i] != '\0' && line[i] != '"'; i++) {
        if (line[i] != ' ')
            return (0);
    }
    if (line[i] == '\0')
        return (0);
    for (i = i + 1; line[i] != '\0' && line[i] != '"'; i++);
    if (line[i] == '\0')
        return (0);
    for (i = i + 1; line[i] != '\0'; i++) {
        if (line[i] != ' ')
            return (0);
    }
    return (1);
}

int check_header_error(char **header)
{
    bool has_name = false;
    bool has_comment = false;
    int var_data = 0;

    for (int i = 0; header[i] != NULL; i++) {
        if (my_strcmp(my_strcut(header[i], 0, 5), ".name ") == 1)
            has_name = true;
        if (my_strcmp(my_strcut(header[i], 0, 8), ".comment ") == 1)
            has_comment = true;
        var_data += has_correct_data(header[i]);
    }
    if (has_comment == false || has_name == false || var_data != 2)
        return (my_perror("Error in header\n", -1));
    return (1);
}

int is_only_label(char *line)
{
    int i = 0;

    for (i = 0; line[i] != '\0'; i++) {
        if (line[i] == ':')
            break;
    }
    if (line[i] == '\0')
        return (1);
    for (i = i + 1; line[i] != '\0'; i++) {
        if (line[i] != ' ')
            return (0);
    }
    return (1);
}

int find_instruction(char *line)
{
    char *temp;
    int beg = 0;
    int scheme = 0;

    if (line[0] == '\0' || is_only_label(line) == 1)
        return (0);
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == ':' && line[i + 1] == ' ')
            beg = i + 2;
    }
    for (beg = beg; line[beg] == ' ' && line[beg] != '\0'; beg++);
    line = my_strcut(line, beg, my_strlen(line));
    for (scheme = 0; op_tab[scheme].nbr_args != 0; scheme++) {
        temp = my_strcat(op_tab[scheme].mnemonique, " ");
        if (my_strncmp(temp, line, my_strlen(temp)) == 0)
            break;
    }
    if (op_tab[scheme].mnemonique == NULL)
        return (my_perror("Invalid instruction.\n", -1));
    return (check_all_params(line, scheme));
}

int check_body_error(char **body)
{
    for (int i = 0; body[i] != NULL; i++) {
        if (find_label(body, i) == -1)
            return (-1);
        if (find_instruction(body[i]) == -1 && body[i][0] != '\0')
            return (-1);
    }
    if (multiple_label(body) == -1)
        return (-1);
    return (1);
}
