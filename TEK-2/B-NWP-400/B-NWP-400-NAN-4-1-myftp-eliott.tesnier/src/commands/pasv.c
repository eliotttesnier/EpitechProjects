/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** pasv
*/

#include "myftp.h"

static int create_passive_socket(void)
{
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {0};

    if (sock_fd < 0)
        return -1;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = 0;
    if (bind(sock_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        close(sock_fd);
        return -1;
    }
    if (listen(sock_fd, 1) < 0) {
        close(sock_fd);
        return -1;
    }
    return sock_fd;
}

static void send_passive_response(client_t *client, struct sockaddr_in *addr)
{
    char response[BUFFER_SIZE];
    struct sockaddr_in local_addr;
    socklen_t len = sizeof(local_addr);
    unsigned char *ip;
    uint16_t port = ntohs(addr->sin_port);

    getsockname(client->control_fd, (struct sockaddr *)&local_addr, &len);
    ip = (unsigned char *)&local_addr.sin_addr.s_addr;
    snprintf(response, sizeof(response),
        "Entering Passive Mode (%d,%d,%d,%d,%d,%d).",
        ip[0], ip[1], ip[2], ip[3],
        port >> 8, port & 0xFF);
    send_reply(client, RPL_PASSIVE_MODE, response);
}

static int setup_passive_mode(client_t *client)
{
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);

    client->passive_listen_fd = create_passive_socket();
    if (client->passive_listen_fd < 0) {
        send_reply(client, RPL_ERROR, "Could not create passive socket.");
        return -1;
    }
    if (getsockname(client->passive_listen_fd,
        (struct sockaddr *)&addr, &addr_len) < 0) {
        close(client->passive_listen_fd);
        client->passive_listen_fd = -1;
        send_reply(client, RPL_ERROR, "Could not get socket information.");
        return -1;
    }
    send_passive_response(client, &addr);
    return 0;
}

int pasv_command(server_t *serv, client_t *client, char *args)
{
    (void)serv;
    (void)args;
    if (client->passive_listen_fd != -1)
        close(client->passive_listen_fd);
    if (client->data_fd != -1)
        close(client->data_fd);
    if (setup_passive_mode(client) == 0) {
        client->mode = PASSIVE;
        client->data_fd = -1;
    }
    return 0;
}
