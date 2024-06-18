/*
** EPITECH PROJECT, 2024
** nb_elements_array
** File description:
** number of elements in an array
*/

#include "../../includes/header.h"

int nb_elements_array(char **arr)
{
    int nb = 0;

    for (int i = 0; arr[i] != NULL; i++) {
        nb++;
    }
    return (nb);
}
