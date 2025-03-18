/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** cwd
*/

#include "myftp.h"

static bool validate_cwd_args(client_t *client, char *args)
{
    if (!args || strlen(args) == 0) {
        send_reply(client, RPL_SYNTAX_ERROR, "Missing path argument");
        return false;
    }
    return true;
}

static char *build_new_path(server_t *serv, client_t *client, char *args)
{
    char *tmp;
    char *result;

    if (args[0] == '/')
        return get_absolute_path(serv->complete_root_dir, args);
    tmp = get_absolute_path(client->complete_current_dir, args);
    result = normalize_relative_path(tmp);
    free(tmp);
    return result;
}

bool check_directory_access(client_t *client, const char *path)
{
    DIR *dir = opendir(path);

    if (!dir) {
        send_reply(client, RPL_FILE_UNAVAILABLE, "Failed to change directory");
        return false;
    }
    closedir(dir);
    return true;
}

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

int cwd_command(server_t *serv, client_t *client, char *args)
{
    char *new_complete_path;

    if (!validate_cwd_args(client, args))
        return 0;
    if (!is_valid_path(serv->complete_root_dir, client->complete_current_dir,
        args)) {
        send_reply(client, RPL_FILE_UNAVAILABLE, "Access denied");
        return 0;
    }
    new_complete_path = build_new_path(serv, client, args);
    if (!check_directory_access(client, new_complete_path)) {
        free(new_complete_path);
        return 0;
    }
    update_client_paths(serv, client, new_complete_path);
    free(new_complete_path);
    send_reply(client, RPL_FILE_ACTION_OK, "Directory successfully changed");
    return 0;
}
