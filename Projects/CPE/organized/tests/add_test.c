/*
** EPITECH PROJECT, 2023
** unit_tests
** File description:
** tests for add
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../libshell/shell.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(add, adding_one_node, .init = redirect_all_std)
{
    organiz orga;
    char *args[50] = {"WIRE", "usb"};
    int ret;

    orga.max_id = -1;
    orga.list = NULL;
    ret = add(&orga, args);
    cr_assert_stdout_eq_str("WIRE n°0 - \"usb\" added.\n");
}

Test(add, adding_multiple_nodes, .init = redirect_all_std)
{
    organiz orga;
    char *args[50] = {"WIRE", "usb", "SENSOR", "plate", "DEVICE", "pc"};
    int ret;

    orga.max_id = -1;
    orga.list = NULL;
    ret = add(&orga, args);
    cr_assert_stdout_eq_str("WIRE n°0 - \"usb\" added.\nSENSOR n°1 - \"plate\" added.\nDEVICE n°2 - \"pc\" added.\n");
}

Test(add, adding_nothing, .init = redirect_all_std)
{
    organiz orga;
    char *args[50] = {""};
    int ret;

    orga.max_id = -1;
    orga.list = NULL;
    ret = add(&orga, args);
    cr_assert_eq(ret, 84);
}

Test(add, adding_false, .init = redirect_all_std)
{
    organiz orga;
    char *args[50] = {"test", "salam"};
    int ret;

    orga.max_id = -1;
    orga.list = NULL;
    ret = add(&orga, args);
    cr_assert_eq(ret, 84);
}

Test(add, adding_processot, .init = redirect_all_std)
{
    organiz orga;
    char *args[50] = {"PROCESSOT", "usb"};
    int ret;

    orga.max_id = -1;
    orga.list = NULL;
    ret = add(&orga, args);
    cr_assert_eq(ret, 84);
}

Test(add, adding_actutor, .init = redirect_all_std)
{
    organiz orga;
    char *args[50] = {"ACTUATOR", "usb"};
    int ret;

    orga.max_id = -1;
    orga.list = NULL;
    ret = add(&orga, args);
    cr_assert_eq(ret, 0);
}

Test(add, adding_actutot, .init = redirect_all_std)
{
    organiz orga;
    char *args[50] = {"ACTUATOT", "usb"};
    int ret;

    orga.max_id = -1;
    orga.list = NULL;
    ret = add(&orga, args);
    cr_assert_eq(ret, 84);
}
