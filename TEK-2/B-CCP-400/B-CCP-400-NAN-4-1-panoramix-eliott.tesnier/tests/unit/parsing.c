/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-panoramix-eliott.tesnier
** File description:
** parsing
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "panoramix.h"

void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(parse_arguments, valid_arguments)
{
    char *argv[] = {"./panoramix", "5", "10", "3", "2"};
    cli_args_t args = parse_arguments(5, argv);

    cr_assert_eq(args.nb_villagers, 5);
    cr_assert_eq(args.pot_size, 10);
    cr_assert_eq(args.nb_fights, 3);
    cr_assert_eq(args.nb_refills, 2);
}

Test(parse_arguments, invalid_arguments_zero, .exit_code = FAILURE, .init = redirect_all_stdout)
{
    char *argv[] = {"./panoramix", "0", "0", "0", "0"};

    parse_arguments(5, argv);
    cr_assert_fail("The function did not exit as expected");
}

Test(parse_arguments, invalid_arguments_negative, .exit_code = FAILURE, .init = redirect_all_stdout)
{
    char *argv[] = {"./panoramix", "-1", "-1", "-1", "-1"};

    parse_arguments(5, argv);
    cr_assert_fail("The function did not exit as expected");
}

Test(parse_arguments, invalid_arguments_negative_1, .exit_code = FAILURE, .init = redirect_all_stdout)
{
    char *argv[] = {"./panoramix", "-1", "1", "1", "1"};

    parse_arguments(5, argv);
    cr_assert_fail("The function did not exit as expected");
}

Test(parse_arguments, invalid_arguments_negative_2, .exit_code = FAILURE, .init = redirect_all_stdout)
{
    char *argv[] = {"./panoramix", "1", "-1", "1", "1"};

    parse_arguments(5, argv);
    cr_assert_fail("The function did not exit as expected");
}

Test(parse_arguments, invalid_arguments_negative_3, .exit_code = FAILURE, .init = redirect_all_stdout)
{
    char *argv[] = {"./panoramix", "1", "1", "-1", "1"};

    parse_arguments(5, argv);
    cr_assert_fail("The function did not exit as expected");
}

Test(parse_arguments, invalid_arguments_negative_4, .exit_code = FAILURE, .init = redirect_all_stdout)
{
    char *argv[] = {"./panoramix", "1", "1", "1", "-1"};

    parse_arguments(5, argv);
    cr_assert_fail("The function did not exit as expected");
}

Test(parse_arguments, invalid_arguments_non_integer, .exit_code = FAILURE, .init = redirect_all_stdout)
{
    char *argv[] = {"./panoramix", "5", "10", "3", "abc"};

    parse_arguments(5, argv);
    cr_assert_fail("The function did not exit as expected");
}

Test(parse_arguments, invalid_arguments_too_few, .exit_code = FAILURE, .init = redirect_all_stdout)
{
    char *argv[] = {"./panoramix", "5", "10", "3"};

    parse_arguments(4, argv);
    cr_assert_fail("The function did not exit as expected");
}

Test(parse_arguments, invalid_arguments_too_many, .exit_code = FAILURE, .init = redirect_all_stdout)
{
    char *argv[] = {"./panoramix", "5", "10", "3", "2", "extra"};

    parse_arguments(6, argv);
    cr_assert_fail("The function did not exit as expected");
}
