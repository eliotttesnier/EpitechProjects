/*
** EPITECH PROJECT, 2025
** ASM
** File description:
** tests_strcasecmp
*/

#include <criterion/criterion.h>
#include <strings.h>
#include <stdio.h>
#include <dlfcn.h>

extern int strcasecmp(const char *s1, const char *s2);

Test(strcasecmp, identical_strings) {
    char str1[] = "hello";
    char str2[] = "hello";
    cr_assert_eq(strcasecmp(str1, str2), 0);
}

Test(strcasecmp, different_case) {
    char str1[] = "Hello";
    char str2[] = "hElLo";
    cr_assert_eq(strcasecmp(str1, str2), 0);
}

Test(strcasecmp, different_strings) {
    char str1[] = "Hello";
    char str2[] = "World";
    cr_assert_lt(strcasecmp(str1, str2), 0);
    cr_assert_gt(strcasecmp(str2, str1), 0);
}

Test(strcasecmp, different_length) {
    char str1[] = "hello";
    char str2[] = "hello!";
    cr_assert_lt(strcasecmp(str1, str2), 0);
}

Test(strcasecmp, empty_strings) {
    char str1[] = "";
    char str2[] = "";
    cr_assert_eq(strcasecmp(str1, str2), 0);
}

Test(strcasecmp, numbers_and_symbols) {
    char str1[] = "Hello123!";
    char str2[] = "hello123!";
    cr_assert_eq(strcasecmp(str1, str2), 0);
}

Test(strcasecmp, partial_match) {
    char str1[] = "HelloWorld";
    char str2[] = "helloEarth";
    cr_assert_gt(strcasecmp(str1, str2), 0);
}

Test(strcasecmp, special_characters) {
    char str1[] = "Hello\n";
    char str2[] = "hello\n";
    cr_assert_eq(strcasecmp(str1, str2), 0);
}

Test(strcasecmp, mixed_case_comparison) {
    char str1[] = "aBcDeF";
    char str2[] = "AbCdEf";
    cr_assert_eq(strcasecmp(str1, str2), 0);
}
