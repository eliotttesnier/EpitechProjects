/*
** EPITECH PROJECT, 2024
** SECURED
** File description:
** my_root
*/

#include "../include/secured.h"

double my_root(double square)
{
    double root = square / 3;
    int i;

    if (square <= 0)
        return (0);
    for (i = 0; i < 32; i++) {
        root = (root + square / root) / 2;
    }
    return (root);
}
