/*
** EPITECH PROJECT, 2023
** decrpyt
** File description:
** encrypt the matrice
*/

#include "include/103.h"
#include <stdlib.h>

double determinant(double **key, int k)
{
    double s = 1, det = 0;
    double **b = malloc(sizeof(double *) * 25);
    int m, n;

    for (int i = 0; i < 25; i++) {
        b[i] = malloc(25);
    }
    if (k == 1)
        return (key[0][0]);
    for (int c = 0; c < k; c++) {
        m = 0;
        n = 0;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                b[i][j] = 0;
                if (i != 0 && j != c) {
                    b[m][n] = key[i][j];
                    if (n < (k - 2))
                        n++;
                    else {
                        n = 0;
                        m++;
                    }
                }
            }
        }
        det = det + s * (key[0][c] * determinant(b, k - 1));
        s = -1 * s;
    }
    return (det);
}

void transpose(double **num, double **fac, double r)
{
    double **b = malloc(sizeof(double *) * 25);
    double **inverse = malloc(sizeof(double *) * 25);
    double d = determinant(num, r);;

    for (int i = 0; i < 25; i++) {
        b[i] = malloc(25);
        inverse[i] = malloc(25);
    }
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < r; j++) {
            num[i][j] = fac[j][i] / d;
        }
    }
}

void cofactor(double **num, double f)
{
    double **b = malloc(sizeof(double *) * 25);
    double **fac = malloc(sizeof(double *) * 25);
    int m, n;

    for (int i = 0; i < 25; i++) {
        b[i] = malloc(25);
        fac[i] = malloc(25);
    }
    for (int q = 0; q < f; q++) {
        for (int p = 0; p < f; p++) {
            m = 0;
            n = 0;
            for (int i = 0; i < f; i++) {
                for (int j = 0; j < f; j++) {
                    if (i != q && j != p) {
                        b[m][n] = num[i][j];
                        if (n < (f - 2))
                            n++;
                        else {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);
        }
    }
    transpose(num, fac, f);
}

void invert(double **key)
{
    int nb_line_key = nb_lines(key);
    float det = 0;

    det = determinant(key, nb_line_key);
    if (det == 0.000000) {
        write(2, "key matrix is not inversible\n", 29);
        exit(84);
    }
    cofactor(key, (double)nb_line_key);
}

void decrypt_message(double **mess, double **key)
{
    int nb_line_mess = nb_lines(mess);
    int nb_col_mess = nb_cols(mess);
    int nb_col_key = nb_cols(key);
    double **result = malloc(sizeof(double *) * nb_line_mess + 1);

    if (nb_col_key == 1)
        key[0][0] = 1/key[0][0];
    else
        invert(key);
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
    display_decript(key, result, nb_line_mess, nb_col_mess);
}
