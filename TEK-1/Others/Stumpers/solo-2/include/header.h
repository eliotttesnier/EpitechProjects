/*
** EPITECH PROJECT, 2023
** navy_header.h
** File description:
** my_navy header
*/

#pragma once

#define _XOPEN_SOURCE 700
#define IS_LETTER(c) ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ? 1 : 0)
#define IS_UPC(c) (c >= 'A' && c <= 'Z' ? 1 : 0)
#define IS_LOWC(c) (c >= 'a' && c <= 'z' ? 1 : 0)
#define IS_NUMBER(c) (c >= '0' && c <= '9' ? 1 : 0)
#define ABS(nb) (nb < 0 ? nb * -1 : nb)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>

int fozzbazz(int ac, char **av);
