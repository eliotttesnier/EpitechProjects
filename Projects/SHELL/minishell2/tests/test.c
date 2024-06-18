/*
** EPITECH PROJECT, 2023
** unit_tests
** File description:
** tests for secured
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../includes/header.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

// TESTS :

Test(mysh, too_many_arguments, .init = redirect_all_std)
{
    int mysh = 0;

    mysh = system("echo \"ls\" | ./mysh arg");
    cr_assert_eq(mysh, 21504);
}

Test(mysh, unknown_command, .init = redirect_all_std)
{
    int mysh = 0;
    int tcsh = 0;

    tcsh = system("echo \"coucou\" | tcsh");
    mysh = system("echo \"coucou\" | ./mysh");
    cr_assert_eq(mysh, tcsh);
}

Test(mysh, unknown_command_path, .init = redirect_all_std)
{
    int mysh = 0;
    int tcsh = 0;

    tcsh = system("echo \"./coucou\" | tcsh");
    mysh = system("echo \"./coucou\" | ./mysh");
    cr_assert_eq(mysh, tcsh);
}

Test(mysh, env, .init = redirect_all_std)
{
    int mysh = 0;
    int tcsh = 0;

    tcsh = system("echo \"env\" | tcsh");
    mysh = system("echo \"env\" | ./mysh");
    cr_assert_eq(mysh, tcsh);
}

Test(mysh, cd_cannot_find, .init = redirect_all_std)
{
    int mysh = 0;
    int tcsh = 0;

    tcsh = system("echo \"cd nofile\" | tcsh");
    mysh = system("echo \"cd nofile\" | ./mysh");
    cr_assert_eq(mysh, tcsh);
}

Test(mysh, cd_no_args, .init = redirect_all_std)
{
    int mysh = 0;
    int tcsh = 0;

    tcsh = system("echo \"cd\" | tcsh");
    mysh = system("echo \"cd\" | ./mysh");
    cr_assert_eq(mysh, tcsh);
}

Test(mysh, exit, .init = redirect_all_std)
{
    int mysh = 0;
    int tcsh = 0;

    tcsh = system("echo \"exit\" | tcsh");
    mysh = system("echo \"exit\" | ./mysh");
    cr_assert_eq(mysh, tcsh);
}

Test(mysh, pwd, .init = redirect_all_std)
{
    int mysh = 0;
    int tcsh = 0;

    tcsh = system("echo \"pwd\" | tcsh");
    mysh = system("echo \"pwd\" | ./mysh");
    cr_assert_eq(mysh, tcsh);
}

Test(mysh, ls_nofile, .init = redirect_all_std)
{
    int mysh = 0;
    int tcsh = 0;

    tcsh = system("echo \"ls nofile\" | tcsh");
    mysh = system("echo \"ls nofile\" | ./mysh");
    cr_assert_eq(mysh, tcsh);
}

Test(mysh, ls, .init = redirect_all_std)
{
    int mysh = 0;
    int tcsh = 0;

    tcsh = system("echo \"ls\" | tcsh");
    mysh = system("echo \"ls\" | ./mysh");
    cr_assert_eq(mysh, tcsh);
}
