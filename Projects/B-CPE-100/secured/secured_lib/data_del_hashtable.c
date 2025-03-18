/*
** EPITECH PROJECT, 2024
** ht_delete
** File description:
** delete data function
*/

#include "../include/secured.h"

int scan_list(data_l **list, int hashed)
{
    data_l *copy = *list;

    if (*list == NULL)
        return (84);
    if ((*list)->h_key == hashed) {
        *list = (*list)->next;
        return (0);
    }
    for (copy; copy->next != NULL; copy = copy->next) {
        if (copy->next->h_key == hashed) {
            copy->next = copy->next->next;
            return (0);
        }
    }
    return (84);
}

int delete(hashtable_t *ht, char *key)
{
    int hashed = ht->hash(key, ht->len);
    int ind = hashed % ht->len;

    return (scan_list(&ht->h_table[ind], hashed));
}

int ht_delete(hashtable_t *ht, char *key)
{
    if (ht == NULL || key == NULL)
        return (84);
    if (ht->h_table == NULL || ht->hash == NULL || ht->len == 0)
        return (84);
    if (my_strlen(key) == 0)
        return (84);
    if (ht->hash(key, ht->len) < 0)
        return (84);
    return (delete(ht, key));
}
