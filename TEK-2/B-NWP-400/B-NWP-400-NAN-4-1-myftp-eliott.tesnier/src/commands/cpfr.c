/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** cpfr
*/

#include "myftp.h"

bool validate_cpfr_args(server_t *s, client_t *client, char *args)
{
    char *path = NULL;

    if (!args || strlen(args) == 0) {
        send_reply(client, RPL_SYNTAX_ERROR, "Missing path argument");
        return false;
    }
    if (!is_file_path_valid(s, client, args)) {
        send_reply(client, RPL_FILE_UNAVAILABLE, "Path is invalid");
        return false;
    }
    path = get_abs(s, client, args);
    if (!is_file_path_existing(path)) {
        send_reply(client, RPL_FILE_UNAVAILABLE, "Path does not exist");
        free(path);
        return false;
    }
    return true;
}

int cpfr_command(server_t *serv, client_t *client, char *args)
{
    char *abs_path = NULL;

    if (!validate_cpfr_args(serv, client, args))
        return 0;
    abs_path = get_abs(serv, client, args);
    if (client->rnfr_path)
        free(client->rnfr_path);
    client->cpfr_path = strdup(abs_path);
    send_reply(client, RPL_FILE_ACTION_OK, "Ready for CPTO");
    free(abs_path);
    return 0;
}
