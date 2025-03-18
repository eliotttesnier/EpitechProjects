/*
** EPITECH PROJECT, 2025
** ASM
** File description:
** tests_strcmp
*/

#include <criterion/criterion.h>
#include <string.h>
#include <stdio.h>
#include <dlfcn.h>

extern int strcmp(const char *s1, const char *s2);

Test(strcmp, identical_strings) {
    char str1[] = "Hello";
    char str2[] = "Hello";
    cr_assert_eq(strcmp(str1, str2), 0);
}

Test(strcmp, different_strings) {
    char str1[] = "Hello";
    char str2[] = "World";
    cr_assert_lt(strcmp(str1, str2), 0);
    cr_assert_gt(strcmp(str2, str1), 0);
}

Test(strcmp, different_length) {
    char str1[] = "Hello";
    char str2[] = "Hello!";
    cr_assert_lt(strcmp(str1, str2), 0);
    cr_assert_gt(strcmp(str2, str1), 0);
}

Test(strcmp, empty_strings) {
    char str1[] = "";
    char str2[] = "";
    cr_assert_eq(strcmp(str1, str2), 0);
}

Test(strcmp, empty_vs_nonempty) {
    char str1[] = "";
    char str2[] = "Hello";
    cr_assert_lt(strcmp(str1, str2), 0);
    cr_assert_gt(strcmp(str2, str1), 0);
}

Test(strcmp, special_characters) {
    char str1[] = "Hello\n";
    char str2[] = "Hello\t";
    cr_assert_neq(strcmp(str1, str2), 0);
}

Test(strcmp, case_sensitivity) {
    char str1[] = "Hello";
    char str2[] = "hello";
    cr_assert_lt(strcmp(str1, str2), 0);
}

Test(strcmp, partial_match) {
    char str1[] = "Hello World";
    char str2[] = "Hello Earth";
    cr_assert_gt(strcmp(str1, str2), 0);
}

Test(strcmp, null_terminated) {
    char str1[] = {'H', 'e', 'l', 'l', 'o', '\0'};
    char str2[] = {'H', 'e', 'l', 'l', 'o', '\0'};
    cr_assert_eq(strcmp(str1, str2), 0);
}
