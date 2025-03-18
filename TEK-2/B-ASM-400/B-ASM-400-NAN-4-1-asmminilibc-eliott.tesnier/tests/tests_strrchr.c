/*
** EPITECH PROJECT, 2025
** B-ASM-400-NAN-4-1-asmminilibc-eliott.tesnier
** File description:
** test_strrchr
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <string.h>

extern char *strrchr(const char *str, int c);

Test(strrchr, basic_test)
{
    char *str = "Hello World";
    cr_assert_str_eq(strrchr(str, 'o'), "orld");
}

Test(strrchr, multiple_occurrences)
{
    char *str = "hello hello";
    cr_assert_str_eq(strrchr(str, 'l'), "lo");
}

Test(strrchr, character_not_found)
{
    char *str = "Hello World";
    cr_assert_null(strrchr(str, 'z'));
}

Test(strrchr, empty_string)
{
    char *str = "";
    cr_assert_null(strrchr(str, 'a'));
}

Test(strrchr, null_byte)
{
    char *str = "Hello";
    cr_assert_str_eq(strrchr(str, '\0'), "");
}

Test(strrchr, special_characters)
{
    char *str = "Hello\nWorld";
    cr_assert_str_eq(strrchr(str, '\n'), "\nWorld");
}
