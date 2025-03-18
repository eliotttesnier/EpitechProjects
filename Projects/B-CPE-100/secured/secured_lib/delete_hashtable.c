/*
** EPITECH PROJECT, 2024
** delete_hashtable
** File description:
** delete the hashtable
*/

#include "../include/secured.h"

void free_data(data_l *list)
{
    if (list == NULL)
        return;
    free_data(list->next);
    free(list->data);
    free(list);
}

void delete_hashtable(hashtable_t *ht)
{
    if (ht->h_table == NULL)
        return;
    for (int i = 0; i < ht->len; i++) {
        free_data(ht->h_table[i]);
    }
    free(ht->h_table);
    free(ht);
}
