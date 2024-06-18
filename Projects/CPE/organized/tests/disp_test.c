/*
** EPITECH PROJECT, 2023
** unit_tests
** File description:
** tests for disp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../libshell/shell.h"

Test(disp, disp_one_disp, .init = redirect_all_std)
{
    organiz orga;
    char *args[50] = {"WIRE", "usb"};
    int ret;

    orga.max_id = -1;
    orga.list = NULL;
    add(&orga, args);
    disp(&orga, args);
    cr_assert_stdout_eq_str("WIRE n°0 - \"usb\" added.\nWIRE n°0 - \"usb\"\n");
}

Test(disp, disp_one_ret, .init = redirect_all_std)
{
    organiz orga;
    char *args[50] = {"WIRE", "usb"};
    int ret;

    orga.max_id = -1;
    orga.list = NULL;
    add(&orga, args);
    ret = disp(&orga, args);
    cr_assert_eq(ret, 84);
}
