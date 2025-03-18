/*
** EPITECH PROJECT, 2023
** unit_tests
** File description:
** tests for del
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../libshell/shell.h"

Test(del, delete_one, .init = redirect_all_std)
{
    organiz orga;
    char *args[50] = {"WIRE", "usb", "DEVICE", "pc"};
    char *id[50] = {"0"};
    int ret;

    orga.max_id = -1;
    orga.list = NULL;
    add(&orga, args);
    ret = del(&orga, id);
    cr_assert_eq(ret, 0);
    //cr_assert_stdout_eq_str("WIRE n°0 - \"usb\" added.\nWIRE n°0 - \"usb\" deleted.");
}

Test(del, delete_null_args, .init = redirect_all_std)
{
    organiz orga;
    char *args[50] = {"WIRE", "usb", "DEVICE", "pc"};
    char *id[50] = {NULL};
    int ret;

    orga.max_id = -1;
    orga.list = NULL;
    add(&orga, args);
    ret = del(&orga, id);
    cr_assert_eq(ret, 84);
    //cr_assert_stdout_eq_str("WIRE n°0 - \"usb\" deleted.");
}


Test(del, delete_non_existing, .init = redirect_all_std)
{
    organiz orga;
    char *args[50] = {"WIRE", "usb", "DEVICE", "pc"};
    char *id[50] = {"9"};
    int ret;

    orga.max_id = -1;
    orga.list = NULL;
    add(&orga, args);
    ret = del(&orga, id);
    cr_assert_eq(ret, 0);
    //cr_assert_stdout_eq_str("WIRE n°0 - \"usb\" deleted.");
}


Test(del, delete_multiple, .init = redirect_all_std)
{
    organiz orga;
    char *args[50] = {"WIRE", "usb", "DEVICE", "pc"};
    char *id[50] = {"0", "1"};
    int ret;

    orga.max_id = -1;
    orga.list = NULL;
    add(&orga, args);
    ret = del(&orga, id);
    cr_assert_eq(ret, 0);
    //cr_assert_stdout_eq_str("WIRE n°0 - \"usb\" deleted.");
}


Test(del, delete_nothing, .init = redirect_all_std)
{
    organiz orga;
    char *args[50] = {"PROCESSOR", "usb", "SENSOR", "pc"};
    char *id[50] = {""};
    int ret;

    orga.max_id = -1;
    orga.list = NULL;
    add(&orga, args);
    ret = del(&orga, id);
    cr_assert_eq(ret, 84);
    //cr_assert_stdout_eq_str("WIRE n°0 - \"usb\" deleted.");
}

Test(del, delete_null, .init = redirect_all_std)
{
    organiz orga;
    char *args[50] = {""};
    char *id[50] = {"0"};
    int ret;

    orga.max_id = -1;
    orga.list = NULL;
    ret = del(&orga, id);
    cr_assert_eq(ret, 84);
    //cr_assert_stdout_eq_str("WIRE n°0 - \"usb\" deleted.");
}

Test(del, delete_chars, .init = redirect_all_std)
{
    organiz orga;
    char *args[50] = {"ACTUATOR", "usb", "WIRE", "pc"};
    char *id[50] = {"abc"};
    int ret;

    orga.max_id = -1;
    orga.list = NULL;
    add(&orga, args);
    ret = del(&orga, id);
    cr_assert_eq(ret, 84);
    //cr_assert_stdout_eq_str("WIRE n°0 - \"usb\" deleted.");
}
