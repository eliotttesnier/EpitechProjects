/*
** EPITECH PROJECT, 2025
** B-PDG-300-NAN-3-1-PDGD06-eliott.tesnier
** File description:
** tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

extern size_t strcspn(const char *s, const char *reject);

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(strcspn, test_no_reject_chars, .init = redirect_all_std)
{
    char *str = "hello";
    char *reject = "xyz";
    cr_assert_eq(strcspn(str, reject), 5);
}

Test(strcspn, test_reject_char_at_start, .init = redirect_all_std)
{
    char *str = "hello";
    char *reject = "h";
    cr_assert_eq(strcspn(str, reject), 0);
}

Test(strcspn, test_reject_char_in_middle, .init = redirect_all_std)
{
    char *str = "hello";
    char *reject = "l";
    cr_assert_eq(strcspn(str, reject), 2);
}

Test(strcspn, test_reject_char_at_end, .init = redirect_all_std)
{
    char *str = "hello";
    char *reject = "o";
    cr_assert_eq(strcspn(str, reject), 4);
}

Test(strcspn, test_empty_reject)
{
    char *str = "hello";
    char *reject = "";
    cr_assert_eq(strcspn(str, reject), 5);
}

Test(strcspn, test_empty_str, .init = redirect_all_std)
{
    char *str = "";
    char *reject = "abc";
    cr_assert_eq(strcspn(str, reject), 0);
}

Test(strcspn, test_empty_str_and_reject, .init = redirect_all_std)
{
    char *str = "";
    char *reject = "";
    cr_assert_eq(strcspn(str, reject), 0);
}

Test(strcspn, test_all_reject_chars, .init = redirect_all_std)
{
    char *str = "hello";
    char *reject = "helo";
    cr_assert_eq(strcspn(str, reject), 0);
}

Test(strcspn, test_non_ascii_reject_char, .init = redirect_all_std)
{
    char *str = "héllo";
    char *reject = "é";
    cr_assert_eq(strcspn(str, reject), 1);
}

Test(strcspn, test_multiple_reject_chars, .init = redirect_all_std)
{
    char *str = "abcdef";
    char *reject = "dxz";
    cr_assert_eq(strcspn(str, reject), 3);
}
