/*
** EPITECH PROJECT, 2024
** n4s
** File description:
** main
*/

#include "header.h"

static void fill_direction(direction_t *dir)
{
    float treshold = 1000;
    char **arr = NULL;

    dprintf(1, "GET_INFO_LIDAR\n");
    arr = str_to_array(get_output(), ":");
    dir->front = (atof(arr[18]) + atof(arr[19])) / 2;
    dir->left = (atof(arr[3]) + atof(arr[4])) / 2;
    dir->right = (atof(arr[33]) + atof(arr[34]) / 2);
    dir->lf = (atof(arr[10]) + atof(arr[11]) / 2);
    dir->rf = (atof(arr[26]) + atof(arr[27]) / 2);
    if (dir->front > treshold)
        dir->front = treshold;
    if (dir->right > treshold)
        dir->right = treshold;
    if (dir->left > treshold)
        dir->left = treshold;
    if (dir->rf > treshold)
        dir->rf = treshold;
    if (dir->lf > treshold)
        dir->lf = treshold;
}

static float calc_backwards(float left, float right, float front)
{
    char **arr;

    dprintf(1, "GET_CURRENT_SPEED\n");
    arr = str_to_array(get_output(), ":");
    if (front < 25 || left < 25 || right < 25)
        return (-0.5);
    free(arr);
    return (0);
}

bool is_biggest(direction_t *dir, float try)
{
    if (try < dir->front)
        return (false);
    if (try < dir->left)
        return (false);
    if (try < dir->lf)
        return (false);
    if (try < dir->rf)
        return (false);
    if (try < dir->right)
        return (false);
    return (true);
}

float calc_direction(direction_t *dir)
{
    if (is_biggest(dir, dir->front) && is_biggest(dir, dir->left) && dir->right < 500)
        return (0.25);
    if (is_biggest(dir, dir->front) && is_biggest(dir, dir->right) && dir->left < 500)
        return (-0.25);
    if (is_biggest(dir, dir->front))
        return (0.00);
    if (is_biggest(dir, dir->rf))
        return (-0.25);
    if (is_biggest(dir, dir->lf))
        return (0.25);
    if (is_biggest(dir, dir->right))
        return (-0.5);
    if (is_biggest(dir, dir->left))
        return (0.5);
    return (0);
}

static float calc_speed(direction_t *dir, float direc)
{
    if (direc == 0.0 && (dir->front == 1000 && dir->lf > 900 && dir->rf > 900))
        return (0.5);
    if (direc == 0.25 || direc == -0.25)
        return (0.4);
    return (0.2);
}

void watch_wall(float *speed, float *direc)
{
    direction_t dir;
    float multiplier = 0.5;

    fill_direction(&dir);
    if (dir.front < 500 || dir.lf < 300 || dir.rf < 300)
        multiplier = 0.75;
    if (dir.front < 300 || dir.lf < 200 || dir.rf < 200)
        multiplier = 1.0;
    *direc = calc_direction(&dir) * multiplier;
    *speed = calc_speed(&dir, *direc);
    if (calc_backwards(dir.left, dir.right, dir.front) != 0) {
        *direc = 0;
        *speed = -0.5;
    }
    dprintf(2, "direct : %9f\n", *direc);
}

static void vroom_sound(sfMusic *vroom)
{
    int rdm = rand() % 15;

    if (sfMusic_getStatus(vroom) == sfStopped && rdm == 1)
        sfMusic_play(vroom);
    if (sfMusic_getPlayingOffset(vroom).microseconds > 9000000)
        sfMusic_stop(vroom);
}

int main(void)
{
    bool end = false;
    float speed = 0.3;
    float dir = 0.0;
    sfMusic *mus = sfMusic_createFromFile("max.wav");
    sfMusic *vroom = sfMusic_createFromFile("vroom.wav");

    start();
    sfMusic_setLoop(mus, sfTrue);
    sfMusic_play(mus);
    while (end == false) {
        watch_wall(&speed, &dir);
        direction(dir, &end);
        if (end == true)
            break;
        forward(speed, &end);
        vroom_sound(vroom);
    }
    forward(0.1, &end);
    stop();
    sfMusic_destroy(mus);
    sfMusic_destroy(vroom);
    return (0);
}
