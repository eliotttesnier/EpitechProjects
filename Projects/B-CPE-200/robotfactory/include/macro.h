/*
** EPITECH PROJECT, 2024
** lib
** File description:
** macro
*/

#pragma once

#define ABS(i) (i < 0 ? i * -1 : i)
#define IS_NEG(i) (i < 0 ? 1 : 0)
#define IS_UCASE(c) (c >= 65 && c <= 90 ? 1 : 0)
#define IS_LCASE(c) (c >= 97 && c <= 122 ? 1 : 0)
#define IS_NBR(c) (c >= 48 && c <= 57 ? 1 : 0)
#define IS_BTWN(n, a, b) (n > a && n < b ? 1 : 0)
