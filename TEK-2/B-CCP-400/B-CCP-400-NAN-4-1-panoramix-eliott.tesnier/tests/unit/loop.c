/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-panoramix-eliott.tesnier
** File description:
** loop
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "panoramix.h"

void redirect_all_stdout(void);

Test(panoramix, working_case, .init = redirect_all_stdout)
{
    char *args[] = {"./panoramix", "3", "5", "3", "1"};
    int result = panoramix(5, args);

    cr_assert_eq(result, SUCCESS);
}

Test(panoramix, working_case_2, .init = redirect_all_stdout)
{
    char *args[] = {"./panoramix", "3", "2", "5", "2"};
    int result = panoramix(5, args);

    cr_assert_eq(result, SUCCESS);
}

Test(panoramix, more_refill_than_needed, .init = redirect_all_stdout)
{
    char *args[] = {"./panoramix", "2", "5", "2", "6"};
    int result = panoramix(5, args);

    cr_assert_eq(result, SUCCESS);
}

Test(panoramix, not_enough_refill_to_finish, .init = redirect_all_stdout)
{
    char *args[] = {"./panoramix", "8", "1", "8", "1"};
    int result = panoramix(5, args);

    cr_assert_eq(result, SUCCESS);
}
