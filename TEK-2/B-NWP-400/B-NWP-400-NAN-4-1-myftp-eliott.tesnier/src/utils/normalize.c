/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** normalize
*/

#include "myftp.h"

static void handle_component(char **components, int *comp_count, char *token)
{
    if (strcmp(token, ".") == 0)
        return;
    if (strcmp(token, "..") == 0 && *comp_count > 0) {
        if (*comp_count > 0)
            (*comp_count)--;
        return;
    }
    components[*comp_count] = strdup(token);
    (*comp_count)++;
}

static char *init_path_tokenization(const char *path)
{
    char *tmp = strdup(path);

    return tmp;
}

static int split_path_components(const char *path, char **components)
{
    char *tmp = init_path_tokenization(path);
    char *token;
    int comp_count = 0;

    token = strtok(tmp, "/");
    while (token != NULL) {
        handle_component(components, &comp_count, token);
        token = strtok(NULL, "/");
    }
    free(tmp);
    return comp_count;
}

static void rebuild_path(char *result, char **components, int comp_count)
{
    result[0] = '/';
    result[1] = '\0';
    for (int i = 0; i < comp_count; i++) {
        strcat(result, components[i]);
        if (i < comp_count - 1)
            strcat(result, "/");
        free(components[i]);
    }
}

char *normalize_relative_path(const char *path)
{
    char *result = malloc(PATH_MAX_LEN);
    char **components = malloc(sizeof(char *) * PATH_MAX_LEN);
    int comp_count;

    if (!path || !result || !components)
        return NULL;
    comp_count = split_path_components(path, components);
    rebuild_path(result, components, comp_count);
    free(components);
    return result;
}
