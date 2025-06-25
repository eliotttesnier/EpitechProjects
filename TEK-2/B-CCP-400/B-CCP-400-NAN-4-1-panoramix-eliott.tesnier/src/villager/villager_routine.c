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

/**
 * Try to get a potion from the pot
 *
 * @param state The program state
 * @param villager The current villager
 * @return 1 if got a potion, 0 if needs refill
 */
static bool try_get_potion(program_state_t *state, villager_t *villager)
{
    pthread_mutex_lock(&state->pot_mutex);
    printf(VILLAGER_PREFIX VILLAGER_DRINK_MSG,
        villager->id, state->potion_pot);
    if (state->potion_pot > 0) {
        state->potion_pot--;
        pthread_mutex_unlock(&state->pot_mutex);
        return true;
    }
    pthread_mutex_unlock(&state->pot_mutex);
    return false;
}

/**
 * Request a pot refill from the druid
 *
 * @param state The program state
 * @param villager The current villager
 * @return true if refill was successful, false if druid is out of refills
 */
static bool request_refill(program_state_t *state, villager_t *villager)
{
    bool refilled = false;

    printf(VILLAGER_PREFIX VILLAGER_REFILL_MSG, villager->id);
    sem_post(state->druid_semaphore);
    sem_wait(state->refill_semaphore);
    pthread_mutex_lock(&state->pot_mutex);
    refilled = state->potion_pot > 0;
    pthread_mutex_unlock(&state->pot_mutex);
    return refilled;
}

/**
 * Fight against Romans
 *
 * @param villager The current villager
 * @param fights_left Number of fights left
 */
static void fight(villager_t *villager, int fights_left)
{
    printf(VILLAGER_PREFIX VILLAGER_FIGHT_MSG, villager->id, fights_left - 1);
}

/**
 * Villager loop function
 *
 * @param state The program state
 * @param vil The current villager
 * @return Loop status
 */
static loop_status_t villager_loop(program_state_t *state, villager_t *vil)
{
    bool refilled = false;

    sem_wait(state->pot_semaphore);
    if (!try_get_potion(state, vil)) {
        sem_post(state->pot_semaphore);
        refilled = request_refill(state, vil);
        if (!refilled)
            return BREAK_LOOP;
        pthread_mutex_lock(&state->pot_mutex);
        if (state->potion_pot > 0) {
            state->potion_pot--;
        }
        pthread_mutex_unlock(&state->pot_mutex);
        return NOTHING;
    } else {
        sem_post(state->pot_semaphore);
    }
    return NOTHING;
}

/**
 * Decrement the active villagers counter and signal the druid
 *
 * @param state The program state
 */
static void decrement_active_villagers(program_state_t *state)
{
    pthread_mutex_lock(&state->active_villagers_mutex);
    state->active_villagers--;
    pthread_mutex_unlock(&state->active_villagers_mutex);
    sem_post(state->druid_semaphore);
}

/**
 * Villager routine function
 *
 * @param arg Pointer to the villager context
 * @return NULL
 */
void *villager_routine(void *arg)
{
    program_state_t *state = ((villager_context_t *)arg)->state;
    villager_t *villager = &state->villagers[((villager_context_t *)arg)->id];
    loop_status_t status = NOTHING;
    int fights_left = villager->nb_fights;

    printf(VILLAGER_PREFIX VILLAGER_READY_MSG, villager->id);
    usleep(10000);
    while (fights_left > 0) {
        status = villager_loop(state, villager);
        if (status == BREAK_LOOP)
            break;
        if (status == CONTINUE_LOOP)
            continue;
        fight(villager, fights_left);
        fights_left--;
    }
    usleep(10000);
    printf(VILLAGER_PREFIX VILLAGER_DONE_MSG, villager->id);
    decrement_active_villagers(state);
    return NULL;
}
