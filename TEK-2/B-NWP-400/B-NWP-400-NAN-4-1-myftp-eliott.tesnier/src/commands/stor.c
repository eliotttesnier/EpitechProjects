/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** stor
*/

#include "myftp.h"

static int open_data_connection(client_t *client)
{
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    int data_fd = -1;

    if (client->mode == PASSIVE) {
        data_fd = accept(client->passive_listen_fd,
            (struct sockaddr *)&addr, &addr_len);
        close(client->passive_listen_fd);
        client->passive_listen_fd = -1;
        return data_fd;
    }
    data_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (data_fd >= 0 && connect(data_fd,
        (struct sockaddr *)&client->data_addr,
        sizeof(client->data_addr)) < 0) {
        close(data_fd);
        data_fd = -1;
    }
    return data_fd;
}

static void receive_file(int data_fd, FILE *file)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    size_t bytes_written;

    bytes_read = read(data_fd, buffer, BUFFER_SIZE);
    while (bytes_read > 0) {
        bytes_written = fwrite(buffer, 1, bytes_read, file);
        if (bytes_written != (size_t)bytes_read)
            break;
        bytes_read = read(data_fd, buffer, BUFFER_SIZE);
    }
}

static char *resolve_path(client_t *client, const char *filepath)
{
    char *normalized_path = normalize_relative_path(filepath);
    char *abspath;

    if (!normalized_path)
        return NULL;
    abspath = get_absolute_path(client->complete_current_dir, normalized_path);
    free(normalized_path);
    return abspath;
}

static FILE *open_file_for_upload(const char *abs_path)
{
    FILE *file = fopen(abs_path, "w");

    if (!file)
        return NULL;
    return file;
}

static void perform_upload(client_t *client, const char *filepath)
{
    FILE *file;
    int data_fd;
    char *abs_path = resolve_path(client, filepath);

    if (!abs_path)
        exit(1);
    file = open_file_for_upload(abs_path);
    free(abs_path);
    if (!file)
        exit(1);
    data_fd = open_data_connection(client);
    if (data_fd < 0) {
        fclose(file);
        exit(1);
    }
    receive_file(data_fd, file);
    fclose(file);
    close(data_fd);
}

static void handle_child_upload(client_t *client, const char *filepath)
{
    signal(SIGPIPE, SIG_IGN);
    perform_upload(client, filepath);
    exit(0);
}

static int setup_upload(client_t *client, const char *path)
{
    pid_t pid;

    send_reply(client, RPL_FILE_STATUS_OK,
        "Opening data connection for file upload.");
    pid = fork();
    if (pid < 0) {
        send_reply(client, RPL_ERROR, "Could not create process.");
        return -1;
    }
    if (pid == 0) {
        handle_child_upload(client, path);
    } else {
        client->data_pid = pid;
    }
    return 0;
}

static int check_stor_preconditions(client_t *client, char *path)
{
    char *abs_path;
    char *normalized;

    normalized = normalize_relative_path(path);
    if (!normalized) {
        send_reply(client, RPL_FILE_UNAVAILABLE, "Invalid path.");
        return -1;
    }
    abs_path = get_absolute_path(client->complete_current_dir, normalized);
    free(normalized);
    if (!abs_path || !is_subpath(client->complete_current_dir, abs_path)) {
        free(abs_path);
        send_reply(client, RPL_FILE_UNAVAILABLE,
            "File unavailable or access denied.");
        return -1;
    }
    free(abs_path);
    return 0;
}

int stor_command(server_t *serv, client_t *client, char *args)
{
    char *path = strtok(args, " \r\n");

    (void)serv;
    if (!path) {
        send_reply(client, RPL_SYNTAX_ERROR, "No filename specified.");
        return 0;
    }
    if (client->mode == NONE) {
        send_reply(client, RPL_CANT_OPEN_DATA_CNX, "Use PORT or PASV first.");
        return 0;
    }
    if (check_stor_preconditions(client, path) < 0)
        return 0;
    return setup_upload(client, path);
}
