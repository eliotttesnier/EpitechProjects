/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** parsing_config
*/

#include "rpg_header.h"

void add_node_config(config_t **list, char *line)
{
    config_t *new = malloc(sizeof(config_t) * 1);
    config_t *tmp = *list;

    new->line = str_to_array(line, ":;\n");
    new->next = NULL;
    if (tmp == NULL) {
        *list = new;
        return;
    }
    for (tmp = *list; tmp->next != NULL; tmp = tmp->next);
    tmp->next = new;
}

config_t *get_config(char *path)
{
    config_t *list = NULL;
    FILE *fd = fopen(path, "r");
    size_t size = 0;
    char *buff = NULL;
    int ret = 0;

    if (fd == NULL && strcmp(path, "files/save.txt") == 0)
        return (NULL);
    if (fd == NULL)
        exit(84);
    for (; true; size = 0) {
        ret = getline(&buff, &size, fd);
        if (ret == -1)
            break;
        if (buff[0] != '#')
            add_node_config(&list, buff);
        buff = NULL;
    }
    fclose(fd);
    return (list);
}
