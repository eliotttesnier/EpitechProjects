/*
** EPITECH PROJECT, 2025
** B-PDG-300-NAN-3-1-PDGD06-eliott.tesnier
** File description:
** tests_strpbrk
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <string.h>

extern char *strpbrk(const char *s, const char *accept);

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(strpbrk, basic_usage, .init = redirect_all_std)
{
    char *s = "Hello World!";
    char *accept = "o";
    cr_assert_eq(strpbrk(s, accept), strpbrk(s, accept));
}

Test(strpbrk, empty_strings, .init = redirect_all_std)
{
    cr_assert_null(strpbrk("", ""));
    cr_assert_null(strpbrk("hello", ""));
    cr_assert_null(strpbrk("", "hello"));
}

Test(strpbrk, multiple_matches, .init = redirect_all_std)
{
    char *s = "hello world";
    char *accept = "ol";
    cr_assert_eq(strpbrk(s, accept), strpbrk(s, accept));
}

Test(strpbrk, no_match, .init = redirect_all_std)
{
    char *s = "hello world";
    char *accept = "xyz";
    cr_assert_null(strpbrk(s, accept));
}

Test(strpbrk, special_chars, .init = redirect_all_std)
{
    char *s = "hello!@#$%^&*()";
    char *accept = "@#$";
    cr_assert_eq(strpbrk(s, accept), strpbrk(s, accept));
}

Test(strpbrk, first_char_match, .init = redirect_all_std)
{
    char *s = "hello world";
    char *accept = "h";
    cr_assert_eq(strpbrk(s, accept), strpbrk(s, accept));
}

Test(strpbrk, last_char_match, .init = redirect_all_std)
{
    char *s = "hello world";
    char *accept = "d";
    cr_assert_eq(strpbrk(s, accept), strpbrk(s, accept));
}

Test(strpbrk, duplicate_chars_in_accept, .init = redirect_all_std)
{
    char *s = "hello world";
    char *accept = "ll";
    cr_assert_eq(strpbrk(s, accept), strpbrk(s, accept));
}
