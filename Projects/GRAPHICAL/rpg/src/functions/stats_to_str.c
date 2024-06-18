/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** stats_to_str
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

char *get_hp(gamedata_t *game)
{
    char *hp_to_str = my_itoa(game->inventory->stats->health);
    char *max_to_str = my_itoa(game->inventory->stats->max_health);
    char *temp_hp = my_strcat("HP: ", hp_to_str);
    char *temp_max = my_strcat("/", max_to_str);
    char *hp_str = my_strcat(temp_hp, temp_max);

    free(hp_to_str);
    free(max_to_str);
    free(temp_hp);
    free(temp_max);
    return (hp_str);
}

char *get_mana(gamedata_t *game)
{
    int mana = game->inventory->stats->mana;
    char *nbr_to_str = my_itoa(mana);
    char *mana_str = my_strcat("MANA: ", nbr_to_str);

    free(nbr_to_str);
    return (mana_str);
}

char *get_def(gamedata_t *game)
{
    int def = game->inventory->stats->defense;
    char *nbr_to_str = my_itoa(def);
    char *def_str = my_strcat("DEF: ", nbr_to_str);

    free(nbr_to_str);
    return (def_str);
}

char *get_xp(gamedata_t *game)
{
    int xp = game->inventory->stats->xp;
    char *nbr_to_str = my_itoa(xp);
    char *xp_str = my_strcat("XP: ", nbr_to_str);

    free(nbr_to_str);
    return (xp_str);
}

char *get_atk(gamedata_t *game)
{
    int atk = game->inventory->stats->attack;
    char *nbr_to_str = my_itoa(atk);
    char *atk_str = my_strcat("ATK: ", nbr_to_str);

    free(nbr_to_str);
    return (atk_str);
}
