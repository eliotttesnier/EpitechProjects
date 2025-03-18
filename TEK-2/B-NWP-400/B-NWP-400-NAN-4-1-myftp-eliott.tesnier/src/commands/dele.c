/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** dele
*/

#include "myftp.h"

static bool validate_dele_args(client_t *client, char *args)
{
    if (!args || strlen(args) == 0) {
        send_reply(client, RPL_SYNTAX_ERROR, "Missing path argument");
        return false;
    }
    return true;
}

bool check_file_access_dele(server_t *s, client_t *client, const char *path)
{
    char *abs_path = NULL;

    if (!is_file_path_valid(s, client, path)) {
        send_reply(client, RPL_FILE_UNAVAILABLE, "Failed to delete file");
        return false;
    }
    abs_path = get_abs(s, client, path);
    if (!is_file_path_existing(abs_path)) {
        send_reply(client, RPL_FILE_UNAVAILABLE, "Failed to delete file");
        free(abs_path);
        return false;
    }
    return true;
}

int dele_command(server_t *serv, client_t *client, char *args)
{
    char *abs_path;

    if (!validate_dele_args(client, args))
        return 0;
    if (!check_file_access_dele(serv, client, args))
        return 0;
    abs_path = get_abs(serv, client, args);
    if (remove(abs_path) == -1) {
        send_reply(client, RPL_FILE_UNAVAILABLE, "Failed to delete file");
        free(abs_path);
        return 0;
    }
    send_reply(client, RPL_FILE_ACTION_OK, "File deleted");
    free(abs_path);
    return 0;
}
