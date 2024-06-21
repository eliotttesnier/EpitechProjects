/*
** EPITECH PROJECT, 2024
** fozzbazz
** File description:
** fozzbazz stumper
*/

#include "include/header.h"

int error_cases(int ac, char **av)
{
    if (ac != 3)
        return (84);
    for (int i = 0; av[1][i] != '\0'; i++) {
        if (IS_NUMBER(av[1][i]) == 0 && av[1][i] != '-')
            return (84);
    }
    for (int i = 0; av[2][i] != '\0'; i++) {
        if (IS_NUMBER(av[2][i]) == 0 && av[2][i] != '-')
            return (84);
    }
    if (atoi(av[1]) > atoi(av[2]))
        return (84);
    return (0);
}

void check_condition(int number)
{
    if (number % 2 == 0 && number % 9 == 0) {
        printf("FozzBazz\n");
        return;
    }
    if (number % 2 == 0) {
        printf("Fozz\n");
        return;
    }
    if (number % 9 == 0) {
        printf("Bazz\n");
        return;
    }
    printf("%i\n", number);
}

int printing(int num1, int num2)
{
    for (int i = 0; num1 + i <= num2; i++) {
        check_condition(num1 + i);
    }
    return (0);
}

int fozzbazz(int ac, char **av)
{
    if (error_cases(ac, av) == 84)
        return (84);
    return (printing(atoi(av[1]), atoi(av[2])));
}
