/*
** EPITECH PROJECT, 2023
** header.h
** File description:
** header
*/

#ifndef SETTING_UP_SECU
    #define SETTING_UP_SECU

typedef struct square {
    int x;
    int y;
    int size;
}   s_square;

int get_nb_lines(char *file);
int size(char *file);
int generate_errors(char **av);
int file_errors(char **av);
void replace_x(char **arr, s_square *biggest);
int display_arr(char **arr, int nb_lines);
int scanning(char **arr, int nb_lines);
int get_from_file(char **av);
int generate(char **av);

#endif /* !SETTING_UP_SECU */
