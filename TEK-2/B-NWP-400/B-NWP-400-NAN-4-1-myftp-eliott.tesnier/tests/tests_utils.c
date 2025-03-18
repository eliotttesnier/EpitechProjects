/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** tests_utils
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "myftp.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

// Normalize relative path
Test(normalize_relative_path, test1, .init = redirect_all_std)
{
    char *path = "./test/../test2";
    char *result = normalize_relative_path(path);

    cr_assert_str_eq(result, "/test2");
}

Test(normalize_relative_path, test2, .init = redirect_all_std)
{
    char *path = "./test/./test2";
    char *result = normalize_relative_path(path);

    cr_assert_str_eq(result, "/test/test2");
}

Test(normalize_relative_path, test3, .init = redirect_all_std)
{
    char *path = "./test/test2";
    char *result = normalize_relative_path(path);

    cr_assert_str_eq(result, "/test/test2");
}

Test(normalize_relative_path, test4, .init = redirect_all_std)
{
    char *path = "./test/test2/../../test3";
    char *result = normalize_relative_path(path);

    cr_assert_str_eq(result, "/test3");
}

Test(normalize_relative_path, test5, .init = redirect_all_std)
{
    char *path = NULL;
    char *result = normalize_relative_path(path);

    cr_assert_null(result);
}

// Is valid path
Test(is_valid_path, test1, .init = redirect_all_std)
{
    char *root_path = "/home";
    char *current_path = "/home";
    char *new_path = "/home/test";

    bool result = is_valid_path(root_path, current_path, new_path);

    cr_assert_eq(result, true);
}

Test(is_valid_path, test2, .init = redirect_all_std)
{
    char *root_path = "/home";
    char *current_path = "/home";
    char *new_path = "/home/test/../test2";

    bool result = is_valid_path(root_path, current_path, new_path);

    cr_assert_eq(result, true);
}

Test(is_valid_path, test3, .init = redirect_all_std)
{
    char *root_path = "/home";
    char *current_path = "/home";
    char *new_path = "/home/test/../test2/../../test3";

    bool result = is_valid_path(root_path, current_path, new_path);

    cr_assert_eq(result, true);
}

Test(is_valid_path, test4, .init = redirect_all_std)
{
    char *root_path = "/home";
    char *current_path = "/home";
    char *new_path = "\\home\\test";

    bool result = is_valid_path(root_path, current_path, new_path);

    cr_assert_eq(result, true);
}

Test(is_valid_path, test5, .init = redirect_all_std)
{
    char *root_path = "/home/";
    char *current_path = "/home/";
    char *new_path = "/home/test/";

    bool result = is_valid_path(root_path, current_path, new_path);

    cr_assert_eq(result, true);
}

Test(is_valid_path, test6, .init = redirect_all_std)
{
    char *root_path = "/home";
    char *current_path = "/home";
    char *new_path = "/home";

    bool result = is_valid_path(root_path, current_path, new_path);

    cr_assert_eq(result, true);
}

// Get absolute path
Test(get_absolute_path, test1, .init = redirect_all_std)
{
    char *base_path = "/home";
    char *relative_path = "/test";

    char *result = get_absolute_path(base_path, relative_path);

    cr_assert_str_eq(result, "/home/test");
}

Test(get_absolute_path, test2, .init = redirect_all_std)
{
    char *base_path = "/home";
    char *relative_path = "test";

    char *result = get_absolute_path(base_path, relative_path);

    cr_assert_str_eq(result, "/home/test");
}

Test(get_absolute_path, test3, .init = redirect_all_std)
{
    char *base_path = "/home";
    char *relative_path = "/home";

    char *result = get_absolute_path(base_path, relative_path);

    cr_assert_str_eq(result, "/home");
}

// Error handling
Test(error, test1, .init = redirect_all_std)
{
    int result = error("Error");

    cr_assert_eq(result, 84);
    cr_assert_stderr_eq_str("Error");
}
