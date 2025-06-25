/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-panoramix-eliott.tesnier
** File description:
** cleanup
*/

#include <stdio.h>
#include <stdlib.h>
#include "panoramix.h"

/**
 * @brief Free the allocated resources in the program state
 * @param state Pointer to the program state
 */
void cleanup(program_state_t *state)
{
    if (state->villagers)
        free(state->villagers);
    if (state->villager_contexts)
        free(state->villager_contexts);
    if (state->druid)
        free(state->druid);
    if (state->pot_semaphore) {
        sem_destroy(state->pot_semaphore);
        free(state->pot_semaphore);
    }
    if (state->druid_semaphore) {
        sem_destroy(state->druid_semaphore);
        free(state->druid_semaphore);
    }
    if (state->refill_semaphore) {
        sem_destroy(state->refill_semaphore);
        free(state->refill_semaphore);
    }
    pthread_mutex_destroy(&state->pot_mutex);
    pthread_mutex_destroy(&state->active_villagers_mutex);
}
