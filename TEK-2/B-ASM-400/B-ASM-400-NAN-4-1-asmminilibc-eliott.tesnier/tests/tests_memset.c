/*
** EPITECH PROJECT, 2025
** ASM
** File description:
** tests_memset
*/

/*
** EPITECH PROJECT, 2025
** B-ASM-400-NAN-4-1-asmminilibc-eliott.tesnier
** File description:
** test_memset
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <string.h>

extern void *memset(void *s, int c, size_t n);

Test(memset, basic_string_fill)
{
    char str[] = "Hello World!";
    memset(str, '*', 5);
    cr_assert_str_eq(str, "***** World!");
}

Test(memset, empty_string)
{
    char str[] = "";
    memset(str, '*', 0);
    cr_assert_str_eq(str, "");
}

Test(memset, fill_entire_string)
{
    char str[] = "Hello World!";
    memset(str, 'x', strlen(str));
    cr_assert_str_eq(str, "xxxxxxxxxxxx");
}

Test(memset, fill_with_zero)
{
    char str[] = "Hello World!";
    memset(str, 0, 5);
    cr_assert_eq(str[0], '\0');
    cr_assert_str_eq(str + 5, " World!");
}

Test(memset, fill_with_numbers)
{
    char str[] = "Hello World!";
    memset(str, '0', 5);
    cr_assert_str_eq(str, "00000 World!");
}

Test(memset, non_char_buffer)
{
    int buffer[5] = {1, 2, 3, 4, 5};
    memset(buffer, 0, sizeof(int) * 5);
    for (int i = 0; i < 5; i++)
        cr_assert_eq(buffer[i], 0);
}
