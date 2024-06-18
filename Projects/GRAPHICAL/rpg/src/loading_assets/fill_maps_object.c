/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** fill_maps_object
*/

#include "rpg_header.h"

void fill_maps(gamedata_t *gamedata, config_t *config)
{
    sfIntRect rect = (sfIntRect){0, 0, 6400, 6432};

    gamedata->map = malloc(sizeof(map_t) * 1);
    gamedata->map->back = create_sprite("assets/map/backmap.png", rect);
    gamedata->map->dec = create_sprite("assets/map/decomap.png", rect);
    gamedata->map->colmap = sfImage_createFromFile("assets/map/colmap.png");
    if (gamedata->map->colmap == NULL)
        exit(84);
    (void)config;
}

void add_a_chest(gamedata_t *game, char *line)
{
    char **params = str_to_array(line, ",");
    chest_t *new = malloc(sizeof(chest_t) * 1);

    new->animation = malloc(sizeof(animation_t) * 1);
    new->animation->clock = sfClock_create();
    new->sprite = create_sprite(params[1], (sfIntRect){0, 0, 32, 32});
    new->content = copy_item(atoi(params[2]));
    new->position.x = atoi(params[3]);
    new->position.y = atoi(params[4]);
    sfSprite_setPosition(new->sprite->sprite, new->position);
    new->next = game->obj->chests;
    game->obj->chests = new;
    new->path = strdup(params[1]);
    new->id = atoi(params[5]);
    new->opened = (atoi(params[6]) == 1 ? true : false);
    new->opening = false;
    if (new->opened)
        new->sprite->rect.top = 32 * 3;
}

void fill_bridge(gamedata_t *gamedata)
{
    gamedata->obj->bridge = malloc(sizeof(bridge_t) * 1);
    gamedata->obj->bridge->broken = create_sprite(
        "assets/sprites/Objects/brokenbridge.png", (sfIntRect){0, 0, 352, 80});
    sfSprite_setPosition(gamedata->obj->bridge->broken->sprite,
        (sfVector2f){4464, 5542});
    gamedata->obj->bridge->fixed = create_sprite(
        "assets/sprites/Objects/bridge.png", (sfIntRect){0, 0, 352, 80});
    sfSprite_setPosition(gamedata->obj->bridge->fixed->sprite,
        (sfVector2f){4464, 5542});
    gamedata->obj->bridge->repaired = false;
}

static void put_sound(gamedata_t *game)
{
    for (int i = 0; i < NB_SFX; i++) {
        sfMusic_setVolume(game->sfx->sounds[i], game->settings->vol_sfx);
    }
    sfMusic_setVolume(game->music->menu, game->settings->vol_music);
    sfMusic_setVolume(game->music->world, game->settings->vol_music);
    sfMusic_setVolume(game->music->epic, game->settings->vol_music);
}

static void fill_sfx_second(gamedata_t *gamedata)
{
    sfx_t *sx = gamedata->sfx;

    sx->sounds[SFX_GDEATH] = sfMusic_createFromFile("assets/sfx/gdeath.wav");
    sx->sounds[SFX_WDEATH] = sfMusic_createFromFile("assets/sfx/wdeath.wav");
    sx->sounds[SFX_GODEATH] = sfMusic_createFromFile("assets/sfx/godeath.wav");
}

static void fill_sfx(gamedata_t *gamedata)
{
    sfx_t *sx = gamedata->sfx;

    sx->sounds[SFX_AXE] = sfMusic_createFromFile("assets/sfx/axe.wav");
    sx->sounds[SFX_CHEST] = sfMusic_createFromFile("assets/sfx/chest.wav");
    sx->sounds[SFX_DAMAGE] = sfMusic_createFromFile("assets/sfx/damage.wav");
    sx->sounds[SFX_DIE] = sfMusic_createFromFile("assets/sfx/dead.wav");
    sx->sounds[SFX_EAT] = sfMusic_createFromFile("assets/sfx/eat.wav");
    sx->sounds[SFX_GOBELIN] = sfMusic_createFromFile("assets/sfx/gobelin.wav");
    sx->sounds[SFX_GOLEM] = sfMusic_createFromFile("assets/sfx/golem.wav");
    sx->sounds[SFX_INV] = sfMusic_createFromFile("assets/sfx/inventory.wav");
    sx->sounds[SFX_SPEAR] = sfMusic_createFromFile("assets/sfx/spear.wav");
    sx->sounds[SFX_SWORD] = sfMusic_createFromFile("assets/sfx/sword.wav");
    sx->sounds[SFX_WOLF] = sfMusic_createFromFile("assets/sfx/wolf.wav");
    sx->sounds[SFX_TALKING] = sfMusic_createFromFile("assets/sfx/talking.wav");
    fill_sfx_second(gamedata);
    for (int i = 0; i < NB_SFX; i++) {
        if (sx->sounds[i] == NULL)
            exit(84);
    }
    put_sound(gamedata);
}

void fill_object_list(gamedata_t *gamedata, config_t *config)
{
    config_t *tmp = get_node("OBJ", config);

    gamedata->obj = malloc(sizeof(object_t) * 1);
    gamedata->obj->chests = NULL;
    for (int i = 1; tmp->line[i] != NULL; i++) {
        if (strncmp(tmp->line[i], "CHEST,", 6) == 0)
            add_a_chest(gamedata, tmp->line[i]);
    }
    fill_bridge(gamedata);
    gamedata->obj->gate = create_sprite(
        "assets/sprites/Objects/gate.png", (sfIntRect){0, 0, 16, 80});
    sfSprite_setPosition(gamedata->obj->gate->sprite,
        (sfVector2f){1971, 831});
    gamedata->sfx = malloc(sizeof(sfx_t) * 1);
    fill_sfx(gamedata);
}
