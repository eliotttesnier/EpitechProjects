/*
** EPITECH PROJECT, 2024
** dump
** File description:
** dump function
*/

#include "../include/secured.h"

void ht_dump(hashtable_t *ht)
{
    data_l *copy = NULL;

    if (ht == NULL)
        return;
    for (int i = 0; i < ht->len; i++) {
        mini_printf("[%i]:\n", i);
        copy = ht->h_table[i];
        for (copy; copy != NULL; copy = copy->next) {
            mini_printf("> %i - %s\n", copy->h_key, copy->data);
        }
    }
}
