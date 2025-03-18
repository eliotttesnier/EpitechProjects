/*
** EPITECH PROJECT, 2023
** encrypt
** File description:
** encrypt the matrice
*/

#include "include/103.h"
#include <stdlib.h>

int nb_cols(double **mess)
{
    int i = 0;

    for (i = 0; mess[0][i] != '\0'; i++);
    return (i);
}

int nb_lines(double **mess)
{
    int i = 0;

    for (i = 0; mess[i] != NULL; i++);
    return (i);
}

void encrypt_message(double **mess, double **key)
{
    int nb_line_mess = nb_lines(mess);
    int nb_col_mess = nb_cols(mess);
    int nb_col_key = nb_cols(key);
    double **result = malloc(sizeof(double *) * nb_line_mess + 1);

    for (int i = 0; i < nb_line_mess; i++) {
        result[i] = malloc(sizeof(double) * nb_col_mess + 1);
    }
    for (int i = 0; i < nb_line_mess; i++) {
        for (int j = 0; j < nb_col_key; j++) {
            for (int k = 0; k < nb_col_mess; k++) {
                result[i][j] += mess[i][k] * key[k][j];
            }
        }
    }
    display_encript(key, result, nb_line_mess, nb_col_mess);
}
