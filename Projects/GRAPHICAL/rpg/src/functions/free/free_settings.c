/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** free_settings
*/

#include "rpg_header.h"

void free_settings(settings_t *settings)
{
    free(settings->keys);
    free(settings);
}
