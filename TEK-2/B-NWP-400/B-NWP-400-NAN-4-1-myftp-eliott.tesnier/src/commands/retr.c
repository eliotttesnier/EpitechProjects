/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** retr
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

static void transfer_file(int data_fd, FILE *file)
{
    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    ssize_t bytes_written;
    bool continue_transfer = true;

    while (continue_transfer) {
        bytes_read = fread(buffer, 1, BUFFER_SIZE, file);
        if (bytes_read <= 0)
            break;
        bytes_written = write(data_fd, buffer, bytes_read);
        if (bytes_written < 0 || (size_t)bytes_written != bytes_read) {
            break;
        }
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

static FILE *open_file_for_transfer(const char *abs_path)
{
    FILE *file = fopen(abs_path, "r");

    if (!file)
        return NULL;
    return file;
}

static void perform_transfer(client_t *client, const char *filepath)
{
    FILE *file;
    int data_fd;
    char *abs_path = resolve_path(client, filepath);

    if (!abs_path)
        exit(1);
    file = open_file_for_transfer(abs_path);
    free(abs_path);
    if (!file)
        exit(1);
    data_fd = open_data_connection(client);
    if (data_fd < 0) {
        fclose(file);
        exit(1);
    }
    transfer_file(data_fd, file);
    fclose(file);
    close(data_fd);
}

static void handle_child_transfer(client_t *client, const char *filepath)
{
    signal(SIGPIPE, SIG_IGN);
    perform_transfer(client, filepath);
    exit(0);
}

static int setup_transfer(client_t *client, const char *path)
{
    pid_t pid;

    send_reply(client, RPL_FILE_STATUS_OK,
        "Opening data connection for file transfer.");
    pid = fork();
    if (pid < 0) {
        send_reply(client, RPL_ERROR, "Could not create process.");
        return -1;
    }
    if (pid == 0) {
        handle_child_transfer(client, path);
    } else {
        client->data_pid = pid;
    }
    return 0;
}

static int check_retr_preconditions(client_t *client, char *path)
{
    char *normalized_path;

    if (client->mode == NONE) {
        send_reply(client, RPL_CANT_OPEN_DATA_CNX, "Use PORT or PASV first.");
        return -1;
    }
    normalized_path = normalize_relative_path(path);
    if (!normalized_path) {
        send_reply(client, RPL_FILE_UNAVAILABLE, "Invalid path.");
        return -1;
    }
    if (!check_file_access(client, normalized_path)) {
        free(normalized_path);
        send_reply(client, RPL_FILE_UNAVAILABLE,
            "File unavailable or access denied.");
        return -1;
    }
    free(normalized_path);
    return 0;
}

int retr_command(server_t *serv, client_t *client, char *args)
{
    char *path = strtok(args, " \r\n");

    (void)serv;
    if (!path) {
        send_reply(client, RPL_SYNTAX_ERROR, "No filename specified.");
        return 0;
    }
    if (check_retr_preconditions(client, path) < 0)
        return 0;
    return setup_transfer(client, path);
}
