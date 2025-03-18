/*
** EPITECH PROJECT, 2025
** ASM
** File description:
** tests_strlen
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

extern size_t strlen(const char *str);

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

// strlen
Test(strlen, test_strlen, .init = redirect_all_std)
{
    char *str = "Hello World!";
    cr_assert_eq(strlen(str), 12);
}

Test(strlen, test_strlen_empty, .init = redirect_all_std)
{
    char *str = "";
    cr_assert_eq(strlen(str), 0);
}

Test(strlen, test_strlen_single_char, .init = redirect_all_std)
{
    char *str = "A";
    cr_assert_eq(strlen(str), 1);
}

Test(strlen, test_strlen_whitespace, .init = redirect_all_std)
{
    char *str = "   ";
    cr_assert_eq(strlen(str), 3);
}

Test(strlen, test_strlen_special_chars, .init = redirect_all_std)
{
    char *str = "!@#$%^&*()";
    cr_assert_eq(strlen(str), 10);
}

Test(strlen, test_strlen_long_string, .init = redirect_all_std)
{
    char *str = "This is a very long string used for testing the strlen function.";
    cr_assert_eq(strlen(str), 64);
}
