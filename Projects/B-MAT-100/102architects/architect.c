/*
** EPITECH PROJECT, 2023
** architect.c
** File description:
** calcul of matrices
*/

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include "header.h"

void display_m(double **M)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            if (M[i][j] < 0.00 && M[i][j] > - 0.001)
                M[i][j] = 0.00;
            printf("%-8.2f", M[i][j]);
        }
        printf("%.2f\n", M[i][2]);
    }
}

void refl(double **M, double *point, double d)
{
    double **tM = malloc(sizeof(char *) * 3);
    tM[0] = malloc(3);
    tM[1] = malloc(3);
    tM[2] = malloc(3);
    tM[0][0] = cos((2 * d) * M_PI / 180); tM[0][1] = sin((2 * d) * M_PI / 180); tM[0][2] = 0.00;
    tM[1][0] = sin((2 * d) * M_PI / 180); tM[1][1] = -cos((2 * d) * M_PI / 180); tM[1][2] = 0.00;
    tM[2][0] = 0.00; tM[2][1] = 0.00; tM[2][2] = 1.00;
    calc_matrice(M, tM);
    printf("Reflection over an axis with an inclination angle of %i degrees\n", (int)d);
}

void rota(double **M, double *point, double d)
{
    double **tM = malloc(sizeof(char *) * 3);
    tM[0] = malloc(3);
    tM[1] = malloc(3);
    tM[2] = malloc(3);
    tM[0][0] = cos(d * M_PI / 180); tM[0][1] = -sin(d * M_PI / 180); tM[0][2] = 0.00;
    tM[1][0] = sin(d * M_PI / 180); tM[1][1] = cos(d * M_PI / 180); tM[1][2] = 0.00;
    tM[2][0] = 0.00; tM[2][1] = 0.00; tM[2][2] = 1.00;
    calc_matrice(M, tM);
    printf("Rotation by a %i degree angle\n", (int)d);
}

void scaling(double **M, double *point, double m, double n)
{
    double **tM = malloc(sizeof(char *) * 3);
    tM[0] = malloc(3);
    tM[1] = malloc(3);
    tM[2] = malloc(3);
    tM[0][0] = m; tM[0][1] = 0.00; tM[0][2] = 0.00; tM[1][0] = 0.00; tM[1][1] = n; tM[1][2] = 0.00; tM[2][0] = 0.00; tM[2][1] = 0.00; tM[2][2] = 1.00;
    calc_matrice(M, tM);
    printf("Scaling by factors %i and %i\n", (int)m, (int)n);
}

void translation(double **M, double *point, double i, double j)
{
    double **tM = malloc(sizeof(char *) * 3);
    tM[0] = malloc(3);
    tM[1] = malloc(3);
    tM[2] = malloc(3);
    tM[0][0] = 1.00; tM[0][1] = 0.00; tM[0][2] = i; tM[1][0] = 0.00; tM[1][1] = 1.00; tM[1][2] = j; tM[2][0] = 0.00; tM[2][1] = 0.00; tM[2][2] = 1.00;
    calc_matrice(M, tM);
    printf("Translation along vector (%i, %i)\n", (int)i, (int)j);
}

void fill(double **M, double *point, char **av)
{
    M[0][0] = 1.00;
    M[0][1] = 0.00;
    M[0][2] = 0.00;
    M[1][0] = 0.00;
    M[1][1] = 1.00;
    M[1][2] = 0.00;
    M[2][0] = 0.00;
    M[2][1] = 0.00;
    M[2][2] = 1.00;
    point[0] = strtod(av[1], NULL);
    point[1] = strtod(av[2], NULL);
    point[2] = 1.00;
}

int main(int ac, char **av)
{
    error_cases(ac, av);

    double **M = malloc(sizeof(char *) * 3);
    M[0] = malloc(3);
    M[1] = malloc(3);
    M[2] = malloc(3);
    double *point = malloc(3);
    fill(M, point, av);
    for (int i = 0; i < ac; i++) {
        if ((av[i][0] == '-') && (av[i][1] == 't') && (av[i][2] == '\0')) {
            translation(M, point, strtod(av[i + 1], NULL), strtod(av[i + 2], NULL));
        }
        if ((av[i][0] == '-') && (av[i][1] == 'z') && (av[i][2] == '\0')) {
            scaling(M, point, strtod(av[i + 1], NULL), strtod(av[i + 2], NULL));
        }
        if ((av[i][0] == '-') && (av[i][1] == 'r') && (av[i][2] == '\0')) {
            rota(M, point, strtod(av[i + 1], NULL));
        }
        if ((av[i][0] == '-') && (av[i][1] == 's') && (av[i][2] == '\0')) {
            refl(M, point, strtod(av[i + 1], NULL));
        }
    }
    calc_coord(M, point);
    display_m(M);
    printf("(%.2f, %.2f) => (%.2f, %.2f)\n", strtod(av[1], NULL), strtod(av[2], NULL), point[0], point[1]);
    return (0);
}