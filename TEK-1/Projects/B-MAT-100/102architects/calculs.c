/*
** EPITECH PROJECT, 2023
** calculs.c
** File description:
** calculs
*/

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>

void calc_coord(double **M, double *point)
{
    double *C = malloc(3);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            C[i] += M[i][j] * point[j];
        }
    }
    for (int i = 0; i < 3; i++) {
        point[i] = C[i];
    }
}

void calc_matrice(double **M, double **M2)
{
    double **C = malloc(sizeof(char *) * 3);
    C[0] = malloc(3);
    C[1] = malloc(3);
    C[2] = malloc(3);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                C[i][j] += M2[i][k] * M[k][j];
            }
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            M[i][j] = C[i][j];
        }
    }
}
