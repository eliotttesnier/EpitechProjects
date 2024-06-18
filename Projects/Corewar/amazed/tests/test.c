/*
** EPITECH PROJECT, 2023
** unit_tests
** File description:
** tests for sort
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "header.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(amazed, working_case, .init = redirect_all_std)
{
    int fd = open("tests/working", O_RDONLY);
    int ret = 0;

    dup2(fd, STDIN_FILENO);
    ret = amazed(1);
    close(fd);
    cr_assert_eq(ret, 0);
}

Test(amazed, empty, .init = redirect_all_std)
{
    int fd = open("tests/empty", O_RDONLY);
    int ret = 0;

    dup2(fd, STDIN_FILENO);
    ret = amazed(1);
    close(fd);
    cr_assert_eq(ret, 84);
}

Test(amazed, wrong_nb_robots, .init = redirect_all_std)
{
    int fd = open("tests/wnbrobot", O_RDONLY);
    int ret = 0;

    dup2(fd, STDIN_FILENO);
    ret = amazed(1);
    close(fd);
    cr_assert_eq(ret, 84);
}

Test(amazed, wrong_nb_robots2, .init = redirect_all_std)
{
    int fd = open("tests/nbro2", O_RDONLY);
    int ret = 0;

    dup2(fd, STDIN_FILENO);
    ret = amazed(1);
    close(fd);
    cr_assert_eq(ret, 84);
}

Test(amazed, wrong_nb_robots3, .init = redirect_all_std)
{
    int fd = open("tests/nbro3", O_RDONLY);
    int ret = 0;

    dup2(fd, STDIN_FILENO);
    ret = amazed(1);
    close(fd);
    cr_assert_eq(ret, 84);
}

Test(amazed, wrong_nb_robots4, .init = redirect_all_std)
{
    int fd = open("tests/nbro4", O_RDONLY);
    int ret = 0;

    dup2(fd, STDIN_FILENO);
    ret = amazed(1);
    close(fd);
    cr_assert_eq(ret, 84);
}

Test(amazed, no_rooms, .init = redirect_all_std)
{
    int fd = open("tests/noroom", O_RDONLY);
    int ret = 0;

    dup2(fd, STDIN_FILENO);
    ret = amazed(1);
    close(fd);
    cr_assert_eq(ret, 84);
}

Test(amazed, room1, .init = redirect_all_std)
{
    int fd = open("tests/room1", O_RDONLY);
    int ret = 0;

    dup2(fd, STDIN_FILENO);
    ret = amazed(1);
    close(fd);
    cr_assert_eq(ret, 84);
}

Test(amazed, room2, .init = redirect_all_std)
{
    int fd = open("tests/room2", O_RDONLY);
    int ret = 0;

    dup2(fd, STDIN_FILENO);
    ret = amazed(1);
    close(fd);
    cr_assert_eq(ret, 84);
}

Test(amazed, room3, .init = redirect_all_std)
{
    int fd = open("tests/room3", O_RDONLY);
    int ret = 0;

    dup2(fd, STDIN_FILENO);
    ret = amazed(1);
    close(fd);
    cr_assert_eq(ret, 84);
}

Test(amazed, room4, .init = redirect_all_std)
{
    int fd = open("tests/room4", O_RDONLY);
    int ret = 0;

    dup2(fd, STDIN_FILENO);
    ret = amazed(1);
    close(fd);
    cr_assert_eq(ret, 84);
}

Test(amazed, room5, .init = redirect_all_std)
{
    int fd = open("tests/room5", O_RDONLY);
    int ret = 0;

    dup2(fd, STDIN_FILENO);
    ret = amazed(1);
    close(fd);
    cr_assert_eq(ret, 84);
}

Test(amazed, room6, .init = redirect_all_std)
{
    int fd = open("tests/room6", O_RDONLY);
    int ret = 0;

    dup2(fd, STDIN_FILENO);
    ret = amazed(1);
    close(fd);
    cr_assert_eq(ret, 84);
}

Test(amazed, room7, .init = redirect_all_std)
{
    int fd = open("tests/room7", O_RDONLY);
    int ret = 0;

    dup2(fd, STDIN_FILENO);
    ret = amazed(1);
    close(fd);
    cr_assert_eq(ret, 84);
}

Test(amazed, room8, .init = redirect_all_std)
{
    int fd = open("tests/room8", O_RDONLY);
    int ret = 0;

    dup2(fd, STDIN_FILENO);
    ret = amazed(1);
    close(fd);
    cr_assert_eq(ret, 84);
}

Test(amazed, no_tunnels, .init = redirect_all_std)
{
    int fd = open("tests/notunnel", O_RDONLY);
    int ret = 0;

    dup2(fd, STDIN_FILENO);
    ret = amazed(1);
    close(fd);
    cr_assert_eq(ret, 84);
}

Test(amazed, same_id, .init = redirect_all_std)
{
    int fd = open("tests/sameid", O_RDONLY);
    int ret = 0;

    dup2(fd, STDIN_FILENO);
    ret = amazed(1);
    close(fd);
    cr_assert_eq(ret, 84);
}

Test(amazed, same_coords, .init = redirect_all_std)
{
    int fd = open("tests/samecoords", O_RDONLY);
    int ret = 0;

    dup2(fd, STDIN_FILENO);
    ret = amazed(1);
    close(fd);
    cr_assert_eq(ret, 84);
}

Test(amazed, invalid_argument_number, .init = redirect_all_std)
{
    cr_assert_eq(amazed(2), 84);
    cr_assert_eq(words_number(NULL), 0);
}

Test(amazed, remove_coms, .init = redirect_all_std)
{
    char str1[19] = "foo    bar\t#test\n";
    int nb;

    remove_coms(str1);
    cr_assert_str_eq(str1, "foo    bar \n");
    nb = words_number(str1);
    cr_assert_eq(nb, 2);
    nb = words_number("18-19\n");
    cr_assert_eq(nb, 2);
}

Test(is_start, with_null_line)
{
    parsing_t *new = malloc(sizeof(parsing_t) * 1);

    new->line = strdup("   ");
    new->end = true;
    new->start = true;
    cr_assert_eq(is_start(new), false);
}

Test(is_end, with_null_line)
{
    parsing_t *new = malloc(sizeof(parsing_t) * 1);

    new->line = strdup("   ");
    new->end = true;
    new->start = true;
    cr_assert_eq(is_end(new), false);
}

Test(is_start, with_null)
{
    cr_assert_eq(is_start(NULL), false);
}

Test(is_end, with_null)
{
    cr_assert_eq(is_end(NULL), false);
}

Test(is_a_command, with_null)
{
    cr_assert_eq(is_a_command("  "), false);
}

Test(is_a_comment, with_null)
{
    cr_assert_eq(is_a_comment("  "), false);
}

// Lib - Coverage

Test(mini_printf, coverage, .init = redirect_all_std)
{
    mini_printf("%i %d %c %%", 0, 0, '0');
    mini_printf("%s\n", "salut");
}

Test(arrays, coverage)
{
    char **arr1 = str_to_array("Unit Test pour \"la vie\"", " ");
    char **arr2 = my_arrdup(arr1);
    char **arr3 = str_to_array(" Oui", " ");
    char **arr4 = str_to_array("", " ");
    char **arr5 = str_to_array("salut les gars\n", " \n");

    my_arrlen(arr1);
    my_arrlen(NULL);
    my_pushback_to_arr(arr1, "foo");
    my_pushback_to_arr(NULL, "foo");
    free_arr(arr2);
    free_arr(arr3);
    free_arr(NULL);
    arr5 = del_in_array(arr5, 1);
    del_in_array(arr5, 18);
    free_arr(arr5);
}

Test(numbers, coverage)
{
    my_getnbr(" 18 ", 0);
    my_getnbr(" -18 ", 0);
    my_getnbr(" no numbers", 0);
    my_int_to_str(255);
    my_int_to_str(-42);
    my_root(9.00);
    my_root(-9.00);
}

Test(strings, coverage)
{
    char *str = my_strcat("foo", "bar");
    char *str2 = my_strdup("criterion");
    char *nullll = my_strdup(NULL);
    char *str3 = my_strcut("unit", 2, 3);
    char *str4 = my_strcut("unit", 0, -1);
    char *str5 = my_strcut("unit", 9, 9);

    my_strcmp("foo", "bar");
    my_strcmp("f", "foobar");
    my_strcmp("foo", "foo");
    my_strncmp("foo", "bar", 3);
    my_strncmp("f", "foobar", 3);
    my_strncmp("foo", "foo", 3);
    free(str);
    free(str2);
    free(str3);
    free(str4);
}

// Template
    // Test(function, name, .init = redirect_all_std)
    // {
    //     cr_assert_eq(0, 0);
    //     cr_assert_stdout_eq_str("");
    // }