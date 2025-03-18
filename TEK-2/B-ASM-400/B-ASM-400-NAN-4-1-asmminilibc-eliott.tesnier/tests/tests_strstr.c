/*
** EPITECH PROJECT, 2025
** ASM
** File description:
** tests_strstr
*/

#include <criterion/criterion.h>
#include <string.h>
#include <stdio.h>
#include <dlfcn.h>

extern char *strstr(const char *haystack, const char *needle);

Test(strstr, basic_substring) {
    char haystack[] = "Hello World";
    char needle[] = "World";
    cr_assert_str_eq(strstr(haystack, needle), "World");
}

Test(strstr, substring_at_start) {
    char haystack[] = "Hello World";
    char needle[] = "Hello";
    cr_assert_str_eq(strstr(haystack, needle), "Hello World");
}

Test(strstr, substring_not_found) {
    char haystack[] = "Hello World";
    char needle[] = "Python";
    cr_assert_null(strstr(haystack, needle));
}

Test(strstr, empty_needle) {
    char haystack[] = "Hello World";
    char needle[] = "";
    cr_assert_str_eq(strstr(haystack, needle), haystack);
}

Test(strstr, empty_haystack) {
    char haystack[] = "";
    char needle[] = "Test";
    cr_assert_null(strstr(haystack, needle));
}

Test(strstr, multiple_occurrences) {
    char haystack[] = "test test test";
    char needle[] = "test";
    cr_assert_str_eq(strstr(haystack, needle), "test test test");
}

Test(strstr, partial_match) {
    char haystack[] = "Testing";
    char needle[] = "Test123";
    cr_assert_null(strstr(haystack, needle));
}

Test(strstr, case_sensitive) {
    char haystack[] = "Hello World";
    char needle[] = "world";
    cr_assert_null(strstr(haystack, needle));
}

Test(strstr, special_characters) {
    char haystack[] = "Hello\nWorld";
    char needle[] = "\nWorld";
    cr_assert_str_eq(strstr(haystack, needle), "\nWorld");
}
