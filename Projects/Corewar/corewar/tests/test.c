/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "corewar_header.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

// Error cases

Test(corewar, too_few_warriors, .init = redirect_all_std)
{
    char **av = str_to_array("./corewar", " \t");
    int ret = corewar(my_arrlen(av), av);

    cr_assert_eq(ret, 84);
    cr_assert_stderr_eq_str("INIT: Too few warrior\n");
}

Test(check_path, too_few_warriors2, .init = redirect_all_std)
{
    bool ret = check_path("foo.foo");

    cr_assert_eq(ret, false);
}

Test(corewar, invalid_champion_file, .init = redirect_all_std)
{
    char **av = str_to_array("./corewar tests/abel.cor tests/abel.s", " \t");
    int ret = corewar(my_arrlen(av), av);

    cr_assert_eq(ret, 84);
    cr_assert_stderr_eq_str("INIT: header error\n");
}

Test(corewar, non_existing_file, .init = redirect_all_std)
{
    char **av = str_to_array("./corewar champions tests/foo", " \t");
    int ret = corewar(my_arrlen(av), av);

    cr_assert_eq(ret, 84);
}

Test(corewar, small_name_file, .init = redirect_all_std)
{
    char **av = str_to_array("./corewar op.c tests/abel.cor", " \t");
    int ret = corewar(my_arrlen(av), av);

    cr_assert_eq(ret, 84);
    cr_assert_stderr_eq_str("INIT: header error\n");
}

Test(corewar, missplaced_dump, .init = redirect_all_std)
{
    char **av = str_to_array("./corewar tests/abel.cor tests/abel.cor -dump 50", " \t");
    int ret = corewar(my_arrlen(av), av);

    cr_assert_eq(ret, 84);
    cr_assert_stderr_eq_str("INIT: arg aren't relate to any warrior\n");
}

Test(corewar, missplaced_load, .init = redirect_all_std)
{
    char **av = str_to_array("./corewar tests/abel.cor tests/abel.cor -a 50", " \t");
    int ret = corewar(my_arrlen(av), av);

    cr_assert_eq(ret, 84);
    cr_assert_stderr_eq_str("INIT: arg aren't relate to any warrior\n");
}

Test(corewar, missplaced_nb, .init = redirect_all_std)
{
    char **av = str_to_array("./corewar tests/abel.cor tests/abel.cor -n 50", " \t");
    int ret = corewar(my_arrlen(av), av);

    cr_assert_eq(ret, 84);
    cr_assert_stderr_eq_str("INIT: arg aren't relate to any warrior\n");
}

Test(corewar, alone_dump, .init = redirect_all_std)
{
    char **av = str_to_array("./corewar tests/abel.cor tests/abel.cor -dump", " \t");
    int ret = corewar(my_arrlen(av), av);

    cr_assert_eq(ret, 84);
}

Test(corewar, alone_load, .init = redirect_all_std)
{
    char **av = str_to_array("./corewar tests/abel.cor tests/abel.cor -a", " \t");
    int ret = corewar(my_arrlen(av), av);

    cr_assert_eq(ret, 84);
    cr_assert_stderr_eq_str("INIT: header error\n");
}

Test(corewar, alone_nb, .init = redirect_all_std)
{
    char **av = str_to_array("./corewar tests/abel.cor tests/abel.cor -n", " \t");
    int ret = corewar(my_arrlen(av), av);

    cr_assert_eq(ret, 84);
    cr_assert_stderr_eq_str("INIT: header error\n");
}

Test(corewar, well_placed_alone_dump, .init = redirect_all_std)
{
    char **av = str_to_array("./corewar -dump tests/abel.cor tests/abel.cor", " \t");
    int ret = corewar(my_arrlen(av), av);

    cr_assert_eq(ret, 84);
}

Test(corewar, well_placed_alone_load, .init = redirect_all_std)
{
    char **av = str_to_array("./corewar -a tests/abel.cor tests/abel.cor", " \t");
    int ret = corewar(my_arrlen(av), av);

    cr_assert_eq(ret, 84);
}

Test(corewar, well_placed_alone_nb, .init = redirect_all_std)
{
    char **av = str_to_array("./corewar -n tests/abel.cor tests/abel.cor", " \t");
    int ret = corewar(my_arrlen(av), av);

    cr_assert_eq(ret, 84);
}

Test(corewar, alone_valor_one, .init = redirect_all_std)
{
    char **av = str_to_array("./corewar tests/abel.cor tests/abel.cor 50", " \t");
    int ret = corewar(my_arrlen(av), av);

    cr_assert_eq(ret, 84);
    cr_assert_stderr_eq_str("INIT: header error\n");
}

Test(corewar, alone_valor_two, .init = redirect_all_std)
{
    char **av = str_to_array("./corewar 50 tests/abel.cor 50 tests/abel.cor", " \t");
    int ret = corewar(my_arrlen(av), av);

    cr_assert_eq(ret, 84);
}

Test(corewar, wrong_dump_arg, .init = redirect_all_std)
{
    char **av = str_to_array("./corewar -dump foo tests/abel.cor tests/abel.cor", " \t");
    int ret = corewar(my_arrlen(av), av);

    cr_assert_eq(ret, 84);
}

Test(corewar, wrong_load_arg, .init = redirect_all_std)
{
    char **av = str_to_array("./corewar -a foo tests/abel.cor tests/abel.cor", " \t");
    int ret = corewar(my_arrlen(av), av);

    cr_assert_eq(ret, 84);
}

Test(corewar, wrong_nb_arg, .init = redirect_all_std)
{
    char **av = str_to_array("./corewar -n foo tests/abel.cor tests/abel.cor", " \t");
    int ret = corewar(my_arrlen(av), av);

    cr_assert_eq(ret, 84);
}

// Working cases

Test(corewar, dump, .init = redirect_all_std)
{
    char **av = str_to_array("./corewar -dump 50 tests/abel.cor tests/abel.cor", " \t");
    int ret = corewar(my_arrlen(av), av);

    cr_assert_eq(ret, 0);
}

Test(corewar, load, .init = redirect_all_std)
{
    char **av = str_to_array("./corewar -dump 50 -a 50 tests/abel.cor tests/abel.cor", " \t");
    int ret = corewar(my_arrlen(av), av);

    cr_assert_eq(ret, 0);
}

Test(corewar, nb, .init = redirect_all_std)
{
    char **av = str_to_array("./corewar -n 50 tests/abel.cor tests/abel.cor", " \t");
    int ret = corewar(my_arrlen(av), av);

    cr_assert_eq(ret, 0);
}

Test(corewar, same_nb, .init = redirect_all_std)
{
    char **av = str_to_array("./corewar -n 50 tests/abel.cor -n 50 tests/abel.cor", " \t");
    int ret = corewar(my_arrlen(av), av);

    cr_assert_eq(ret, 0);
}

Test(corewar, abel_pdd_bill_tyron)
{
    char **av = str_to_array("./corewar tests/abel.cor tests/pdd.cor tests/bill.cor tests/tyron.cor", " \t");
    int ret = corewar(my_arrlen(av), av);

    cr_assert_eq(ret, 0);
}

Test(corewar, all_instru)
{
    char **av = str_to_array("./corewar tests/all.cor tests/all.cor", " \t");
    int ret = corewar(my_arrlen(av), av);

    cr_assert_eq(ret, 0);
}

// LIB

Test(free_arr, simple_free)
{
    char **arr = str_to_array("foo bar\n", " \n");

    cr_assert_neq(arr, NULL);
    free_arr(arr);
}

Test(free_arr, null_free)
{
    free_arr(NULL);
}

Test(is_there_char, there_is)
{
    cr_assert_eq(is_there_char("salut", 's'), true);
}

Test(is_there_char, there_is_not)
{
    cr_assert_eq(is_there_char("salut", 'z'), false);
}

Test(mini_printf, coverage)
{
    fflush(NULL);
    cr_assert_eq(mini_printf("salut\n"), 0);
    cr_assert_eq(mini_printf("%%\n"), 0);
    cr_assert_eq(mini_printf("%i\n", 0), 0);
    cr_assert_eq(mini_printf("%d\n", 0), 0);
    cr_assert_eq(mini_printf("%s\n", "salut"), 0);
    cr_assert_eq(mini_printf("%c\n", 'c'), 0);
    fflush(NULL);
}

Test(my_arrdup, arrdup)
{
    char **av = str_to_array("Foo bar", " ");
    char **dup = my_arrdup(av);

    cr_assert_str_eq(dup[0], av[0]);
    cr_assert_str_eq(dup[1], av[1]);
    cr_assert_eq(dup[2], av[2]);
}

Test(my_arrlen, arrlen)
{
    char **av = str_to_array("Foo bar", " ");

    cr_assert_eq(my_arrlen(av), 2);
    cr_assert_eq(my_arrlen(NULL), -1);
}

Test(my_getnbr, getnbr)
{
    cr_assert_eq(my_getnbr("Foo 42 bar", 0), 42);
    cr_assert_eq(my_getnbr("Foo bar", 0), -9);
    cr_assert_eq(my_getnbr("Foo -42 bar", 0), -42);
}

Test(my_int_to_str, int_to_str)
{
    cr_assert_str_eq(my_int_to_str(-42), "-42");
    cr_assert_str_eq(my_int_to_str(42), "42");
    cr_assert_str_eq(my_int_to_str(0), "0");
}

Test(my_nbrlen, nbrlen)
{
    cr_assert_eq(my_nbrlen(123), 3);
    cr_assert_eq(my_nbrlen(0), 0);
}

Test(my_perror, myperror)
{
    cr_assert_eq(my_perror("foo bar", 84), 84);
}

Test(my_root, root)
{
    cr_assert_eq(my_root(9), 3.00);
    cr_assert_eq(my_root(-9), 0);
}

Test(my_strcat, mystrcat)
{
    cr_assert_str_eq(my_strcat("foo", "bar"), "foobar");
}

Test(my_strcmp, mystrcmp)
{
    cr_assert_eq(my_strcmp("foo", "bar"), 0);
    cr_assert_eq(my_strcmp("foo", "foo"), 1);
}

Test(my_strcut, mystrcut)
{
    cr_assert_str_eq(my_strcut("foobar", 0, 2), "foo");
    cr_assert_str_eq(my_strcut("foobar", 0, 18), "");
    cr_assert_str_eq(my_strcut("foobar", 18, 18), "");
    cr_assert_str_eq(my_strcut("foobar", 0, -1), "foobar");
}

Test(my_strdup, mystrdup)
{
    cr_assert_str_eq(my_strdup("foobar"), "foobar");
    cr_assert_eq(my_strdup(NULL), NULL);
}

Test(my_strlen, mystrlen)
{
    cr_assert_eq(my_strlen("foobar"), 6);
}

Test(my_strncmp, mystrncmp)
{
    cr_assert_eq(my_strncmp("foo", "bar", 2), -1);
    cr_assert_eq(my_strncmp("foo", "bar", 18), -1);
    cr_assert_eq(my_strncmp("foo", "foo", 2), 0);
}

Test(str_to_array, strtoarray)
{
    char **av = str_to_array(" yo   les  geeks\n", " \t\n");
    char **av2 = str_to_array("  \t", " \t");

    cr_assert_str_eq(av[0], "yo");
    cr_assert_str_eq(av[1], "les");
    cr_assert_str_eq(av[2], "geeks");
}
