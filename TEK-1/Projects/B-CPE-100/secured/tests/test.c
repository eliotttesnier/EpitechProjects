/*
** EPITECH PROJECT, 2023
** unit_tests
** File description:
** tests for secured
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/secured.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

int temporary(char *text, int numb)
{
    return (-1);
}

// NEW_HASHTABLE TESTS :

Test(new_hashtable, creating_hash, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 6);

    cr_assert_eq(ht, ht);
}

Test(new_hashtable, creating_0_hash, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 0);

    cr_assert_eq(ht, ht);
}

Test(new_hashtable, creating_1_hash, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 1);

    cr_assert_eq(ht, ht);
}

Test(new_hashtable, creating_huge_hash, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 10000);

    cr_assert_eq(ht, ht);
}

// DELETE_HASHTABLE TESTS :

Test(delete_hashtable, deleting_hash, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 6);

    delete_hashtable(ht);
    cr_assert_eq(ht, ht);
    //cr_assert_stdout_eq_str("WIRE n°0 - \"usb\" added.\n");
}

Test(delete_hashtable, deleting_empty_hash, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 3);

    delete_hashtable(ht);
    cr_assert_eq(ht, ht);
    //cr_assert_stdout_eq_str("WIRE n°0 - \"usb\" added.\n");
}

Test(delete_hashtable, deleting_empty_table, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 3);
    ht->h_table = NULL;

    delete_hashtable(ht);
    cr_assert_eq(ht, ht);
    //cr_assert_stdout_eq_str("WIRE n°0 - \"usb\" added.\n");
}

Test(delete_hashtable, deleting_huge_hash, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 10000);

    delete_hashtable(ht);
    cr_assert_eq(ht, ht);
    //cr_assert_stdout_eq_str("WIRE n°0 - \"usb\" added.\n");
}

// HT_INSERT TESTS :

Test(ht_insert, insert_empty_table, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 0);
    int ret = ht_insert(ht, "Kratos", "J'adore ce jeu");

    cr_assert_eq(ret, 84);
}

Test(ht_insert, insert_0_table, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 6);
    ht->len = 0;
    int ret = ht_insert(ht, "Kratos", "J'adore ce jeu");

    cr_assert_eq(ret, 84);
}

Test(ht_insert, insert_0_key, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 6);
    int ret = ht_insert(ht, "", "J'adore ce jeu");

    cr_assert_eq(ret, 84);
}

Test(ht_insert, insert_hash_problem, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&temporary, 6);
    int ret = ht_insert(ht, "Kratos", "J'adore ce jeu");

    cr_assert_eq(ret, 84);
}

Test(ht_insert, insert_4_empty_hash, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 4);

    ht_insert(ht, "Kratos", "J'adore ce jeu");
    ht_dump(ht);
    cr_assert_stdout_eq_str("[0]:\n> 546016 - J'adore ce jeu\n[1]:\n[2]:\n[3]:\n");
    delete_hashtable(ht);
}

Test(ht_insert, insert_same_key_hash, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 4);

    ht_insert(ht, "Kratos", "J'adore ce jeu");
    ht_insert(ht, "Kratos", "Suuuuuuuu");
    ht_dump(ht);
    cr_assert_stdout_neq_str("[0]:\n[1]:\n[2]:\n> hash - Suuuuuuuu\n[3]:\n");
    delete_hashtable(ht);
}

Test(ht_insert, insert_same_index_hash, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 4);

    ht_insert(ht, "Kratos", "J'adore ce jeu");
    ht_insert(ht, "Same Index", "Suuuuuuuu");
    ht_dump(ht);
    cr_assert_stdout_neq_str("[0]:\n[1]:\n[2]:\n> hash - J'adore ce jeu\n> hash - Suuuuuuuu\n[3]:\n");
    delete_hashtable(ht);
}

// HT_DUMP TESTS :

Test(ht_dump, dump_4_empty_hash, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 4);

    ht_dump(ht);
    cr_assert_stdout_eq_str("[0]:\n[1]:\n[2]:\n[3]:\n");
    delete_hashtable(ht);
}

Test(ht_dump, dump_empty_hash, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 0);

    ht_dump(ht);
    cr_assert_stdout_neq_str("[0]:\n:");
}

// HT_DELETE TESTS :

Test(ht_delete, delete_0_hash, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 0);
    int ret = ht_delete(ht, "Kratos");

    cr_assert_eq(ret, 84);
}

Test(ht_delete, delete_malloc, .init = redirect_all_std)
{
    hashtable_t *ht = malloc(sizeof(hashtable_t));
    int ret = ht_delete(ht, "Kratos");

    cr_assert_eq(ret, 84);
}

Test(ht_delete, delete_empty_4_hash, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 4);
    int ret = ht_delete(ht, "Kratos");

    cr_assert_eq(ret, 84);
    delete_hashtable(ht);
}

Test(ht_delete, delete_empty_key_test, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 4);
    int ret = ht_delete(ht, "");

    cr_assert_eq(ret, 84);
    delete_hashtable(ht);
}


Test(ht_delete, delete_hash_error_key, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&temporary, 4);
    int ret = ht_delete(ht, "Salam");

    cr_assert_eq(ret, 84);
    delete_hashtable(ht);
}

Test(ht_delete, delete_non_existing_key_hash, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 4);

    ht_insert(ht, "Krilin", "Incroyable les HP");
    ht_delete(ht, "Kratos");
    ht_dump(ht);
    cr_assert_stdout_neq_str("[0]:\n[1]:\n[2]:\n> hash - Incroyable les HP\n[3]:\n");
    delete_hashtable(ht);
}

Test(ht_delete, delete_simple_key_hash, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 4);

    ht_insert(ht, "Krilin", "Incroyable les HP");
    ht_delete(ht, "Krilin");
    ht_dump(ht);
    cr_assert_stdout_eq_str("[0]:\n[1]:\n[2]:\n[3]:\n");
    delete_hashtable(ht);
}

Test(ht_delete, delete_mutliple_index_hash, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 4);

    ht_insert(ht, "Kratos", "J'adore ce jeu");
    ht_insert(ht, "banae", "Suuuuuuuu");
    ht_delete(ht, "Kratos");
    ht_dump(ht);
    cr_assert_stdout_neq_str("[0]:\n[1]:\n> 189753 - Suuuuuuuu\n[2]:\n[3]:\n");
    delete_hashtable(ht);
}

Test(ht_delete, delete_nothing, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 4);

    ht_insert(ht, "Kratos", "J'adore ce jeu");
    ht_delete(ht, "Vision");
    ht_dump(ht);
    cr_assert_stdout_neq_str("[0]:\n[1]:\n> 189753 - Suuuuuuuu\n[2]:\n[3]:\n");
    delete_hashtable(ht);
}

Test(ht_delete, delete_tkt_index_hash, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 4);

    ht_insert(ht, "Kratos", "J'adore ce jeu");
    ht_delete(ht, "Canare");
    ht_dump(ht);
    cr_assert_eq(0, 0);
    delete_hashtable(ht);
}


// HT_SEARCH TESTS :

Test(ht_search, search_0_hash, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 0);

    cr_assert_eq(ht_search(ht, "Kratos"), NULL);
}

Test(ht_search, search_empty_4_hash, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 4);

    cr_assert_eq(ht_search(ht, "Kratos"), NULL);
    delete_hashtable(ht);
}

Test(ht_search, search_non_existing_key_hash, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 4);

    ht_insert(ht, "Krilin", "Incroyable les HP");
    cr_assert_eq(ht_search(ht, "Kratos"), NULL);
    delete_hashtable(ht);
}

Test(ht_search, search_0_len, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 4);
    ht->len = 0;
    char *ret = ht_search(ht, "Krilin");

    cr_assert_eq(ret, NULL);
    delete_hashtable(ht);
}

Test(ht_search, search_empty_key, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 4);
    char *ret = ht_search(ht, "");

    cr_assert_eq(ret, NULL);
    delete_hashtable(ht);
}

Test(ht_search, search_hash_problem, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&temporary, 4);
    char *ret = ht_search(ht, "Coucou");

    cr_assert_eq(ret, NULL);
    delete_hashtable(ht);
}

Test(ht_search, search_few_in_same_ind, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 4);

    ht_insert(ht, "Kratos", "Incroyable les HP");
    ht_insert(ht, "Vision", "Incroyable les HP");
    mini_printf("%s", ht_search(ht, "Kratos"));
    cr_assert_stdout_eq_str("Incroyable les HP");
    delete_hashtable(ht);
}

Test(ht_search, search_simple_key_hash, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 4);

    ht_insert(ht, "Krilin", "Incroyable les HP");
    mini_printf("%s\n", ht_search(ht, "Krilin"));
    cr_assert_stdout_eq_str("Incroyable les HP\n");
    delete_hashtable(ht);
}

Test(ht_search, search_mutliple_index_hash, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 4);

    ht_insert(ht, "Kratos", "J'adore ce jeu");
    ht_insert(ht, "Canare", "Suuuuuuuu");
    mini_printf("%s\n", ht_search(ht, "Kratos"));
    cr_assert_stdout_eq_str("J'adore ce jeu\n");
    delete_hashtable(ht);
}

// HASH TESTS :

Test(hash, hash_normal, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 4);
    int ret = hash("Kratos", 4);

    cr_assert_eq(ret, 546016);
    delete_hashtable(ht);
}

Test(hash, hash_similar, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 4);
    int ret = hash("Kratos", 4);
    int ret2 = hash("Krato", 4);

    cr_assert_neq(ret, ret2 + 1);
    delete_hashtable(ht);
}

Test(hash, hash_empty, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 4);
    int ret = hash("", 4);

    cr_assert_neq(ret, 42);
    delete_hashtable(ht);
}

Test(hash, hash_huge, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 4);
    int ret = hash("Kratos Le Goat ouloulouououuu", 4);

    cr_assert_neq(ret, 42);
    delete_hashtable(ht);
}

// COVERAGE

Test(coverage, coverage, .init = redirect_all_std)
{
    mini_printf("%d", -15);
    mini_printf("%%");
    mini_printf("%c", 'c');
    mini_printf("%i", -15);
    mini_printf("%b", -15);
    mini_printf("okay");
    my_nbrlen(18);
    my_root(-15);
}
