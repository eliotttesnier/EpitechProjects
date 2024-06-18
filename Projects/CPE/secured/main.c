/*
** EPITECH PROJECT, 2024
** main
** File description:
** main for secured
*/

#include <stdio.h>
#include "include/secured.h"

int main(int ac, char **av)
{
    hashtable_t *ht = new_hashtable(&hash, 4);

    mini_printf("%i  |  %i\n", hash("Kratos", 4) % 4, hash("banae", 4) % 4);
    delete_hashtable(ht);
    return (0);
}
