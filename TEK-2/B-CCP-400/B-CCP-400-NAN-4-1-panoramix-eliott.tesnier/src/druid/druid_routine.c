/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-panoramix-eliott.tesnier
** File description:
** routine
*/

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "panoramix.h"

const char *DRUID_REFILL_MSG = "Druid: Ah! Yes, yes, I'm awake! "
    "Working on it! Beware I can only make %d more refills after this one.\n";

const char *DRUID_DONE_MSG = "Druid: I'm out of viscum. "
    "I'm going back to... zZz\n";

/**
 * Check if the pot is empty and needs refill
 *
 * @param state The program state
 * @return true if pot is empty, false otherwise
 */
static bool is_pot_empty(program_state_t *state)
{
    bool empty = false;

    pthread_mutex_lock(&state->pot_mutex);
    empty = state->potion_pot <= 0;
    pthread_mutex_unlock(&state->pot_mutex);
    return empty;
}

/**
 * Check if there are any active villagers
 *
 * @param state The program state
 * @return true if there are active villagers, false otherwise
 */
static bool has_active_villagers(program_state_t *state)
{
    bool active = false;

    pthread_mutex_lock(&state->active_villagers_mutex);
    active = state->active_villagers > 0;
    pthread_mutex_unlock(&state->active_villagers_mutex);
    return active;
}

/**
 * Refill the potion pot
 *
 * @param state The program state
 * @param refills_left Number of refills left after this one
 */
static void refill_pot(program_state_t *state, int refills_left)
{
    if (!is_pot_empty(state)) {
        sem_post(state->refill_semaphore);
        return;
    }
    printf(DRUID_REFILL_MSG, refills_left - 1);
    pthread_mutex_lock(&state->pot_mutex);
    state->potion_pot = state->max_pot_size;
    pthread_mutex_unlock(&state->pot_mutex);
    for (int i = 0; i < state->nb_villagers; i++) {
        sem_post(state->refill_semaphore);
    }
}

/**
 * Perform a refill operation if needed
 *
 * @param state The program state
 * @param refills_left Pointer to the number of refills left
 * @return true if should continue, false if should break the loop
 */
static bool process_refill_request(program_state_t *state, int *refills_left)
{
    if (!has_active_villagers(state))
        return false;
    pthread_mutex_lock(&state->pot_mutex);
    if (state->potion_pot <= 0) {
        printf(DRUID_REFILL_MSG, *refills_left - 1);
        state->potion_pot = state->max_pot_size;
        (*refills_left)--;
    }
    pthread_mutex_unlock(&state->pot_mutex);
    sem_post(state->refill_semaphore);
    return true;
}

/**
 * Druid routine function
 *
 * @param arg Pointer to the program state
 * @return NULL
 */
void *druid_routine(void *arg)
{
    program_state_t *state = (program_state_t *)arg;
    int refills_left = state->druid->nb_refills;
    bool should_continue = true;

    printf(DRUID_READY_MSG);
    usleep(10000);
    while (refills_left > 0) {
        sem_wait(state->druid_semaphore);
        should_continue = process_refill_request(state, &refills_left);
        if (!should_continue)
            break;
        refill_pot(state, refills_left);
    }
    for (int i = 0; i < state->nb_villagers; i++) {
        sem_post(state->refill_semaphore);
    }
    printf("%s", DRUID_DONE_MSG);
    return NULL;
}
