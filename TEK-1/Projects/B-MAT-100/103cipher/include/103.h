/*
** EPITECH PROJECT, 2023
** 103cipher
** File description:
** 103
*/

#ifndef CIPH
    #define CIPH
    #include <math.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <string.h>

void encrypt_message(double **mess, double **key);
void decrypt_message(double **mess, double **key);
void display_decript(double **key, double **result, int nb_l, int nb_c);
void display_encript(double **key, double **result, int nb_l, int nb_c);
int nb_lines(double **mess);
int nb_cols(double **mess);

#endif /* CIPH */
