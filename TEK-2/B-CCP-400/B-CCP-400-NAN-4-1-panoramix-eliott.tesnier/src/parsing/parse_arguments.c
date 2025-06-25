/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-panoramix-eliott.tesnier
** File description:
** parse_arguments
*/

#include <stdio.h>
#include <stdlib.h>
#include "panoramix.h"

const char *USAGE_MSG = "USAGE: %s "
    "<nb_villagers> <pot_size> <nb_fights> <nb_refills>\n"
    "Values must be >0.\n";

/**
 * @brief Exit the program with an error message
 * @param argv Argument values
 */
void exit_with_error(char **argv)
{
    fprintf(stderr, USAGE_MSG, argv[0]);
    exit(FAILURE);
}

/**
 * @brief Parse command line arguments and validate them
 * @param argc Argument count
 * @param argv Argument values
 * @return Parsed arguments as cli_args_t structure
 */
cli_args_t parse_arguments(int argc, char **argv)
{
    cli_args_t args = {0, 0, 0, 0};

    if (argc != EXPECTED_ARGS_COUNT)
        exit_with_error(argv);
    args.nb_villagers = atoi(argv[1]);
    args.pot_size = atoi(argv[2]);
    args.nb_fights = atoi(argv[3]);
    args.nb_refills = atoi(argv[4]);
    if (args.nb_villagers <= 0 || args.pot_size <= 0 ||
        args.nb_fights <= 0 || args.nb_refills <= 0)
        exit_with_error(argv);
    return args;
}
