/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** paths
*/

#include "myftp.h"

char *normalize_path(const char *path)
{
    char *normalized = strdup(path);
    char *ptr = normalized;
    size_t len;

    while (*ptr) {
        if (*ptr == '\\')
            *ptr = '/';
        ptr++;
    }
    len = strlen(normalized);
    if (len > 1 && normalized[len - 1] == '/')
        normalized[len - 1] = '\0';
    return normalized;
}

char *get_absolute_path(const char *base_path, const char *relative_path)
{
    char *result = malloc(PATH_MAX_LEN);
    char *normalized = normalize_path(relative_path);
    char *root_dir;
    char *root_start;

    if (normalized[0] == '/') {
        root_dir = strdup(base_path);
        root_start = strstr(root_dir, normalized);
        if (root_start) {
            snprintf(result, PATH_MAX_LEN, "%s", root_dir);
        } else {
            snprintf(result, PATH_MAX_LEN, "%s%s", root_dir, normalized);
        }
        free(root_dir);
    } else {
        snprintf(result, PATH_MAX_LEN, "%s/%s", base_path, normalized);
    }
    free(normalized);
    return result;
}

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

bool is_valid_path(const char *root_path, const char *current_path,
    const char *new_path)
{
    char *abs_path;
    bool valid;

    if (new_path[0] == '/') {
        abs_path = handle_absolute_path(root_path, new_path);
    } else {
        abs_path = handle_relative_path(current_path, new_path);
    }
    valid = validate_normalized_path(root_path, abs_path);
    free(abs_path);
    return valid;
}

bool is_subpath(const char *parent, const char *child)
{
    char *norm_parent = normalize_path(parent);
    char *norm_child = normalize_path(child);
    bool result = strncmp(norm_child, norm_parent, strlen(norm_parent)) == 0;

    free(norm_parent);
    free(norm_child);
    return result;
}

bool check_file_access(client_t *client, const char *path)
{
    char *abs_path;
    struct stat st;
    bool result = false;

    if (!is_valid_path(client->complete_current_dir,
        client->complete_current_dir, path))
        return false;
    abs_path = get_absolute_path(client->complete_current_dir, path);
    if (stat(abs_path, &st) == 0) {
        if (S_ISREG(st.st_mode) && (st.st_mode & S_IRUSR))
            result = true;
    }
    free(abs_path);
    return result;
}
