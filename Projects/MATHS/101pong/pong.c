/*
** EPITECH PROJECT, 2023
** pong
** File description:
** pong
*/

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>

int main(int ac, char **av)
{
    if (ac < 8) {
        write(2, "not enough arguments\n", 22);
        exit(84);
    }
    if (ac > 8) {
        write(2, "too many arguments\n", 20);
        exit(84);
    }
    for (int i = 1; i < 8; i++) {
        for (int j = 0; j < strlen(av[i]); j++) {
            if (av[i][j] != '.' && av[i][j] != '-' && (av[i][j] < '0' || av[i][j] > '9')) {
                write(2, "incorrect argument\n", 20);
                exit(84);
            }
        }
    }
    double x0 = strtod(av[1], NULL);
    double y0 = strtod(av[2], NULL);
    double z0 = strtod(av[3], NULL);
    double x1 = strtod(av[4], NULL);
    double y1 = strtod(av[5], NULL);
    double z1 = strtod(av[6], NULL);
    int n = (int)strtod(av[7], NULL);
    if ((double)n != strtod(av[7], NULL)) {
        write(2, "wrong format for last argument\n", 32);
        exit(84);
    }
    if (n < 0) {
        write(2, "negative time shift\n",21);
        exit(84);
    }
    double Vx1 = x1 - x0;
    double Vy1 = y1 - y0;
    double Vz1 = z1 - z0;
    printf("The velocity vector of the ball is:\n(%.2f, %.2f, %.2f)\n", Vx1, Vy1, Vz1);
    printf("At time t + %i, ball coordinates will be:\n", n);
    double Nx = x1 + (double)n * Vx1;
    double Ny = y1 + (double)n * Vy1;
    double Nz = z1 + (double)n * Vz1;
    printf("(%.2f, %.2f, %.2f)\n", Nx, Ny, Nz);
    double z2 = z1 + (double)2 * Vz1;
    double VXab = (x1 - x0);
    double VYab = (y1 - y0);
    double VZab = (z1 - z0);
    double len_Vab = sqrt((VXab * VXab) + (VYab * VYab) + (VZab * VZab));
    double len_Vah = z0 - z1;
    double angle = asin(len_Vah / len_Vab);
    angle = (angle * 180) / M_PI;
    if (angle < 0.00)
    angle = angle * (double)-1;
    if (z0 == 0 && z1 == 0)
        printf("The incidence angle is: 0 degrees\n");
    else if (z1 >= 0) {
        if (z2 >= z1)
            printf("The ball won't reach the paddle.\n");
        if (z2 < z1)
            printf("The incidence angle is:\n%.2f degrees\n", angle);
    }
    if (z1 < 0) {
        if (z2 <= z1)
            printf("The ball won't reach the paddle.\n");
        if (z2 > z1)
            printf("The incidence angle is:\n%.2f degrees\n", angle);
    }
    exit(0);
}
