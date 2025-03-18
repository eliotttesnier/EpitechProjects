/*
** EPITECH PROJECT, 2025
** ASM
** File description:
** tests_strchr
*/

#include <criterion/criterion.h>
#include <string.h>
#include <stdio.h>
#include <dlfcn.h>

extern char *strchr(const char *str, int c);

Test(strchr, basic_search) {
    char str[] = "Hello, World!";
    cr_assert_eq(strchr(str, 'W'), strstr(str, "World"));
}

Test(strchr, search_first_char) {
    char str[] = "Hello, World!";
    cr_assert_eq(strchr(str, 'H'), str);
}

Test(strchr, search_last_char) {
    char str[] = "Hello, World!";
    cr_assert_eq(strchr(str, '!'), &str[strlen(str)-1]);
}

Test(strchr, search_null_terminator) {
    char str[] = "Hello";
    cr_assert_eq(strchr(str, '\0'), str + strlen(str));
}

Test(strchr, char_not_found) {
    char str[] = "Hello, World!";
    cr_assert_null(strchr(str, 'z'));
}

Test(strchr, empty_string) {
    char str[] = "";
    cr_assert_null(strchr(str, 'a'));
    cr_assert_eq(strchr(str, '\0'), str);
}

Test(strchr, multiple_occurrences) {
    char str[] = "Hello, Hello!";
    cr_assert_eq(strchr(str, 'l'), &str[2]);  // Should find first 'l'
}

Test(strchr, special_characters) {
    char str[] = "Hello\n\t\r\b!";
    cr_assert_eq(strchr(str, '\n'), &str[5]);
    cr_assert_eq(strchr(str, '\t'), &str[6]);
    cr_assert_eq(strchr(str, '\r'), &str[7]);
    cr_assert_eq(strchr(str, '\b'), &str[8]);
}

Test(strchr, repeated_characters) {
    char str[] = "aaa";
    cr_assert_eq(strchr(str, 'a'), str);  // Should return first occurrence
}

Test(strchr, single_character_string) {
    char str[] = "a";
    cr_assert_eq(strchr(str, 'a'), str);
    cr_assert_null(strchr(str, 'b'));
}

Test(strchr, only_searched_char) {
    char str[] = "zzz";
    cr_assert_eq(strchr(str, 'z'), str);
}

Test(strchr, space_characters) {
    char str[] = "Hello World";
    cr_assert_eq(strchr(str, ' '), &str[5]);
}

Test(strchr, null_in_middle) {
    char str[] = "Hello\0World";
    cr_assert_eq(strchr(str, '\0'), &str[5]);
    cr_assert_null(strchr(str, 'W'));  // Should not find 'W' after null
}

Test(strchr, binary_data) {
    char str[] = {0x01, 0x02, 0x03, 0x00};
    cr_assert_eq(strchr(str, 0x02), &str[1]);
    cr_assert_null(strchr(str, 0x04));
}
