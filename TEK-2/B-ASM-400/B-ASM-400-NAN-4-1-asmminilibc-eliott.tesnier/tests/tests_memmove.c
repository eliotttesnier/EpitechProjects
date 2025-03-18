/*
** EPITECH PROJECT, 2025
** B-PDG-300-NAN-3-1-PDGD06-eliott.tesnier
** File description:
** tests_memmove
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <string.h>

extern void *memmove(void *dest, const void *src, size_t n);

Test(memmove, basic_test)
{
    char dest[20] = "Hello World!";
    memmove(dest, "Bonjour", 7);
    cr_assert_str_eq(dest, "Bonjourorld!");
}

Test(memmove, overlapping_forward)
{
    char str[] = "0123456789";
    memmove(str + 4, str + 3, 3);
    cr_assert_str_eq(str, "0123345789");
}

Test(memmove, overlapping_backward)
{
    char str[] = "0123456789";
    memmove(str + 3, str + 4, 3);
    cr_assert_str_eq(str, "0124566789");
}

Test(memmove, zero_size)
{
    char dest[] = "Hello";
    char src[] = "World";
    memmove(dest, src, 0);
    cr_assert_str_eq(dest, "Hello");
}

Test(memmove, non_string_data)
{
    int src[] = {1, 2, 3, 4, 5};
    int dest[5];
    memmove(dest, src, sizeof(int) * 5);
    for (int i = 0; i < 5; i++)
        cr_assert_eq(dest[i], src[i]);
}

Test(memmove, full_buffer_copy)
{
    char src[100];
    char dest[100];
    memset(src, 'A', 99);
    src[99] = '\0';
    memmove(dest, src, 100);
    cr_assert_str_eq(dest, src);
}

Test(memmove, single_byte)
{
    char dest[] = "Hello";
    char src[] = "World";
    memmove(dest, src, 1);
    cr_assert_eq(dest[0], 'W');
    cr_assert_str_eq(dest + 1, "ello");
}
