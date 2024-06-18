/*
** EPITECH PROJECT, 2024
** main
** File description:
** main
*/

#include "include/robot_header.h"

int compile_file(int asm_fd, char *filepath)
{
    struct stat st;
    char *buffer;
    char **head_arr;
    char **body_arr;
    int right_format = 0;

    stat(filepath, &st);
    buffer = malloc(sizeof(char) * (st.st_size + 1));
    read(asm_fd, buffer, st.st_size);
    head_arr = get_head_in_arr(buffer);
    body_arr = get_body_in_arr(buffer);
    right_format += check_header_error(head_arr);
    right_format += check_body_error(body_arr);
    if (right_format != 2)
        return (-1);
    free(buffer);
    return (organize_for_compilation(head_arr, body_arr, filepath));
}

int init_files(char *filepath)
{
    int asm_fd = open_asm_file(filepath);

    if (asm_fd == -1)
        return (-1);
    return (compile_file(asm_fd, filepath));
}

int main(int ac, char **av)
{
    char *file_type;

    if (ac < 2)
        mini_printf("Where the fudge is the file ?\n");
    if (ac > 2)
        mini_printf("Too many arguments.\n");
    if (ac != 2)
        return (84);
    file_type = my_strcut(av[1], my_strlen(av[1]) - 2, my_strlen(av[1]) - 1);
    if (my_strcmp(file_type, ".s") == 0 || my_strlen(av[1]) < 3) {
        mini_printf("Wrong file type or name.\n");
        return (84);
    }
    if (init_files(av[1]) == -1)
        return (84);
    return (0);
}
