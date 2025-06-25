/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-panoramix-eliott.tesnier
** File description:
** init_prog_state
*/

#include <stdio.h>
#include <stdlib.h>
#include "panoramix.h"

/**
 * @brief Initialize the villagers and their threads
 * @param state Pointer to the program state
 * @param args Command line arguments
 * @return SUCCESS on success, FAILURE on error
 */
static int init_villagers(program_state_t *state, cli_args_t args)
{
    state->villagers = malloc(sizeof(villager_t) * args.nb_villagers);
    state->villager_contexts =
        malloc(sizeof(villager_context_t) * args.nb_villagers);
    if (!state->villagers || !state->villager_contexts)
        return FAILURE;
    for (int i = 0; i < args.nb_villagers; i++) {
        state->villagers[i].id = i;
        state->villagers[i].nb_fights = args.nb_fights;
        state->villager_contexts[i].id = i;
        state->villager_contexts[i].state = state;
        if (pthread_create(&state->villagers[i].thread, NULL,
                villager_routine, &state->villager_contexts[i]) != 0) {
            return FAILURE;
        }
    }
    return SUCCESS;
}

/**
 * @brief Initialize the druid and its thread
 * @param state Pointer to the program state
 * @param args Command line arguments
 * @return SUCCESS on success, FAILURE on error
 */
static int init_druid(program_state_t *state, cli_args_t args)
{
    state->druid = malloc(sizeof(druid_t));
    if (!state->druid)
        return FAILURE;
    state->druid->nb_refills = args.nb_refills;
    if (pthread_create(&state->druid->thread, NULL,
            druid_routine, state) != 0) {
        return FAILURE;
    }
    return SUCCESS;
}

/**
 * @brief Initialize the potion pot semaphore for the villagers
 * @param state Pointer to the program state
 * @return SUCCESS on success, FAILURE on error
 */
static int init_pot_semaphores(program_state_t *state)
{
    state->pot_semaphore = malloc(sizeof(sem_t));
    if (!state->pot_semaphore)
        return FAILURE;
    if (sem_init(state->pot_semaphore, 0, 1) != 0)
        return FAILURE;
    return SUCCESS;
}

/**
 * @brief Initialize the druid semaphore for the villagers
 * @param state Pointer to the program state
 * @return SUCCESS on success, FAILURE on error
 */
static int init_druid_semaphores(program_state_t *state)
{
    state->druid_semaphore = malloc(sizeof(sem_t));
    if (!state->druid_semaphore)
        return FAILURE;
    if (sem_init(state->druid_semaphore, 0, 0) != 0)
        return FAILURE;
    return SUCCESS;
}

/**
 * @brief Initialize the refill semaphore for the villagers
 * @param state Pointer to the program state
 * @return SUCCESS on success, FAILURE on error
 */
static int init_refill_semaphores(program_state_t *state)
{
    state->refill_semaphore = malloc(sizeof(sem_t));
    if (!state->refill_semaphore)
        return FAILURE;
    if (sem_init(state->refill_semaphore, 0, 0) != 0)
        return FAILURE;
    return SUCCESS;
}

/**
 * @brief Initialize the mutex for the potion pot
 * @param state Pointer to the program state
 * @return SUCCESS on success, FAILURE on error
 */
static int init_pot_mutex(program_state_t *state)
{
    if (pthread_mutex_init(&state->pot_mutex, NULL) != 0)
        return FAILURE;
    return SUCCESS;
}

/**
 * @brief Initialize the mutex for active villagers counter
 * @param state Pointer to the program state
 * @return SUCCESS on success, FAILURE on error
 */
static int init_active_villagers_mutex(program_state_t *state)
{
    if (pthread_mutex_init(&state->active_villagers_mutex, NULL) != 0)
        return FAILURE;
    return SUCCESS;
}

/**
 * @brief Initialize the program state with the given arguments
 * @param state Pointer to the program state
 * @param args Command line arguments
 * @return SUCCESS on success, FAILURE on error
 */
int initialize_program_state(program_state_t *state, cli_args_t args)
{
    state->potion_pot = args.pot_size;
    state->max_pot_size = args.pot_size;
    state->nb_villagers = args.nb_villagers;
    state->active_villagers = args.nb_villagers;
    if (init_druid(state, args) == FAILURE)
        return FAILURE;
    if (init_villagers(state, args) == FAILURE)
        return FAILURE;
    if (init_pot_semaphores(state) == FAILURE)
        return FAILURE;
    if (init_druid_semaphores(state) == FAILURE)
        return FAILURE;
    if (init_refill_semaphores(state) == FAILURE)
        return FAILURE;
    if (init_pot_mutex(state) == FAILURE)
        return FAILURE;
    if (init_active_villagers_mutex(state) == FAILURE)
        return FAILURE;
    return SUCCESS;
}
