/*
** EPITECH PROJECT, 2025
** ASM
** File description:
** tests_index
*/

#include <criterion/criterion.h>
#include <string.h>
#include <stdio.h>
#include <dlfcn.h>

extern char *index(const char *s, int c);

Test(index, basic_search) {
    char str[] = "Hello, World!";
    cr_assert_eq(index(str, 'W'), strstr(str, "World"));
}

Test(index, search_first_char) {
    char str[] = "Hello, World!";
    cr_assert_eq(index(str, 'H'), str);
}

Test(index, search_last_char) {
    char str[] = "Hello, World!";
    cr_assert_eq(index(str, '!'), &str[strlen(str)-1]);
}

Test(index, search_null_terminator) {
    char str[] = "Hello";
    cr_assert_eq(index(str, '\0'), str + strlen(str));
}

Test(index, char_not_found) {
    char str[] = "Hello, World!";
    cr_assert_null(index(str, 'z'));
}

Test(index, empty_string) {
    char str[] = "";
    cr_assert_null(index(str, 'a'));
    cr_assert_eq(index(str, '\0'), str);
}

Test(index, multiple_occurrences) {
    char str[] = "Hello, Hello!";
    cr_assert_eq(index(str, 'l'), &str[2]);  // Should find first 'l'
}
