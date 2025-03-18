/*
** EPITECH PROJECT, 2024
** ROBOT
** File description:
** setup_header_struct
*/

#include "include/robot_header.h"

void fill_str(char *to_fill, char *fill)
{
    for (int i = 0; fill[i] != '\0'; i++) {
        to_fill[i] = fill[i];
    }
}

header_t *setup_header_struct(char **head_arr)
{
    header_t *header_s = malloc(sizeof(header_t));
    int begin = 0;
    int end = 0;
    int in = 0;

    header_s->magic = COREWAR_EXEC_MAGIC;
    header_s->prog_size = 22;
    for (in = 0; my_strlen(head_arr[in]) < 3; in++);
    for (begin = 0; head_arr[in][begin] != '"'; begin++);
    for (end = begin + 1; head_arr[in][end] != '"'; end++);
    fill_str(header_s->prog_name, my_strcut(head_arr[in], begin + 1, end - 1));
    for (in = in + 1; head_arr[in][0] == '\0'; in++);
    for (begin = 0; head_arr[in][begin] != '"'; begin++);
    for (end = begin + 1; head_arr[in][end] != '"'; end++);
    fill_str(header_s->comment, my_strcut(head_arr[in], begin + 1, end - 1));
    return (header_s);
}
