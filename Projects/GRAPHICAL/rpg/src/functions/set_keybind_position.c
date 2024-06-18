/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** ventory
*/

#include "rpg_header.h"

static void set_pos_keybind_button_two(struct option_menu_s *optionmenu,
    sfFloatRect pos)
{
    pos = sfText_getGlobalBounds(optionmenu->inventory->key->text);
    sfText_setPosition(optionmenu->inventory->key->text,
        (sfVector2f){pos.left - (pos.width / 2), pos.top - (pos.height / 2)});
    pos = sfText_getGlobalBounds(optionmenu->attack->key->text);
    sfText_setPosition(optionmenu->attack->key->text,
        (sfVector2f){pos.left - (pos.width / 2), pos.top - (pos.height / 2)});
    pos = sfText_getGlobalBounds(optionmenu->fire_spell->key->text);
    sfText_setPosition(optionmenu->fire_spell->key->text,
        (sfVector2f){pos.left - (pos.width / 2), pos.top - (pos.height / 2)});
    pos = sfText_getGlobalBounds(optionmenu->heal_spell->key->text);
    sfText_setPosition(optionmenu->heal_spell->key->text,
        (sfVector2f){pos.left - (pos.width / 2), pos.top - (pos.height / 2)});
    pos = sfText_getGlobalBounds(optionmenu->stun_spell->key->text);
    sfText_setPosition(optionmenu->stun_spell->key->text,
        (sfVector2f){pos.left - (pos.width / 2), pos.top - (pos.height / 2)});
}

void set_pos_keybind_button(struct option_menu_s *optionmenu)
{
    sfFloatRect pos = sfText_getGlobalBounds(optionmenu->forward->key->text);

    sfText_setPosition(optionmenu->forward->key->text,
        (sfVector2f){pos.left - (pos.width / 2), pos.top - (pos.height / 2)});
    pos = sfText_getGlobalBounds(optionmenu->backward->key->text);
    sfText_setPosition(optionmenu->backward->key->text,
        (sfVector2f){pos.left - (pos.width / 2), pos.top - (pos.height / 2)});
    pos = sfText_getGlobalBounds(optionmenu->left->key->text);
    sfText_setPosition(optionmenu->left->key->text,
        (sfVector2f){pos.left - (pos.width / 2), pos.top - (pos.height / 2)});
    pos = sfText_getGlobalBounds(optionmenu->right->key->text);
    sfText_setPosition(optionmenu->right->key->text,
        (sfVector2f){pos.left - (pos.width / 2), pos.top - (pos.height / 2)});
    pos = sfText_getGlobalBounds(optionmenu->interact->key->text);
    sfText_setPosition(optionmenu->interact->key->text,
        (sfVector2f){pos.left - (pos.width / 2), pos.top - (pos.height / 2)});
    set_pos_keybind_button_two(optionmenu, pos);
}
