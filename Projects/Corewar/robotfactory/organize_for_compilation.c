/*
** EPITECH PROJECT, 2024
** ROBOT
** File description:
** organize_for_compilation
*/

#include "include/robot_header.h"

int get_prog_size(body_t **instruction_arr)
{
    int code = 0;
    int prog_size = 0;

    for (int i = 0; instruction_arr[i] != NULL; i++) {
        code = instruction_arr[i]->code;
        if (instruction_arr[i]->bytes1 != -1)
            prog_size += instruction_arr[i]->bytes1;
        if (instruction_arr[i]->bytes2 != -1)
            prog_size += instruction_arr[i]->bytes2;
        if (instruction_arr[i]->bytes3 != -1)
            prog_size += instruction_arr[i]->bytes3;
        prog_size += 1;
        if (code != 1 && code != 9 && code != 12 && code != 15)
            prog_size += 1;
    }
    if (check_endian() == true)
        prog_size = little_to_big_u(prog_size);
    return (prog_size);
}

int write_header(header_t *header_s, int cor_fd)
{
    write(cor_fd, header_s, sizeof(header_t));
    return (0);
}

int organize_for_compilation(char **head_arr, char **body_arr, char *filepath)
{
    int cor_fd = 0;
    body_t **instruction_arr = setup_body_struct(body_arr);
    header_t *header_s = setup_header_struct(head_arr);

    if (my_strlen(header_s->comment) > COMMENT_LENGTH)
        return (my_perror("The comment is too long.\n", -1));
    if (my_strlen(header_s->prog_name) > PROG_NAME_LENGTH)
        return (my_perror("The name is too long.\n", -1));
    cor_fd = create_cor_file(filepath);
    if (cor_fd == -1)
        return (-1);
    if (check_endian() == 1) {
        header_s->magic = little_to_big_u(header_s->magic);
        header_s->prog_size = little_to_big_u(header_s->prog_size);
    }
    header_s->prog_size = get_prog_size(instruction_arr);
    set_label_args(instruction_arr, body_arr);
    write(cor_fd, header_s, sizeof(header_t));
    write_body(instruction_arr, cor_fd);
    return (0);
}
