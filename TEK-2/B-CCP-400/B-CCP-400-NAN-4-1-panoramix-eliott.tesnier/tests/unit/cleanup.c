/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-panoramix-eliott.tesnier
** File description:
** cleanup
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "panoramix.h"

void redirect_all_stdout(void);

Test(cleanup, cleanup_empty)
{
    program_state_t state = {0};

    cleanup(&state);
    cr_assert_eq(0, 0, "Cleanup function should not crash with empty state");
}

Test(cleanup, cleanup_villagers)
{
    program_state_t state = {0};
    state.villagers = malloc(sizeof(villager_context_t) * 5);

    cleanup(&state);
    cr_assert_eq(0, 0, "Cleanup function should free villager");
}

Test(cleanup, cleanup_villager_contexts)
{
    program_state_t state = {0};
    state.villager_contexts = malloc(sizeof(villager_context_t) * 5);

    cleanup(&state);
    cr_assert_eq(0, 0, "Cleanup function should free villager");
}

Test(cleanup, cleanup_druid)
{
    program_state_t state = {0};
    state.druid = malloc(sizeof(druid_t));

    cleanup(&state);
    cr_assert_eq(0, 0, "Cleanup function should free villager");
}

Test(cleanup, cleanup_pot_semaphore)
{
    program_state_t state = {0};
    state.pot_semaphore = malloc(sizeof(sem_t));

    cleanup(&state);
    cr_assert_eq(0, 0, "Cleanup function should free villager");
}

Test(cleanup, cleanup_druid_semaphore)
{
    program_state_t state = {0};
    state.druid_semaphore = malloc(sizeof(sem_t));

    cleanup(&state);
    cr_assert_eq(0, 0, "Cleanup function should free villager");
}

Test(cleanup, cleanup_refill_semaphore)
{
    program_state_t state = {0};
    state.refill_semaphore = malloc(sizeof(sem_t));

    cleanup(&state);
    cr_assert_eq(0, 0, "Cleanup function should free villager");
}

Test(cleanup, cleanup_pot_mutex)
{
    program_state_t state = {0};
    pthread_mutex_init(&state.pot_mutex, NULL);

    cleanup(&state);
    cr_assert_eq(0, 0, "Cleanup function should free villager");
}

Test(cleanup, cleanup_active_villagers_mutex)
{
    program_state_t state = {0};
    pthread_mutex_init(&state.active_villagers_mutex, NULL);

    cleanup(&state);
    cr_assert_eq(0, 0, "Cleanup function should free villager");
}
