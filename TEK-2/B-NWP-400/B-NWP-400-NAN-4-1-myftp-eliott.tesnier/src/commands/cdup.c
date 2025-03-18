/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** cdup
*/

#include "myftp.h"

static void update_client_paths(server_t *serv, client_t *client,
    const char *new_complete_path)
{
    size_t root_len = strlen(serv->complete_root_dir);
    char *normalized_relative =
        normalize_relative_path(new_complete_path + root_len);

    strncpy(client->current_dir, normalized_relative, PATH_MAX_LEN);
    strncpy(client->complete_current_dir, new_complete_path, PATH_MAX_LEN);
    free(normalized_relative);
}

int cdup_command(server_t *serv, client_t *client, char *args)
{
    char *new_complete_path;

    (void)args;
    if (strcmp(client->current_dir, "/") == 0) {
        send_reply(client, RPL_FILE_UNAVAILABLE, "Already at root directory");
        return 0;
    }
    new_complete_path = get_absolute_path(client->complete_current_dir, "..");
    if (!check_directory_access(client, new_complete_path)) {
        free(new_complete_path);
        return 0;
    }
    update_client_paths(serv, client, new_complete_path);
    send_reply(client, RPL_COMMAND_OK, "Directory changed");
    free(new_complete_path);
    return 0;
}
