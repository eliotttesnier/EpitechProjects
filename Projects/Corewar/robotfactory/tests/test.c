/*
** EPITECH PROJECT, 2023
** unit_tests
** File description:
** tests for robotfactory
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/robot_header.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(format_arr, formatting_simple_arr, .init = redirect_all_std)
{
    char **arr = malloc(sizeof(char *) * 6);

    arr[0] = strdup("    Salut");
    arr[1] = strdup("sti #lesgo");
    arr[2] = strdup("Je #su fan");
    arr[3] = strdup("#test");
    arr[4] = strdup("ma");
    arr[5] = NULL;
    format_arr(arr);
    cr_assert_str_eq(arr[0], "Salut");
    cr_assert_str_eq(arr[1], "sti ");
    cr_assert_str_eq(arr[2], "Je ");
    cr_assert_str_eq(arr[3], "");
    cr_assert_str_eq(arr[4], "ma");
}

Test(mini_printf, coverage, .init = redirect_all_std)
{
    mini_printf("%d", -15);
    mini_printf("%%");
    mini_printf("%c", 'c');
    mini_printf("%i", -15);
    mini_printf("%b", -15);
    mini_printf("okay");
}
