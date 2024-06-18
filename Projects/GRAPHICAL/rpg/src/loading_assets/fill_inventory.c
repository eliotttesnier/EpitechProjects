/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** ventory
*/

#include "rpg_header.h"

const item_t item_list[39] = {
    {"assets/sprites/weapons/sword_1(100x100).png", 0, 0, 1, 0, 0, NULL,
        "basic sword"},
    {"assets/sprites/weapons/sword_2(100x100).png", 1, 1, 2, 0, 0, NULL,
        "good sword"},
    {"assets/sprites/weapons/sword_3(100x100).png", 2, 2, 3, 0, 0, NULL,
        "fancy sword"},
    {"assets/sprites/weapons/sword_4(100x100).png", 3, 3, 4, 0, 0, NULL,
        "epic sword"},
    {"assets/sprites/weapons/sword_5(100x100).png", 4, 4, 5, 0, 0, NULL,
        "lengendary sword"},
    {"assets/sprites/weapons/spear_1(100x100).png", 5, 0, 1, 0, 0, NULL,
        "basic spear"},
    {"assets/sprites/weapons/spear_2(100x100).png", 6, 1, 2, 0, 0, NULL,
        "good spear"},
    {"assets/sprites/weapons/spear_3(100x100).png", 7, 2, 3, 0, 0, NULL,
        "fancy spear"},
    {"assets/sprites/weapons/spear_4(100x100).png", 8, 3, 4, 0, 0, NULL,
        "epic spear"},
    {"assets/sprites/weapons/spear_5(100x100).png", 9, 4, 5, 0, 0, NULL,
        "lengendary spear"},
    {"assets/sprites/weapons/axe_1(100x100).png", 10, 0, 1, 0, 0, NULL,
        "basic axe"},
    {"assets/sprites/weapons/axe_2(100x100).png", 11, 1, 2, 0, 0, NULL,
        "good axe"},
    {"assets/sprites/weapons/axe_3(100x100).png", 12, 2, 3, 0, 0, NULL,
        "fancy axe"},
    {"assets/sprites/weapons/axe_4(100x100).png", 13, 3, 4, 0, 0, NULL,
        "epic axe"},
    {"assets/sprites/weapons/axe_5(100x100).png", 14, 4, 5, 0, 0, NULL,
        "lengendary axe"},
    {"assets/sprites/armors/helmet_1(100x100).png", 15, 0, 0, 1, 0, NULL,
        "basic helmet"},
    {"assets/sprites/armors/helmet_2(100x100).png", 16, 1, 0, 2, 0, NULL,
        "good helmet"},
    {"assets/sprites/armors/helmet_3(100x100).png", 17, 2, 0, 3, 0, NULL,
        "fancy helmet"},
    {"assets/sprites/armors/helmet_4(100x100).png", 18, 3, 0, 4, 0, NULL,
        "epic helmet"},
    {"assets/sprites/armors/helmet_5(100x100).png", 19, 4, 0, 5, 0, NULL,
        "lengendary helmet"},
    {"assets/sprites/armors/chestplate_1(100x100).png", 20, 0, 0, 1, 0, NULL,
        "basic chestplate"},
    {"assets/sprites/armors/chestplate_2(100x100).png", 21, 1, 0, 2, 0, NULL,
        "good chestplate"},
    {"assets/sprites/armors/chestplate_3(100x100).png", 22, 2, 0, 3, 0, NULL,
        "fancy chestplate"},
    {"assets/sprites/armors/chestplate_4(100x100).png", 23, 3, 0, 4, 0, NULL,
        "epic chestplate"},
    {"assets/sprites/armors/chestplate_5(100x100).png", 24, 4, 0, 5, 0, NULL,
        "lengendary chestplate"},
    {"assets/sprites/armors/gloves_1(100x100).png", 25, 0, 0, 1, 0, NULL,
        "basic pair of gloves"},
    {"assets/sprites/armors/gloves_2(100x100).png", 26, 1, 0, 2, 0, NULL,
        "good pair of gloves"},
    {"assets/sprites/armors/gloves_3(100x100).png", 27, 2, 0, 3, 0, NULL,
        "fancy pair of gloves"},
    {"assets/sprites/armors/gloves_4(100x100).png", 28, 3, 0, 4, 0, NULL,
        "epic pair of gloves"},
    {"assets/sprites/armors/gloves_5(100x100).png", 29, 4, 0, 5, 0, NULL,
        "lengendary pair of gloves"},
    {"assets/sprites/armors/boots_1(100x100).png", 30, 0, 0, 1, 0, NULL,
        "basic pair of boots"},
    {"assets/sprites/armors/boots_2(100x100).png", 31, 1, 0, 2, 0, NULL,
        "good pair of boots"},
    {"assets/sprites/armors/boots_3(100x100).png", 32, 2, 0, 3, 0, NULL,
        "fancy pair of boots"},
    {"assets/sprites/armors/boots_4(100x100).png", 33, 3, 0, 4, 0, NULL,
        "epic pair of boots"},
    {"assets/sprites/armors/boots_5(100x100).png", 34, 4, 0, 5, 0, NULL,
        "lengendary pair of boots"},
    {"assets/sprites/consumables/bread(100x100).png", 35, 0, 0, 0, 10, NULL,
        "piece of bread"},
    {"assets/sprites/consumables/apple(100x100).png", 36, 0, 0, 0, 10, NULL,
        "beatiful apple"},
    {"assets/sprites/consumables/choco(100x100).png", 37, 0, 0, 0, 10, NULL,
        "pain au chocolat"},
    {"assets/sprites/consumables/meat(100x100).png", 38, 0, 0, 0, 20, NULL,
        "piece of meat"},
};

static void add_an_item(gamedata_t *gamedata, char *item)
{
    backpack_t *new = malloc(sizeof(backpack_t));

    new->item = malloc(sizeof(item_t));
    new->sprite = malloc(sizeof(sprite_t));
    new->item = (item_t *)(&item_list[atoi(item)]);
    new->sprite->rect = (sfIntRect){0, 0, 100, 100};
    new->sprite->texture =
        sfTexture_createFromFile(new->item->asset_path, NULL);
    if (new->sprite->texture == NULL)
        exit(84);
    new->sprite->sprite = sfSprite_create();
    sfSprite_setTexture(new->sprite->sprite, new->sprite->texture, sfFalse);
    sfSprite_setScale(new->sprite->sprite, (sfVector2f){0.25, 0.25});
    new->next = gamedata->inventory->backpack;
    gamedata->inventory->backpack = new;
}

void fill_backpack(gamedata_t *gamedata, config_t *config)
{
    config_t *tmp = get_node("BAG", config);

    gamedata->inventory = malloc(sizeof(inventory_t));
    gamedata->inventory->backsprite = create_sprite(
        "assets/sprites/inventory/inventory(600x1020).png",
        (sfIntRect){0, 0, 600, 1020});
    sfSprite_setScale(gamedata->inventory->backsprite->sprite,
        (sfVector2f){0.25, 0.25});
    gamedata->inventory->backpack = NULL;
    for (int i = 1; tmp != NULL && tmp->line[i] != NULL; i++) {
        add_an_item(gamedata, tmp->line[i]);
    }
    gamedata->inventory->hanging = NULL;
}

static void get_equiped_sprite(gamedata_t *gamedata, int i)
{
    gamedata->inventory->equipment->sprites[i] = NULL;
    if (gamedata->inventory->equipment->equiped[i] != NULL) {
        gamedata->inventory->equipment->sprites[i] = create_sprite(
            gamedata->inventory->equipment->equiped[i]->asset_path,
            (sfIntRect){0, 0, 100, 100});
        sfSprite_setScale(gamedata->inventory->equipment->sprites[i]->sprite,
            (sfVector2f){0.25, 0.25});
    }
}

item_t *copy_item(int id)
{
    item_t *new = malloc(sizeof(item_t) * 1);

    new->asset_path = strdup(item_list[id].asset_path);
    new->atk = item_list[id].atk;
    new->def = item_list[id].def;
    new->function = item_list[id].function;
    new->id = item_list[id].id;
    new->lvl = item_list[id].lvl;
    new->reg = item_list[id].reg;
    new->name = strdup(item_list[id].name);
    return (new);
}

void fill_equipment(gamedata_t *gamedata, config_t *config)
{
    config_t *tmp = get_node("STF", config);
    int val = 0;

    gamedata->inventory->equipment = malloc(sizeof(equipment_t));
    gamedata->inventory->equipsprite = create_sprite(
        "assets/sprites/inventory/equipment(600x500).png",
        (sfIntRect){0, 0, 600, 500});
    sfSprite_setScale(gamedata->inventory->equipsprite->sprite,
        (sfVector2f){0.25, 0.25});
    for (int i = 1; tmp != NULL && tmp->line[i] != NULL && i < 6; i++) {
        val = atoi(tmp->line[i]);
        gamedata->inventory->equipment->equiped[i - 1] = (val != 84 ?
            copy_item(atoi(tmp->line[i])) : NULL);
        get_equiped_sprite(gamedata, i - 1);
    }
}

void fill_skilltree(gamedata_t *gamedata, config_t *config)
{
    (void)config;
    gamedata->inventory->skilltree = malloc(sizeof(skilltree_t));
    gamedata->inventory->skillsprite = create_sprite(
        "assets/sprites/inventory/skill_tree(600x1020).png",
        (sfIntRect){0, 0, 600, 1020});
    sfSprite_setScale(gamedata->inventory->skillsprite->sprite,
        (sfVector2f){0.25, 0.25});
}
