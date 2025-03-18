/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** cpto
*/

#include "myftp.h"

bool validate_cpto_args(server_t *s, client_t *client, char *args)
{
    char *path = NULL;

    if (!args || strlen(args) == 0) {
        send_reply(client, RPL_SYNTAX_ERROR, "Missing path argument");
        return false;
    }
    if (!client->cpfr_path) {
        send_reply(client, RPL_BAD_SEQUENCE, "CPFR not sent");
        return false;
    }
    path = get_abs(s, client, args);
    if (is_file_path_existing(path)) {
        send_reply(client, RPL_FILE_UNAVAILABLE, "Path already exists");
        free(path);
        return false;
    }
    return true;
}

static bool check_fopen_error(FILE *source, FILE *dest)
{
    if (!source || !dest) {
        if (source)
            fclose(source);
        if (dest)
            fclose(dest);
        return true;
    }
    return false;
}

static int copy_permissions(const char *src, const char *dst)
{
    struct stat src_stat;
    struct stat dst_stat;

    if (stat(src, &src_stat) == -1)
        return -1;
    if (stat(dst, &dst_stat) == -1)
        return -1;
    if (chmod(dst, src_stat.st_mode) == -1)
        return -1;
    return 0;
}

static int copy_file(const char *src, const char *dst)
{
    char buffer[4096];
    FILE *source = fopen(src, "rb");
    FILE *dest = fopen(dst, "wb");
    size_t bytes;

    if (check_fopen_error(source, dest))
        return -1;
    bytes = fread(buffer, 1, sizeof(buffer), source);
    while (bytes > 0) {
        if (fwrite(buffer, 1, bytes, dest) != bytes) {
            fclose(source);
            fclose(dest);
            return -1;
        }
        bytes = fread(buffer, 1, sizeof(buffer), source);
    }
    fclose(source);
    fclose(dest);
    return copy_permissions(src, dst);
}

int cpto_command(server_t *serv, client_t *client, char *args)
{
    char *abs_path = NULL;

    if (!validate_cpto_args(serv, client, args))
        return 0;
    abs_path = get_abs(serv, client, args);
    if (copy_file(client->cpfr_path, abs_path) == -1) {
        send_reply(client, RPL_ERROR, strerror(errno));
        free(abs_path);
        return 0;
    }
    send_reply(client, RPL_FILE_ACTION_OK, "File copied successfully");
    free(abs_path);
    free(client->cpfr_path);
    client->cpfr_path = NULL;
    return 0;
}
