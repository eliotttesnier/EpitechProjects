/*
** EPITECH PROJECT, 2023
** unit_tests
** File description:
** tests for sort
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../libshell/shell.h"

Test(sort, sort_type, .init = redirect_all_std)
{
    organiz orga;
    char *args[50] = {"WIRE", "usb", "DEVICE", "andreas"};
    char *sorting[50] = {"TYPE"};
    int ret;

    orga.max_id = -1;
    orga.list = NULL;
    add(&orga, args);
    sort(&orga, sorting);
    disp(&orga, args);
    cr_assert_stdout_eq_str("WIRE n°0 - \"usb\" added.\nDEVICE n°1 - \"andreas\" added.\nDEVICE n°1 - \"andreas\"\nWIRE n°0 - \"usb\"\n");
}

Test(sort, sort_type_r, .init = redirect_all_std)
{
    organiz orga;
    char *args[50] = {"WIRE", "usb", "DEVICE", "andreas"};
    char *sorting[50] = {"TYPE", "-r"};
    int ret;

    orga.max_id = -1;
    orga.list = NULL;
    add(&orga, args);
    sort(&orga, sorting);
    disp(&orga, args);
    cr_assert_stdout_eq_str("WIRE n°0 - \"usb\" added.\nDEVICE n°1 - \"andreas\" added.\nWIRE n°0 - \"usb\"\nDEVICE n°1 - \"andreas\"\n");
}

Test(sort, sort_name, .init = redirect_all_std)
{
    organiz orga;
    char *args[50] = {"WIRE", "usb", "DEVICE", "andreas"};
    char *sorting[50] = {"NAME"};
    int ret;

    orga.max_id = -1;
    orga.list = NULL;
    add(&orga, args);
    sort(&orga, sorting);
    disp(&orga, args);
    cr_assert_stdout_eq_str("WIRE n°0 - \"usb\" added.\nDEVICE n°1 - \"andreas\" added.\nDEVICE n°1 - \"andreas\"\nWIRE n°0 - \"usb\"\n");
}

Test(sort, sort_name_r, .init = redirect_all_std)
{
    organiz orga;
    char *args[50] = {"WIRE", "usb", "DEVICE", "andreas"};
    char *sorting[50] = {"NAME", "-r"};
    int ret;

    orga.max_id = -1;
    orga.list = NULL;
    add(&orga, args);
    sort(&orga, sorting);
    disp(&orga, args);
    cr_assert_stdout_eq_str("WIRE n°0 - \"usb\" added.\nDEVICE n°1 - \"andreas\" added.\nWIRE n°0 - \"usb\"\nDEVICE n°1 - \"andreas\"\n");
}

Test(sort, sort_id, .init = redirect_all_std)
{
    organiz orga;
    char *args[50] = {"WIRE", "usb", "DEVICE", "andreas"};
    char *sorting[50] = {"ID"};
    int ret;

    orga.max_id = -1;
    orga.list = NULL;
    add(&orga, args);
    sort(&orga, sorting);
    disp(&orga, args);
    cr_assert_stdout_eq_str("WIRE n°0 - \"usb\" added.\nDEVICE n°1 - \"andreas\" added.\nWIRE n°0 - \"usb\"\nDEVICE n°1 - \"andreas\"\n");
}

Test(sort, sort_id_r, .init = redirect_all_std)
{
    organiz orga;
    char *args[50] = {"WIRE", "usb", "DEVICE", "andreas"};
    char *sorting[50] = {"ID", "-r"};
    int ret;

    orga.max_id = -1;
    orga.list = NULL;
    add(&orga, args);
    sort(&orga, sorting);
    disp(&orga, args);
    cr_assert_stdout_eq_str("WIRE n°0 - \"usb\" added.\nDEVICE n°1 - \"andreas\" added.\nDEVICE n°1 - \"andreas\"\nWIRE n°0 - \"usb\"\n");
}

Test(sort, sort_unknow, .init = redirect_all_std)
{
    organiz orga;
    char *args[50] = {"WIRE", "usb", "DEVICE", "andreas"};
    char *sorting[50] = {"TEST"};
    int ret;

    orga.max_id = -1;
    orga.list = NULL;
    add(&orga, args);
    ret = sort(&orga, sorting);
    cr_assert_eq(ret, 84);
}

Test(sort, sort_null, .init = redirect_all_std)
{
    organiz orga;
    char *args[50] = {"WIRE", "usb", "DEVICE", "andreas"};
    char *sorting[50] = {NULL};
    int ret;

    orga.max_id = -1;
    orga.list = NULL;
    add(&orga, args);
    ret = sort(&orga, sorting);
    cr_assert_eq(ret, 84);
}

Test(sort, sort_null_list, .init = redirect_all_std)
{
    organiz orga;
    char *args[50] = {"WIRE", "usb", "DEVICE", "andreas"};
    char *sorting[50] = {NULL};
    int ret;

    orga.max_id = -1;
    orga.list = NULL;
    ret = sort(&orga, sorting);
    cr_assert_eq(ret, 84);
}

Test(sort, sort_only_r, .init = redirect_all_std)
{
    organiz orga;
    char *args[50] = {"WIRE", "usb", "DEVICE", "andreas"};
    char *sorting[50] = {"-r"};
    int ret;

    orga.max_id = -1;
    orga.list = NULL;
    add(&orga, args);
    ret = sort(&orga, sorting);
    cr_assert_eq(ret, 84);
}

Test(sort, sort_two_names, .init = redirect_all_std)
{
    organiz orga;
    char *args[50] = {"WIRE", "usb", "DEVICE", "andreas"};
    char *sorting[50] = {"NAME", "NAME"};
    int ret;

    orga.max_id = -1;
    orga.list = NULL;
    add(&orga, args);
    ret = sort(&orga, sorting);
    cr_assert_eq(ret, 0);
}
