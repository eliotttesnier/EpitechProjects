/*
** EPITECH PROJECT, 2024
** create_hashtable.c
** File description:
** create a new hashtable
*/

#include "../include/secured.h"

hashtable_t *new_hashtable(int (*hash)(char *, int), int len)
{
    hashtable_t *table = malloc(sizeof(hashtable_t));

    if (len <= 0 || table == NULL)
        return (NULL);
    table->h_table = malloc(sizeof(data_l *) * len);
    if (table->h_table == NULL)
        return (NULL);
    table->hash = hash;
    table->len = len;
    for (int i = 0; i < len; i++) {
        table->h_table[i] = NULL;
    }
    return (table);
}
