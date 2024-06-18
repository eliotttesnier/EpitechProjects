/*
** EPITECH PROJECT, 2023
** main prog
** File description:
** 103cipher
*/

#include "include/103.h"

double **code_to_matrix(double **code_m, char *code)
{
    int y = 0;
    int x = 0;
    int c = 0;
    int character;
    int len = strlen(code);

    len = ceil(sqrt(len));
    code_m = malloc(sizeof(double *) * (len + 1));
    for (int i = 0; i < len; i++) {
        code_m[i] = malloc(sizeof(double) * (len + 1));
        code_m[i][len] = '\0';
    }
    code_m[len] = NULL;
    for (y = 0; code_m[y] != NULL; y++) {
        for (x = 0; x < len; x++) {
            if (c >= strlen(code))
                character = 0;
            else
                character = code[c];
            code_m[y][x] = (double)character;
            c++;
        }
    }
    return (code_m);
}

double **message_to_matrix(double **message_m, char *message, int nb_col)
{
    int y = 0;
    int x = 0;
    int c = 0;
    int character;
    int len = strlen(message);

    len = len / nb_col + 1;
    message_m = malloc(sizeof(double *) * (len + 1));
    for (int i = 0; i < len; i++) {
        message_m[i] = malloc(sizeof(double) * (nb_col + 1));
        message_m[i][nb_col] = '\0';
    }
    message_m[len] = NULL;
    for (y = 0; message_m[y] != NULL; y++) {
        for (x = 0; x < nb_col; x++) {
            if (c >= strlen(message))
                character = 0;
            else
                character = message[c];
            message_m[y][x] = (double)character;
            c++;
        }
    }
    return (message_m);
}

int len_mess_decrpyt(char *message)
{
    int len = 0;

    for (int i = 0; message[i] != 0; i++) {
        if (message[i] == ' ')
            len += 1;
    }
    return (len + 1);
}

double **message_to_matrix_decrpyt(double **message_m, char *message, int nb_col)
{
    int y = 0;
    int x = 0;
    int index = 0;
    int character;
    int len = len_mess_decrpyt(message);

    len = (int)ceil((float)len / (float)nb_col);
    message_m = malloc(sizeof(double *) * (len + 1));
    for (int i = 0; i < len; i++) {
        message_m[i] = malloc(sizeof(double) * (nb_col + 1));
        message_m[i][nb_col] = '\0';
    }
    message_m[len] = NULL;
    for (y = 0; message_m[y] != NULL; y++) {
        for (x = 0; x < nb_col; x++) {
            if (index >= strlen(message))
                character = 0;
            else {
                character = strtod(message, NULL);
                for (int i = index; i - index < floor(log10(abs(character))) + 2; i++) {
                    message[i] = ' ';
                }
            }
            message_m[y][x] = (double)character;
            index += floor(log10(abs(character))) + 2;
        }
    }
    return (message_m);
}

void error_case(int ac, char **av)
{
    if (ac != 4)
        exit(84);
    if (av[3][1] != '\0')
        exit(84);
    if (av[3][0] != '1' && av[3][0] != '0')
        exit(84);
}

int main(int ac, char **av)
{
    int nb_col;
    double **code_m;
    double **message_m;

    error_case(ac, av);
    code_m = code_to_matrix(code_m, av[2]);
    for (nb_col = 0; code_m[0][nb_col] != '\0'; nb_col++);
    if (av[3][0] == '0') {
        message_m = message_to_matrix(message_m, av[1], nb_col);
        encrypt_message(message_m, code_m);
    } else if (av[3][0] == '1') {
        message_m = message_to_matrix_decrpyt(message_m, av[1], nb_col);
        decrypt_message(message_m, code_m);
    }
}
