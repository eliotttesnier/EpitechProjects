/*
** EPITECH PROJECT, 2023
** my.h
** File description:
** organized
*/

#pragma once
#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

int mini_printf(const char *format, ...);
int my_putchar(char c);
int my_put_nbr(int nb);
int my_putstr(char const *str);
char *my_strcpy(char *src);
int my_strlen(char const *str);
int my_nbrlen(int nbr);
double my_root(double square);
