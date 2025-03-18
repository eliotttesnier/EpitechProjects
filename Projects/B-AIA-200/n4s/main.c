/*
** EPITECH PROJECT, 2024
** n4s
** File description:
** main
*/

#include "header.h"

int main(void)
{
    bool end = false;
    float speed = 0.3;
    float dir = 0.0;

    start();
    while (end == false) {
        watch_wall(&speed, &dir);
        direction(dir, &end);
        if (end == true)
            break;
        forward(speed, &end);
    }
    forward(0.1, &end);
    stop();
    return (0);
}
