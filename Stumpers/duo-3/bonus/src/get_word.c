/*
** EPITECH PROJECT, 2024
** get_word
** File description:
** get_word
*/

#include "stumper.h"

static char *get_dict(char *path)
{
    int fd = open(path, O_RDONLY);
    int size = get_size(path);
    char *buf = malloc(sizeof(char) * size);

    read(fd, buf, size);
    return (buf);
}

void add_node(dict_t **list, char *word)
{
    dict_t *new = malloc(sizeof(dict_t) * 1);

    new->word = strdup(word);
    new->next = *list;
    *list = new;
}

static int nb_elem_list(dict_t *dico)
{
    dict_t *temp = dico;
    int nb = 0;

    while (temp != NULL) {
        nb++;
        temp = temp->next;
    }
    return (nb);
}

char *get_random_word(dict_t *dico)
{
    int rdm = (rand() % (nb_elem_list(dico)));
    int id = 0;
    dict_t *temp = dico;

    while (temp != NULL) {
        if (id == rdm)
            return (strdup(temp->word));
        id++;
        temp = temp->next;
    }
    return (dico->word);
}

static void free_struct(dict_t *dico)
{
    if (dico == NULL)
        return;
    free_struct(dico->next);
    free(dico->word);
}

char *get_word(char *path)
{
    char *dict = get_dict(path);
    dict_t *dico = NULL;
    char *line = NULL;
    char *word = NULL;

    (void)dico;
    line = strtok(dict, "\n");
    while (line != NULL) {
        add_node(&dico, line);
        line = strtok(NULL, "\n");
    }
    free(dict);
    word = get_random_word(dico);
    free_struct(dico);
    free(dico);
    return (word);
}
