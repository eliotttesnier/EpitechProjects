/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** chest_anim
*/

#include "rpg_header.h"

static char *my_strcat(char *s1, char *s2)
{
    char *new = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
    int i = 0;

    if (s1 == NULL || s2 == NULL)
        return (NULL);
    for (i = 0; i < (int)strlen(s1); i++) {
        new[i] = s1[i];
    }
    for (i = i; i < (int)strlen(s1) + (int)strlen(s2); i++) {
        new[i] = s2[i - strlen(s1)];
    }
    new[strlen(s1) + strlen(s2)] = '\0';
    return (new);
}

void anim_one_chest(chest_t *chest, gamedata_t *game)
{
    float time = sfClock_getElapsedTime(chest->animation->clock).microseconds;

    if (time > 150000) {
        sfClock_restart(chest->animation->clock);
        chest->sprite->rect.top += chest->sprite->rect.height;
        if (chest->sprite->rect.top >= chest->sprite->rect.height * 4) {
            chest->opening = false;
            chest->sprite->rect.top -= chest->sprite->rect.height;
            put_popup(game,
                my_strcat("You just found a \n", chest->content->name));
        }
    }
}

void chest_anim(gamedata_t *game)
{
    chest_t *tmp = game->obj->chests;

    while (tmp != NULL) {
        if (is_chest_visible(game, tmp) && tmp->opening)
            anim_one_chest(tmp, game);
        tmp = tmp->next;
    }
}
