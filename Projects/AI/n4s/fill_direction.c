/*
** EPITECH PROJECT, 2024
** n4s
** File description:
** fill_direction
*/

#include "header.h"

void fill_direction(direction_t *dir)
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
