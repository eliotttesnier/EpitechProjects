#include <criterion/criterion.h>
#include <string.h>
#include <stdio.h>

extern void *memfrob(void *s, size_t n);

Test(memfrob, basic_test)
{
    char str[] = "Hello World";
    char expected[] = "Hello World";
    size_t len = strlen(str);

    // Apply memfrob twice to verify it's reversible
    memfrob(str, len);
    cr_assert_neq(strcmp(str, expected), 0, "String should be encrypted");
    memfrob(str, len);
    cr_assert_eq(strcmp(str, expected), 0, "String should be back to original");
}

Test(memfrob, empty_string)
{
    char str[] = "";
    memfrob(str, 0);
    cr_assert_str_eq(str, "", "Empty string should remain empty");
}

Test(memfrob, null_pointer)
{
    memfrob(NULL, 0);
    cr_assert(1, "Function did not crash with NULL pointer");
}

Test(memfrob, partial_string)
{
    char str[] = "Hello World";
    char expected[] = "Hello World";
    size_t partial_len = 5;

    memfrob(str, partial_len);
    cr_assert_neq(strncmp(str, expected, partial_len), 0,
        "First part should be encrypted");
    cr_assert_eq(strcmp(str + partial_len, expected + partial_len), 0,
        "Second part should remain unchanged");
}

Test(memfrob, special_chars)
{
    unsigned char str[] = {0, 1, 2, 3, 4, 5};
    unsigned char expected[6];
    memcpy(expected, str, 6);

    memfrob(str, 6);
    for (int i = 0; i < 6; i++) {
        cr_assert_eq(str[i], expected[i] ^ 42,
            "Each byte should be XORed with 42");
    }
}

Test(memfrob, with_values)
{
    char str[] = "Hello, World!";
    char expected[] = {98, 79, 70, 70, 69, 6, 10, 125, 69, 88, 70, 78, 11, 0};

    memfrob(str, strlen(str));
    cr_assert_eq(strcmp(str, expected), 0, "String should be encrypted");
}
