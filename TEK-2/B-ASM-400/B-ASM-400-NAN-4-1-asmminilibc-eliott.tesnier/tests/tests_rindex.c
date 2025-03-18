/*
** EPITECH PROJECT, 2025
** ASM
** File description:
** tests_rindex
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <string.h>

extern char *rindex(const char *str, int c);

Test(rindex, basic_test)
{
    char *str = "Hello World";
    cr_assert_str_eq(rindex(str, 'o'), "orld");
}

Test(rindex, multiple_occurrences)
{
    char *str = "hello hello";
    cr_assert_str_eq(rindex(str, 'l'), "lo");
}

Test(rindex, character_not_found)
{
    char *str = "Hello World";
    cr_assert_null(rindex(str, 'z'));
}

Test(rindex, empty_string)
{
    char *str = "";
    cr_assert_null(rindex(str, 'a'));
}

Test(rindex, null_byte)
{
    char *str = "Hello";
    cr_assert_str_eq(rindex(str, '\0'), "");
}

Test(rindex, special_characters)
{
    char *str = "Hello\nWorld";
    cr_assert_str_eq(rindex(str, '\n'), "\nWorld");
}
