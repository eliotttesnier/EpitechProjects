/*
** EPITECH PROJECT, 2023
** display
** File description:
** display the results
*/

#include "include/103.h"
#include <stdlib.h>
#include <stdio.h>

void display_decript(double **key, double **result, int nb_l, int nb_c)
{
    int nb_li = nb_lines(key);

    printf("Key matrix:\n");
    for (int i = 0; i < nb_c; i++) {
        for (int j = 0; j < nb_c - 1; j++) {
            printf("%-8.3f", key[i][j]);
        }
        printf("%-8.3f\n", key[i][nb_c - 1]);
    }
    printf("\nDecrypted message:\n");
    for (int i = 0; i < nb_l; i++) {
        for (int j = 0; j < nb_c; j++) {
            if ((int)result[i][j] != 0)
                printf("%c", (int)round(result[i][j]));
        }
    }
    printf("\n");
}


void display_encript(double **key, double **result, int nb_l, int nb_c)
{
    int nb_li = nb_lines(key);

    printf("Key matrix:\n");
    for (int i = 0; i < nb_li; i++) {
        for (int j = 0; j < nb_li - 1; j++) {
            printf("%-8i", (int)key[i][j]);
        }
        printf("%i\n", (int)key[i][nb_li - 1]);
    }
    printf("\nEncrypted message:\n");
    for (int i = 0; i < nb_l; i++) {
        for (int j = 0; j < nb_c; j++) {
            if ((int)result[i][j] != 0) {
                if (i == 0 && j == 0)
                    printf("%i", (int)result[i][j]);
                else
                    printf(" %i", (int)result[i][j]);
            }
        }
    }
    printf("\n");
}
