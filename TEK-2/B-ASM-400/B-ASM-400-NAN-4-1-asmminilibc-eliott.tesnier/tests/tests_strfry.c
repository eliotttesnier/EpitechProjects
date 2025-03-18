#include <criterion/criterion.h>
#include <string.h>
#include <stdbool.h>

char *strfry(char *string);

// Helper function to check if two strings contain the same characters
static bool same_characters(const char *s1, const char *s2) {
    int count[256] = {0};

    for (int i = 0; s1[i]; i++)
        count[(unsigned char)s1[i]]++;
    for (int i = 0; s2[i]; i++)
        count[(unsigned char)s2[i]]--;
    for (int i = 0; i < 256; i++)
        if (count[i] != 0)
            return false;
    return true;
}

Test(strfry, empty_string) {
    char str[] = "";
    char *result = strfry(str);
    cr_assert_str_eq(result, "");
}

Test(strfry, single_char) {
    char str[] = "a";
    char *result = strfry(str);
    cr_assert_str_eq(result, "a");
}

Test(strfry, normal_string) {
    char str[] = "hello";
    char original[] = "hello";
    char *result = strfry(str);

    cr_assert_eq(strlen(result), strlen(original));
    cr_assert(same_characters(result, original));
    cr_assert_neq(strcmp(result, original), 0);
}

Test(strfry, longer_string) {
    char str[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char original[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *result = strfry(str);

    cr_assert_eq(strlen(result), strlen(original));
    cr_assert(same_characters(result, original));
    cr_assert_neq(strcmp(result, original), 0);
}

Test(strfry, repeated_chars) {
    char str[] = "aaaaabbbcc";
    char original[] = "aaaaabbbcc";
    char *result = strfry(str);

    cr_assert_eq(strlen(result), strlen(original));
    cr_assert(same_characters(result, original));
    cr_assert_neq(strcmp(result, original), 0);
}
