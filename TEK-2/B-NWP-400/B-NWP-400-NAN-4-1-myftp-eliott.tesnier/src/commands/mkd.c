/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** mkd
*/

#include "myftp.h"

bool validate_mkd_args(server_t *s, client_t *client, char *args)
{
    if (!args || strlen(args) == 0) {
        send_reply(client, RPL_SYNTAX_ERROR, "Missing path argument");
        return false;
    }
    if (!is_file_path_valid(s, client, args)) {
        send_reply(client, RPL_FILE_UNAVAILABLE, "Path is invalid");
        return false;
    }
    return true;
}

int mkd_command(server_t *serv, client_t *client, char *args)
{
    char *abs_path = NULL;

    if (!validate_mkd_args(serv, client, args))
        return 0;
    abs_path = get_abs(serv, client, args);
    if (mkdir(abs_path, 0755) == -1) {
        send_reply(client, RPL_FILE_UNAVAILABLE, "Failed to create directory");
        free(abs_path);
        return 0;
    }
    send_reply(client, RPL_FILE_ACTION_OK, "Directory created");
    free(abs_path);
    return 0;
}
