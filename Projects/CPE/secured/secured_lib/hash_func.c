/*
** EPITECH PROJECT, 2024
** hash_func
** File description:
** hash function
*/

#include "../include/secured.h"

int hash(char *key, int len)
{
    int size = my_strlen(key);
    double h_key = 0;

    if (key[0] == '\0')
        return (-1);
    for (int i = 0; key[i] != '\0'; i++) {
        h_key += key[i];
    }
    h_key += 3.1415926535 * my_nbrlen(h_key);
    for (int i = 0; i < 10; i++) {
        h_key = my_root(h_key);
        h_key = h_key - (int)h_key;
        h_key = h_key * 1000000;
    }
    return (h_key);
}
