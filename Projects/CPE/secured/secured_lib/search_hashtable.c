/*
** EPITECH PROJECT, 2024
** search
** File description:
** search function
*/

#include "../include/secured.h"

char *search(hashtable_t *ht, char *key)
{
    int h_key = ht->hash(key, ht->len);
    data_l *tmp = ht->h_table[h_key % ht->len];

    while (tmp != NULL) {
        if (tmp->h_key == h_key)
            return (tmp->data);
        tmp = tmp->next;
    }
    return (NULL);
}

char *ht_search(hashtable_t *ht, char *key)
{
    if (ht == NULL || key == NULL)
        return (NULL);
    if (ht->h_table == NULL || ht->hash == NULL || ht->len == 0)
        return (NULL);
    if (my_strlen(key) == 0)
        return (NULL);
    if (ht->hash(key, ht->len) < 0)
        return (NULL);
    return (search(ht, key));
}
