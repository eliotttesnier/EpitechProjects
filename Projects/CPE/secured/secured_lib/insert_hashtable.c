/*
** EPITECH PROJECT, 2024
** insert
** File description:
** insert function
*/

#include "../include/secured.h"

int create_node(data_l **list, int hashed, char *value)
{
    data_l *new = malloc(sizeof(data_l));

    if (new == NULL)
        return (84);
    new->data = my_strcpy(value);
    if (new->data == NULL)
        return (84);
    new->h_key = hashed;
    new->next = *list;
    *list = new;
    return (0);
}

int scan_key(data_l *list, int hashed, char *value)
{
    data_l *copy = list;

    if (list == NULL)
        return (0);
    for (copy; copy != NULL; copy = copy->next) {
        if (copy->h_key == hashed) {
            copy->data = my_strcpy(value);
            return (1);
        }
    }
    return (0);
}

int insert(hashtable_t *ht, char *key, char *value)
{
    int hashed = ht->hash(key, ht->len);
    int ind = hashed % ht->len;

    if (scan_key(ht->h_table[ind], hashed, value) == 1)
        return (0);
    return (create_node(&ht->h_table[ind], hashed, value));
}

int ht_insert(hashtable_t *ht, char *key, char *value)
{
    if (ht == NULL || key == NULL || value == NULL)
        return (84);
    if (ht->h_table == NULL || ht->hash == NULL || ht->len == 0)
        return (84);
    if (my_strlen(key) == 0 || my_strlen(value) == 0)
        return (84);
    if (ht->hash(key, ht->len) < 0)
        return (84);
    return (insert(ht, key, value));
}
