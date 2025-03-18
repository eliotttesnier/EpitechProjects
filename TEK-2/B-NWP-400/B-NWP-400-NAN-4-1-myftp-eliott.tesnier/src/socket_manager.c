/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** socket_manager
*/

#include "myftp.h"

static int create_socket(void)
{
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;

    if (sock_fd < 0)
        return -1;
    if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        close(sock_fd);
        return -1;
    }
    return sock_fd;
}

static int bind_socket(int sock_fd, int port)
{
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sock_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        return -1;
    return 0;
}

int setup_server_socket(int port)
{
    int sock_fd = create_socket();

    if (sock_fd < 0)
        return -1;
    if (bind_socket(sock_fd, port) < 0) {
        close(sock_fd);
        return -1;
    }
    if (listen(sock_fd, MAX_CLIENTS) < 0) {
        close(sock_fd);
        return -1;
    }
    return sock_fd;
}

int init_poll_structures(server_t *serv)
{
    serv->poll_fds = malloc(sizeof(struct pollfd) * (MAX_CLIENTS + 1));
    serv->clients = malloc(sizeof(client_t) * MAX_CLIENTS);
    if (!serv->poll_fds || !serv->clients)
        return -1;
    serv->poll_fds[0].fd = serv->socket_fd;
    serv->poll_fds[0].events = POLLIN;
    serv->nb_clients = 0;
    return 0;
}
