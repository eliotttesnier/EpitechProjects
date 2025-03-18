/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** fill_entity
*/

#include "rpg_header.h"

static void add_a_voicebox(pnj_t *pnj, char *msg)
{
    voicebox_t *tmp = pnj->voicebox;
    voicebox_t *new = malloc(sizeof(voicebox_t));

    while (tmp != NULL && tmp->next != NULL) {
        tmp = tmp->next;
    }
        new->msg = strdup(msg);
        new->next = NULL;
    if (tmp == NULL) {
        pnj->voicebox = new;
    } else {
        tmp->next = new;
    }
}

static void add_movement(pnj_t *new)
{
    new->movement = malloc(sizeof(movement_t) * 1);
    new->movement->clock = sfClock_create();
    new->movement->direction = (sfVector2f){0, 0};
    new->animation = malloc(sizeof(animation_t) * 1);
    new->animation->clock = sfClock_create();
}

static void add_movement_eny(ennemy_t *new)
{
    new->movement = malloc(sizeof(movement_t) * 1);
    new->movement->clock = sfClock_create();
    new->movement->direction = (sfVector2f){0, 0};
    new->animation = malloc(sizeof(animation_t) * 1);
    new->animation->clock = sfClock_create();
}

void loop_voicebox(pnj_t *pnj)
{
    voicebox_t *voice = pnj->voicebox;

    pnj->talked = false;
    pnj->unlocked = true;
    if (pnj->voicebox == NULL)
        return;
    for (; voice->next != NULL; voice = voice->next);
    voice->next = pnj->voicebox;
}

static void add_a_pnj(gamedata_t *gamedata, char *line)
{
    char **data = str_to_array(line, ",");
    pnj_t *new = malloc(sizeof(pnj_t));

    new->path = strdup(data[0]);
    new->sprite = create_sprite(data[0], (sfIntRect){0, 0, 32, 48});
    new->id = atoi(data[1]);
    new->position.x = atoi(data[2]);
    new->position.y = atoi(data[3]);
    sfSprite_setPosition(new->sprite->sprite, new->position);
    sfSprite_setScale(new->sprite->sprite, (sfVector2f){0.6, 0.6});
    new->anchor.x = atoi(data[4]);
    new->anchor.y = atoi(data[5]);
    new->voicebox = NULL;
    for (int i = 6; data[i] != NULL; i++) {
        add_a_voicebox(new, data[i]);
    }
    loop_voicebox(new);
    add_movement(new);
    new->next = gamedata->entity->pnj;
    gamedata->entity->pnj = new;
}

void fill_pnj_list(gamedata_t *gamedata, config_t *config)
{
    config_t *tmp = get_node("PNJ", config);

    gamedata->entity->pnj = NULL;
    for (int i = 1; tmp->line[i] != NULL; i++) {
        add_a_pnj(gamedata, tmp->line[i]);
    }
    get_pnj_by_id(gamedata, 0)->unlocked = true;
}

void add_stats_eny(ennemy_t *new, char **data)
{
    new->maxhp = atoi(data[9]);
    new->hp = atoi(data[8]);
    new->atk = atoi(data[10]);
    new->respawn_time = atoi(data[11]);
    new->alive = true;
    new->respawn = sfClock_create();
    new->fight = malloc(sizeof(fight_t) * 1);
    new->fight->attacking = false;
    new->fight->can_attack = true;
    new->fight->buffer = sfClock_create();
    new->lifebar = malloc(sizeof(lifebar_t) * 1);
    new->lifebar->back = sfRectangleShape_create();
    new->lifebar->life = sfRectangleShape_create();
    sfRectangleShape_setSize(new->lifebar->back, (sfVector2f){50, 5});
    sfRectangleShape_setSize(new->lifebar->life, (sfVector2f){50, 5});
    sfRectangleShape_setFillColor(new->lifebar->back, sfRed);
    sfRectangleShape_setFillColor(new->lifebar->life, sfGreen);
    sfRectangleShape_setOrigin(new->lifebar->back, (sfVector2f){25, 2.5});
    sfRectangleShape_setOrigin(new->lifebar->life, (sfVector2f){25, 2.5});
}

static void add_a_eny(gamedata_t *gamedata, char *line)
{
    char **data = str_to_array(line, ",");
    ennemy_t *new = malloc(sizeof(ennemy_t));
    int x = atoi(data[2]);
    int y = atoi(data[3]);

    new->path = strdup(data[0]);
    new->sprite = create_sprite(data[0],
        (sfIntRect){0, 0, x, y});
    new->id = atoi(data[1]);
    new->position.x = atoi(data[4]);
    new->position.y = atoi(data[5]);
    sfSprite_setPosition(new->sprite->sprite, new->position);
    new->anchor.x = atoi(data[6]);
    new->anchor.y = atoi(data[7]);
    add_stats_eny(new, data);
    add_movement_eny(new);
    new->next = gamedata->entity->ennemy;
    gamedata->entity->ennemy = new;
}

void fill_ennemy_list(gamedata_t *gamedata, config_t *config)
{
    config_t *tmp = get_node("ENY", config);

    gamedata->entity->ennemy = NULL;
    for (int i = 1; tmp->line[i] != NULL; i++) {
        add_a_eny(gamedata, tmp->line[i]);
    }
}
