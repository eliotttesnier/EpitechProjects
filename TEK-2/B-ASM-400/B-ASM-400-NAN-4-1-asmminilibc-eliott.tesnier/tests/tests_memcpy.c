/*
** EPITECH PROJECT, 2025
** B-ASM-400-NAN-4-1-asmminilibc-eliott.tesnier
** File description:
** memcpy tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <string.h>

extern void *memcpy(void *dest, const void *src, size_t n);

Test(memcpy, basic_string_copy)
{
    char dest[20];
    const char *src = "Hello World!";
    memcpy(dest, src, strlen(src) + 1);
    cr_assert_str_eq(dest, "Hello World!");
}

Test(memcpy, zero_length_copy)
{
    char dest[20] = "unchanged";
    const char *src = "Hello";
    memcpy(dest, src, 0);
    cr_assert_str_eq(dest, "unchanged");
}

Test(memcpy, partial_copy)
{
    char dest[20] = "Testing";
    const char *src = "Hello";
    memcpy(dest, src, 3);
    cr_assert_eq(dest[0], 'H');
    cr_assert_eq(dest[1], 'e');
    cr_assert_eq(dest[2], 'l');
    cr_assert_eq(dest[3], 't');  // Original character
}

Test(memcpy, integer_array_copy)
{
    int src[5] = {1, 2, 3, 4, 5};
    int dest[5] = {0};
    memcpy(dest, src, sizeof(int) * 5);
    for (int i = 0; i < 5; i++)
        cr_assert_eq(dest[i], src[i]);
}

Test(memcpy, overlapping_regions)
{
    char str[20] = "Hello World!";
    memcpy(str + 6, str, 5);  // Should copy "Hello" after "World"
    cr_assert_str_eq(str, "Hello Hello!");
}

Test(memcpy, struct_copy)
{
    struct Test {
        int x;
        char c;
        float f;
    };
    struct Test src = {42, 'A', 3.14f};
    struct Test dest;
    memcpy(&dest, &src, sizeof(struct Test));
    cr_assert_eq(dest.x, 42);
    cr_assert_eq(dest.c, 'A');
    cr_assert_float_eq(dest.f, 3.14f, 0.0001);
}

Test(memcpy, empty_but_valid_buffers)
{
    char dest[1] = {42};
    char src[1] = {0};
    void *result = memcpy(dest, src, 1);
    cr_assert_eq(result, dest);
    cr_assert_eq(dest[0], 0);
}

Test(memcpy, byte_by_byte_copy)
{
    unsigned char src[4] = {0xFF, 0x00, 0xAA, 0x55};
    unsigned char dest[4] = {0};
    void *result = memcpy(dest, src, 4);
    cr_assert_eq(result, dest);
    cr_assert_eq(dest[0], 0xFF);
    cr_assert_eq(dest[1], 0x00);
    cr_assert_eq(dest[2], 0xAA);
    cr_assert_eq(dest[3], 0x55);
}

Test(memcpy, large_copy)
{
    char src[1024];
    char dest[1024];
    memset(src, 'A', 1023);
    src[1023] = '\0';

    void *result = memcpy(dest, src, 1024);
    cr_assert_eq(result, dest);
    cr_assert_str_eq(dest, src);
}

Test(memcpy, one_byte_copy)
{
    unsigned char dest[2] = {0x42, 0x43};  // Initialize with known values
    unsigned char src[2] = {0x41, 0x44};   // Initialize with different values
    void *result = memcpy(dest, src, 1);
    cr_assert_eq(result, dest);
    cr_assert_eq(dest[0], 0x41);  // First byte should be copied
    cr_assert_eq(dest[1], 0x43);  // Second byte should remain unchanged
}

Test(memcpy, aligned_copy)
{
    long src[2] = {0x1234567890ABCDEF, 0xFEDCBA0987654321};
    long dest[2] = {0, 0};
    void *result = memcpy(dest, src, sizeof(long) * 2);
    cr_assert_eq(result, dest);
    cr_assert_eq(dest[0], src[0]);
    cr_assert_eq(dest[1], src[1]);
}

Test(memcpy, unaligned_copy)
{
    char src[10] = "ABCDEFGHI";
    char dest[10] = "123456789";
    void *result = memcpy(dest + 1, src + 2, 5);
    cr_assert_eq(result, dest + 1);
    cr_assert_eq(dest[0], '1');
    cr_assert_eq(dest[1], 'C');
    cr_assert_eq(dest[2], 'D');
    cr_assert_eq(dest[3], 'E');
    cr_assert_eq(dest[4], 'F');
    cr_assert_eq(dest[5], 'G');
}
