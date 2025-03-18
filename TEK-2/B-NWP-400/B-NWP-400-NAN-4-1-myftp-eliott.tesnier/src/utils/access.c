/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** access
*/

#include "myftp.h"

static char *handle_absolute_path(const char *root_path, const char *new_path)
{
    char *root_dir = strdup(root_path);
    char *abs_path = malloc(PATH_MAX_LEN);
    char *root_start = strstr(root_dir, new_path);

    if (root_start) {
        strncpy(abs_path, root_dir, PATH_MAX_LEN);
    } else {
        snprintf(abs_path, PATH_MAX_LEN, "%s%s", root_dir, new_path);
    }
    free(root_dir);
    return abs_path;
}

static char *handle_relative_path(const char *current_path,
    const char *new_path)
{
    char *tmp = get_absolute_path(current_path, new_path);
    char *abs_path = normalize_relative_path(tmp);

    free(tmp);
    return abs_path;
}

static bool validate_normalized_path(const char *root_path,
    const char *abs_path)
{
    char *norm_abs = normalize_relative_path(abs_path);
    bool valid = is_subpath(root_path, norm_abs);

    free(norm_abs);
    return valid;
}

bool is_file_path_existing(const char *path)
{
    struct stat st;

    return stat(path, &st) == 0 && S_ISREG(st.st_mode) && !S_ISDIR(st.st_mode);
}

bool is_folder_path_existing(const char *path)
{
    struct stat st;

    return stat(path, &st) == 0 && S_ISDIR(st.st_mode);
}

bool is_file_path_valid(server_t *serv, client_t *client, const char *path)
{
    char *abs_path;
    bool valid;

    if (path[0] == '/') {
        abs_path = handle_absolute_path(serv->complete_root_dir, path);
    } else {
        abs_path = handle_relative_path(client->complete_current_dir, path);
    }
    valid = validate_normalized_path(serv->complete_root_dir, abs_path);
    free(abs_path);
    return valid;
}
