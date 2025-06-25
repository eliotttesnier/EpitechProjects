/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-panoramix-eliott.tesnier
** File description:
** panoramix
*/

#include <stdio.h>
#include "panoramix.h"

/**
 * @brief Initialize the program state with the given arguments
 * @param state Pointer to the program state
 * @param args Command line arguments
 * @return SUCCESS on success, FAILURE on error
 */
void join_threads(program_state_t *state)
{
    for (int i = 0; i < state->nb_villagers; i++) {
        pthread_join(state->villagers[i].thread, NULL);
    }
    pthread_join(state->druid->thread, NULL);
}

/**
 * @brief Main function of the program
 * @param ac Argument count
 * @param av Argument vector
 * @return Exit status
 */
int panoramix(int ac, char **av)
{
    cli_args_t args = parse_arguments(ac, av);
    program_state_t state = {0};

    if (initialize_program_state(&state, args) == FAILURE) {
        fprintf(stderr, "Failed to initialize program state\n");
        cleanup(&state);
        return FAILURE;
    }
    join_threads(&state);
    cleanup(&state);
    return SUCCESS;
}
