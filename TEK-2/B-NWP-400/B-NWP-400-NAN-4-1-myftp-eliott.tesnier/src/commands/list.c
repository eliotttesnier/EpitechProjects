/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** list
*/

#include "myftp.h"
#include <time.h>

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

static void send_file_info(int data_fd, const char *filename,
    const struct stat *st)
{
    char buffer[BUFFER_SIZE];
    char time_str[13];

    strftime(time_str, sizeof(time_str), "%b %d %H:%M",
        localtime(&st->st_mtime));
    snprintf(buffer, sizeof(buffer),
        "%c%c%c%c%c%c%c%c%c%c %3lu %-8d %-8d %8lu %s %s\r\n",
        S_ISDIR(st->st_mode) ? 'd' : '-',
        (st->st_mode & S_IRUSR) ? 'r' : '-',
        (st->st_mode & S_IWUSR) ? 'w' : '-',
        (st->st_mode & S_IXUSR) ? 'x' : '-',
        (st->st_mode & S_IRGRP) ? 'r' : '-',
        (st->st_mode & S_IWGRP) ? 'w' : '-',
        (st->st_mode & S_IXGRP) ? 'x' : '-',
        (st->st_mode & S_IROTH) ? 'r' : '-',
        (st->st_mode & S_IWOTH) ? 'w' : '-',
        (st->st_mode & S_IXOTH) ? 'x' : '-',
        (unsigned long)st->st_nlink, st->st_uid, st->st_gid,
        (unsigned long)st->st_size, time_str, filename);
    write(data_fd, buffer, strlen(buffer));
}

static void list_directory(int data_fd, const char *path)
{
    DIR *dir = opendir(path);
    struct dirent *entry;
    struct stat st;
    char full_path[PATH_MAX_LEN];

    if (!dir)
        exit(1);
    for (entry = readdir(dir); entry != NULL; entry = readdir(dir)) {
        if (entry->d_name[0] == '.')
            continue;
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        if (stat(full_path, &st) == 0)
            send_file_info(data_fd, entry->d_name, &st);
    }
    closedir(dir);
}

static void list_single_file(int data_fd, const char *path)
{
    struct stat st;
    char *filename = strrchr(path, '/');

    if (!filename || stat(path, &st) != 0)
        exit(1);
    filename++;
    send_file_info(data_fd, filename, &st);
}

static void call_list(int data_fd, char *target)
{
    struct stat st;

    if (stat(target, &st) == 0) {
        if (S_ISDIR(st.st_mode))
            list_directory(data_fd, target);
        else
            list_single_file(data_fd, target);
    }
}

static void perform_list(server_t *s, client_t *client, const char *path)
{
    int data_fd = open_data_connection(client);
    char *target;

    if (data_fd < 0)
        exit(1);
    target = path ? get_abs(s, client, path) :
        strdup(client->complete_current_dir);
    if (!target
        || !is_subpath(client->complete_current_dir, target)) {
        free(target);
        close(data_fd);
        exit(1);
    }
    call_list(data_fd, target);
    free(target);
    close(data_fd);
}

static void handle_child_list(server_t *s, client_t *client, const char *path)
{
    signal(SIGPIPE, SIG_IGN);
    perform_list(s, client, path);
    exit(0);
}

static int setup_list(server_t *s, client_t *client, const char *path)
{
    pid_t pid;

    send_reply(client, RPL_FILE_STATUS_OK,
        "Opening data connection for directory listing.");
    pid = fork();
    if (pid < 0) {
        send_reply(client, RPL_ERROR, "Could not create process.");
        return -1;
    }
    if (pid == 0) {
        handle_child_list(s, client, path);
    } else {
        client->data_pid = pid;
    }
    return 0;
}

static bool is_existing_target(char *target, server_t *serv, client_t *client)
{
    struct stat st;
    char *abs_path = NULL;

    if (!target)
        return true;
    if (!is_file_path_valid(serv, client, target))
        return false;
    abs_path = get_abs(serv, client, target);
    if (stat(abs_path, &st) != 0)
        return false;
    return true;
}

int list_command(server_t *serv, client_t *client, char *args)
{
    char *path = args[0] ? strtok(args, " \r\n") : NULL;

    (void)serv;
    if (client->mode == NONE) {
        send_reply(client, RPL_CANT_OPEN_DATA_CNX, "Use PORT or PASV first.");
        return 0;
    }
    if (!is_existing_target(path, serv, client)) {
        send_reply(client, RPL_FILE_UNAVAILABLE,
            "No such file or directory or access denied.");
        return 0;
    }
    return setup_list(serv, client, path);
}
