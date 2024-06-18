/*
** EPITECH PROJECT, 2023
** linked_list.c
** File description:
** linked list related fucntions
*/

#include "header.h"
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

int get_size(char *file)
{
    struct stat sb;

    stat(file, &sb);
    return (sb.st_size);
}

static void add_node_tower2(list_towers **new)
{
    (*new)->area = sfCircleShape_create();
    sfCircleShape_setFillColor((*new)->area, sfTransparent);
    sfCircleShape_setOutlineColor((*new)->area, sfRed);
    sfCircleShape_setOutlineThickness((*new)->area, 1.00);
    sfCircleShape_setRadius((*new)->area, (*new)->radius);
}

int add_node_tower(list_towers **list, char *buff, int ind)
{
    list_towers *new = malloc(sizeof(list_towers));
    sfVector2f vector = {0.00, 0.00};

    new->texture = sfTexture_createFromFile("assets/tower.png", NULL);
    vector.x = (float)pfmy_getnbr(buff, ind) - 50;
    ind += my_len_nbr((int)vector.x + 50) + 1;
    vector.y = (float)pfmy_getnbr(buff, ind) - 50;
    ind += my_len_nbr((int)vector.y + 50) + 1;
    new->radius = 1920 / 100 * pfmy_getnbr(buff, ind);
    ind += my_len_nbr(pfmy_getnbr(buff, ind)) + 1;
    new->towers = sfSprite_create();
    sfSprite_setTexture(new->towers, new->texture, sfFalse);
    sfSprite_setPosition(new->towers, vector);
    add_node_tower2(&new);
    vector.x -= new->radius - 50;
    vector.y -= new->radius - 50;
    sfCircleShape_setPosition(new->area, vector);
    new->next = *list;
    *list = new;
    return (ind);
}

static int add_node_plane2(list_planes **new, char *buff, int ind)
{
    sfVector2f size = {20, 20};

    (*new)->presence = sfFalse;
    (*new)->exploded = sfFalse;
    (*new)->in_radius = sfFalse;
    (*new)->speed = pfmy_getnbr(buff, ind);
    ind += my_len_nbr((*new)->speed) + 1;
    (*new)->delay = pfmy_getnbr(buff, ind);
    ind += my_len_nbr((*new)->delay) + 1;
    (*new)->plane = sfSprite_create();
    (*new)->hitbox = sfRectangleShape_create();
    sfRectangleShape_setOutlineColor((*new)->hitbox, sfBlue);
    sfRectangleShape_setOutlineThickness((*new)->hitbox, 1.00);
    sfRectangleShape_setSize((*new)->hitbox, size);
    sfRectangleShape_setFillColor((*new)->hitbox, sfTransparent);
    return (ind);
}

void calc_incr(list_planes **new, int ax, int ay, sfVector2f vector)
{
    double height = -((vector.y - (double)ay));
    double width = -((vector.x - (double)ax));
    double hyp = sqrt((height * height) + (width * width));
    double nb_move = hyp / (*new)->speed;

    (*new)->incrX = width / nb_move;
    (*new)->incrY = height / nb_move;
}

int add_node_plane(list_planes **list, char *buff, int ind)
{
    list_planes *new = malloc(sizeof(list_planes));
    sfVector2f vector = {0.00, 0.00};

    new->texture = sfTexture_createFromFile("assets/plane.png", NULL);
    vector.x = (float)pfmy_getnbr(buff, ind) - 20;
    ind += my_len_nbr((int)vector.x + 20) + 1;
    vector.y = (float)pfmy_getnbr(buff, ind) - 20;
    ind += my_len_nbr((int)vector.y + 20) + 1;
    new->ax = pfmy_getnbr(buff, ind);
    ind += my_len_nbr(new->ax) + 1;
    new->ay = pfmy_getnbr(buff, ind);
    ind += my_len_nbr(new->ay) + 1;
    ind = add_node_plane2(&new, buff, ind);
    sfSprite_setTexture(new->plane, new->texture, sfFalse);
    sfSprite_setPosition(new->plane, vector);
    sfRectangleShape_setPosition(new->hitbox, vector);
    calc_incr(&new, new->ax, new->ay, vector);
    new->next = *list;
    *list = new;
    return (ind);
}

void fill_list(all_lists *all_l, char **av)
{
    int file_desc = open(av[1], O_RDONLY);
    int size = get_size(av[1]);
    char *buff = malloc(size + 1);
    int i = 0;

    read(file_desc, buff, size);
    buff[size] = '\0';
    while (i < size) {
        if (buff[i] == 'A')
            i = add_node_plane(&all_l->l_planes, buff, i + 2);
        if (buff[i] == 'T')
            i = add_node_tower(&all_l->l_towers, buff, i + 2);
    }
    add_temp(&all_l->l_planes);
}
