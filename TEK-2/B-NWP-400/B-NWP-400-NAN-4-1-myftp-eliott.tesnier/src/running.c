/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** running
*/

#include "myftp.h"

static void handle_new_connection(server_t *serv)
{
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int client_fd;

    client_fd = accept(serv->socket_fd, (struct sockaddr *)&client_addr,
        &addr_len);
    if (client_fd < 0)
        return;
    if (serv->nb_clients >= MAX_CLIENTS) {
        close(client_fd);
        return;
    }
    add_client(serv, client_fd);
}

static void cleanup_client_data(FILE *fp, server_t *serv, int i)
{
    fclose(fp);
    remove_client(serv, i);
}

static char *read_client_line(FILE *fp, ssize_t *read_size)
{
    char *buffer = malloc(BUFFER_SIZE);
    int fd = fileno(fp);

    if (!buffer)
        return NULL;
    memset(buffer, 0, BUFFER_SIZE);
    *read_size = read(fd, buffer, BUFFER_SIZE - 1);
    if (*read_size <= 0) {
        free(buffer);
        return NULL;
    }
    buffer[*read_size] = '\0';
    return buffer;
}

static int process_client_line(server_t *serv, int client_index, char *line)
{
    char *dup = NULL;

    if (line[0] == '\0')
        return 0;
    dup = strdup(line);
    return handle_client_command(serv, &serv->clients[client_index - 1], dup);
}

static void process_gotten_lien(server_t *serv, int i, char *line, FILE *fp)
{
    client_t *client = &serv->clients[i - 1];
    char *clrf = NULL;

    strcat(client->buffer, line);
    while (1) {
        clrf = strstr(client->buffer, "\r\n");
        if (!clrf)
            break;
        *clrf = '\0';
        if (process_client_line(serv, i, client->buffer) != 0) {
            cleanup_client_data(fp, serv, i);
            return;
        }
        memmove(client->buffer, clrf + 2, strlen(clrf + 2) + 1);
    }
}

static void handle_client_data(server_t *serv, int i)
{
    FILE *fp = fdopen(serv->poll_fds[i].fd, "r");
    char *line;
    ssize_t read;

    if (!fp) {
        remove_client(serv, i);
        return;
    }
    line = read_client_line(fp, &read);
    if (!line) {
        cleanup_client_data(fp, serv, i);
        return;
    }
    process_gotten_lien(serv, i, line, fp);
    free(line);
}

static bool handle_poll_error(void)
{
    if (errno != EINTR)
        return true;
    return false;
}

static void process_client_connections(server_t *serv)
{
    for (int i = 1; i <= serv->nb_clients; i++) {
        if (!(serv->poll_fds[i].revents & POLLIN))
            continue;
        handle_client_data(serv, i);
    }
}

void run_server(server_t *serv)
{
    int poll_result;

    while (1) {
        handle_child_signal(serv);
        poll_result = poll(serv->poll_fds, serv->nb_clients + 1, -1);
        if (poll_result < 0 && handle_poll_error())
            break;
        if (serv->poll_fds[0].revents & POLLIN)
            handle_new_connection(serv);
        process_client_connections(serv);
    }
}
