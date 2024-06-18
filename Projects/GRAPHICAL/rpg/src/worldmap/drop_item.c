/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** drop_item
*/


#include "rpg_header.h"

static item_t *get_random_sword(void)
{
    int rd = my_random(0, 20);
    item_t *item = NULL;

    if (rd < 5)
        item = copy_item(0);
    if (rd >= 5 && rd < 10)
        item = copy_item(1);
    if (rd >= 10 && rd < 14)
        item = copy_item(2);
    if (rd >= 14 && rd < 18)
        item = copy_item(3);
    if (rd >= 18)
        item = copy_item(4);
    return item;
}

void drop_item_goblin(gamedata_t *game)
{
    int rd = my_random(0, 100);
    item_t *item = NULL;

    if (rd < 45)
        item = copy_item(35);
    if (rd >= 45 && rd < 70)
        item = copy_item(36);
    if (rd >= 70 && rd < 95)
        item = get_random_sword();
    if (rd >= 95)
        item = copy_item(37);
    add_to_inv(game, item);
    put_popup(game, "You got a new item !\nCheck your inventory");
}

void drop_item_wolf(gamedata_t *game)
{
    int rd = my_random(0, 100);
    item_t *item = NULL;

    if (rd < 95)
        item = copy_item(38);
    if (rd >= 95)
        item = copy_item(37);
    add_to_inv(game, item);
    put_popup(game, "You got a new item !\nCheck your inventory");
}

void drop_item_golem(gamedata_t *game)
{
    int rd = my_random(0, 38);
    item_t *item = NULL;

    item = copy_item(rd);
    add_to_inv(game, item);
    put_popup(game, "You got a new item !\nCheck your inventory");
}

void drop_item(gamedata_t *game, ennemy_t *eny)
{
    eny_t type = get_eny_type(eny);

    if (is_inv_full(game))
        return;
    if (type == GOBLIN) {
        drop_item_goblin(game);
        return;
    }
    if (type == WOLF) {
        drop_item_wolf(game);
        return;
    }
    if (type == GOLEM) {
        drop_item_golem(game);
        return;
    }
}
