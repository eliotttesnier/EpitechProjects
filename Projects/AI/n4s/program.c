/*
** EPITECH PROJECT, 2024
** n4s
** File description:
** program
*/

#include "header.h"

float calc_backwards(float left, float right, float front)
{
    if (front < 25 || left < 25 || right < 25)
        return (-0.5);
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
    if (is_biggest(dir, dir->front) &&
        is_biggest(dir, dir->left) && dir->right < 500)
        return (0.25);
    if (is_biggest(dir, dir->front) &&
        is_biggest(dir, dir->right) && dir->left < 500)
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

float calc_speed(direction_t *dir, float direc)
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
