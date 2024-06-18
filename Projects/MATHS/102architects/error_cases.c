/*
** EPITECH PROJECT, 2023
** error_cases.c
** File description:
** error_cases
*/

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include "header.h"

void check_if_one_arg(int i, char **av, int ac)
{
    if ((i + 1) <= ac){
        for (int j = 0; j < strlen(av[i + 1]); j++) {
            if (av[i + 1][j] != '.' && av[i + 1][j] != '-' && (av[i + 1][j] < '0' || av[i + 1][j] > '9')) {
                write(2, "incorrect argument\n", 20);
                exit(84);
            }
        }
    }
    if ((i + 2) < ac) {
        if (av[i + 2][0] != '-') {
            write(2, "incorrect argument\n", 20);
            exit(84);
        }
    }
}

void check_if_dooos_arg(int i, char **av, int ac)
{
    if ((i + 1) < ac){
        for (int j = 0; j < strlen(av[i + 1]); j++) {
            if (av[i + 1][j] != '.' && av[i + 1][j] != '-' && (av[i + 1][j] < '0' || av[i + 1][j] > '9')) {
                write(2, "incorrect argument\n", 20);
                exit(84);
            }
        }
    } else {
        exit(84);
    }
    if ((i + 2) < ac) {
        for (int j = 0; j < strlen(av[i + 2]); j++) {
            if (av[i + 2][j] != '.' && av[i + 2][j] != '-' && (av[i + 2][j] < '0' || av[i + 2][j] > '9')) {
                write(2, "incorrect argument\n", 20);
                exit(84);
            }
        }
    if ((i + 3) < ac) {
        if (av[i + 3][0] != '-') {
            write(2, "incorrect argument\n", 20);
            exit(84);
        }
    }
    } else {
        exit(84);
    }
}

void dos(int ac, char **av)
{
    for (int i = 0; i < ac; i++) {
        if ((av[i][0] == '-') && ((av[i][1] == 'z') || av[i][1] == 't') && (av[i][2] == '\0')) {
            check_if_dooos_arg(i, av, ac);
        }
        if ((av[i][0] == '-') && ((av[i][1] == 'r') || av[i][1] == 's') && (av[i][2] == '\0')) {
            check_if_one_arg(i, av, ac);
        }
    }
}

void error_cases(int ac, char **av)
{
    if (ac < 5)
        exit (84);
    for (int i = 1; i < 3; i++) {
        for (int j = 0; j < strlen(av[i]); j++) {
            if (av[i][j] != '.' && av[i][j] != '-' && (av[i][j] < '0' || av[i][j] > '9')) {
                write(2, "incorrect argument\n", 20);
                exit(84);
            }
        }
    }
    for (int i = 1; i < ac; i++) {
        if (av[i][0] == '-' && strlen(av[i]) == 1) {
            write(2, "incorrect argument\n", 20);
            exit(84);
        }
        if (av[i][0] == '-' && av[i][1] > '9' && av[i][1] < '0') {
            if (av[i][1] != 'r' && av[i][1] != 's' &&
                av[i][1] != 'z' && av[i][1] != 't') {
                write(2, "incorrect argument\n", 20);
                exit(84);
            }
            printf("i = %i len = %i\n", i, strlen(av[i]));
            if (strlen(av[i]) != 2)
                exit(84);
        }
        if (i == 3) {
            if (av[i][0] != '-')
                exit(84);
            if (av[i][1] != 'r' && av[i][1] != 's' &&
                av[i][1] != 'z' && av[i][1] != 't') {
                write(2, "incorrect argument\n", 20);
                exit(84);
            }
        }
    }
    dos(ac, av);
}