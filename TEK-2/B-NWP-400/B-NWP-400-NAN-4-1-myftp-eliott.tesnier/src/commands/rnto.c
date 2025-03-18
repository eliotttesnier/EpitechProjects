/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** rnto
*/

#include "myftp.h"

bool validate_rnto_args(server_t *s, client_t *client, char *args)
{
    char *path = NULL;

    if (!args || strlen(args) == 0) {
        send_reply(client, RPL_SYNTAX_ERROR, "Missing path argument");
        return false;
    }
    if (!client->rnfr_path) {
        send_reply(client, RPL_BAD_SEQUENCE, "RNFR not sent");
        return false;
    }
    path = get_abs(s, client, args);
    if (is_file_path_existing(path) || is_folder_path_existing(path)) {
        send_reply(client, RPL_FILE_UNAVAILABLE, "Path already exists");
        free(path);
        return false;
    }
    return true;
}

int rnto_command(server_t *serv, client_t *client, char *args)
{
    char *abs_path = NULL;

    if (!validate_rnto_args(serv, client, args))
        return 0;
    abs_path = get_abs(serv, client, args);
    if (rename(client->rnfr_path, abs_path) == -1) {
        send_reply(client, RPL_ERROR, strerror(errno));
        free(abs_path);
        return 0;
    }
    send_reply(client, RPL_FILE_ACTION_OK, "File renamed successfully");
    free(abs_path);
    free(client->rnfr_path);
    client->rnfr_path = NULL;
    return 0;
}
