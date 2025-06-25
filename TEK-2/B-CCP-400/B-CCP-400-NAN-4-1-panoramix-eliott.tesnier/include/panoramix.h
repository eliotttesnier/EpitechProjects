/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-panoramix-eliott.tesnier
** File description:
** panoramix
*/

#ifndef PANORAMIX_H_
    #define PANORAMIX_H_

    #include <pthread.h>
    #include <semaphore.h>

// ------------------------ Constants ------------------------

    #define SUCCESS 0
    #define FAILURE 84

    #define EXPECTED_ARGS_COUNT 5

    #define VILLAGER_PREFIX "Villager %d: "
    #define VILLAGER_READY_MSG "Going into battle!\n"
    #define VILLAGER_DRINK_MSG "I need a drink... I see %d servings left.\n"
    #define VILLAGER_REFILL_MSG "Hey Pano wake up! We need more potion.\n"
    #define VILLAGER_FIGHT_MSG "Take that roman scum! Only %d left.\n"
    #define VILLAGER_DONE_MSG "I'm going to sleep now.\n"

    #define DRUID_READY_MSG "Druid: I'm ready... but sleepy...\n"

extern const char *DRUID_REFILL_MSG;
extern const char *DRUID_DONE_MSG;
extern const char *USAGE_MSG;

// -------------------------- Enums ----------------------------

typedef enum loop_status_e {
    NOTHING = 0,
    BREAK_LOOP,
    CONTINUE_LOOP,
} loop_status_t;

// ------------------------ Structures ------------------------

typedef struct villager_s {
    int id;
    int nb_fights;
    pthread_t thread;
} villager_t;

typedef struct druid_s {
    pthread_t thread;
    int nb_refills;
} druid_t;

struct villager_context_s;

typedef struct program_state_s {
    int nb_villagers;
    int potion_pot;
    int max_pot_size;
    int active_villagers;
    pthread_mutex_t active_villagers_mutex;
    sem_t *pot_semaphore;
    sem_t *druid_semaphore;
    sem_t *refill_semaphore;
    pthread_mutex_t pot_mutex;
    villager_t *villagers;
    struct villager_context_s *villager_contexts;
    druid_t *druid;
} program_state_t;

typedef struct villager_context_s {
    int id;
    program_state_t *state;
} villager_context_t;

typedef struct cli_args_s {
    int nb_villagers;
    int pot_size;
    int nb_fights;
    int nb_refills;
} cli_args_t;

// ------------------------ Function Prototypes ------------------------

void *villager_routine(void *arg);

void *druid_routine(void *arg);

cli_args_t parse_arguments(int argc, char **argv);
int initialize_program_state(program_state_t *state, cli_args_t args);
void cleanup(program_state_t *state);

int panoramix(int argc, char **argv);

#endif /* !PANORAMIX_H_ */
