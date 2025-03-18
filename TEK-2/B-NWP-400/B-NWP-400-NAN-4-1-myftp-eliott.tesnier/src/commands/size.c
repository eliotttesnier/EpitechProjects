/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** size
*/

#include "myftp.h"

bool validate_size_args(server_t *s, client_t *client, char *args)
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
    if (!is_folder_path_existing(path) && !is_file_path_existing(path)) {
        send_reply(client, RPL_FILE_UNAVAILABLE, "Path does not exist");
        free(path);
        return false;
    }
    free(path);
    return true;
}

int size_command(server_t *serv, client_t *client, char *args)
{
    char *abs_path = NULL;
    char *size_str = NULL;
    unsigned long size = 0;
    struct stat st;

    if (!validate_size_args(serv, client, args))
        return 0;
    abs_path = get_abs(serv, client, args);
    if (stat(abs_path, &st) == -1) {
        send_reply(client, RPL_ERROR, "Failed to get file size");
        free(abs_path);
        return 0;
    }
    size = st.st_size;
    size_str = malloc(20);
    snprintf(size_str, 20, "%lu", size);
    send_reply(client, RPL_FILE_STATUS_OK, size_str);
    free(abs_path);
    free(size_str);
    return 0;
}
