/*
** EPITECH PROJECT, 2025
** B-PDG-300-NAN-3-1-PDGD06-eliott.tesnier
** File description:
** tests_strncmp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <string.h>

extern int strncmp(const char *s1, const char *s2, size_t n);

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(strncmp, basic_compare_equal, .init = redirect_all_std)
{
    char *s1 = "Hello";
    char *s2 = "Hello";
    cr_assert_eq(strncmp(s1, s2, 5), 0);
}

Test(strncmp, compare_with_different_lengths, .init = redirect_all_std)
{
    char *s1 = "abc";
    char *s2 = "abcd";
    cr_assert_eq(strncmp(s1, s2, 4), -100);
}

Test(strncmp, compare_empty_strings, .init = redirect_all_std)
{
    char *s1 = "";
    char *s2 = "";
    cr_assert_eq(strncmp(s1, s2, 0), 0);
}

Test(strncmp, compare_with_empty, .init = redirect_all_std)
{
    char *s1 = "abc";
    char *s2 = "";
    cr_assert_eq(strncmp(s1, s2, 4), 97);
}

Test(strncmp, partial_compare_equal, .init = redirect_all_std)
{
    char *s1 = "abc";
    char *s2 = "abcd";
    cr_assert_eq(strncmp(s1, s2, 3), 0);
}

Test(strncmp, zero_length_compare, .init = redirect_all_std)
{
    char *s1 = "different";
    char *s2 = "strings";
    cr_assert_eq(strncmp(s1, s2, 0), 0);
}

Test(strncmp, compare_different_chars, .init = redirect_all_std)
{
    char *s1 = "apple";
    char *s2 = "banana";
    cr_assert_lt(strncmp(s1, s2, 1), 0);
}

Test(strncmp, compare_special_chars, .init = redirect_all_std)
{
    char *s1 = "test\200";
    char *s2 = "test\0";
    cr_assert_gt(strncmp(s1, s2, 5), 0);
}

Test(strncmp, compare_with_null_byte, .init = redirect_all_std)
{
    char *s1 = "test\0extra";
    char *s2 = "test\0other";
    cr_assert_eq(strncmp(s1, s2, 6), 0);
}

Test(strncmp, compare_large_n, .init = redirect_all_std)
{
    char *s1 = "small";
    char *s2 = "small";
    cr_assert_eq(strncmp(s1, s2, 1000), 0);
}
