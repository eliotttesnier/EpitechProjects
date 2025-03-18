/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** port
*/

#include "myftp.h"

static int parse_port_args(char *args, struct sockaddr_in *addr)
{
    int h1;
    int h2;
    int h3;
    int h4;
    int p1;
    int p2;
    char ip[16];

    if (sscanf(args, "%d,%d,%d,%d,%d,%d", &h1, &h2, &h3, &h4, &p1, &p2) != 6) {
        return -1;
    }
    if (h1 < 0 || h2 < 0 || h3 < 0 || h4 < 0 || p1 < 0 || p2 < 0 ||
        h1 > 255 || h2 > 255 || h3 > 255 || h4 > 255 || p1 > 255 || p2 > 255) {
        return -1;
    }
    snprintf(ip, sizeof(ip), "%d.%d.%d.%d", h1, h2, h3, h4);
    addr->sin_family = AF_INET;
    addr->sin_port = htons(p1 * 256 + p2);
    return inet_pton(AF_INET, ip, &addr->sin_addr) == 1 ? 0 : -1;
}

static int setup_active_mode(client_t *client, struct sockaddr_in *addr)
{
    client->data_addr = *addr;
    client->mode = ACTIVE;
    return 0;
}

int port_command(server_t *serv, client_t *client, char *args)
{
    struct sockaddr_in addr = {0};

    (void)serv;
    if (client->passive_listen_fd != -1)
        close(client->passive_listen_fd);
    if (client->data_fd != -1)
        close(client->data_fd);
    if (parse_port_args(args, &addr) < 0) {
        send_reply(client, RPL_SYNTAX_ERROR, "Invalid PORT command.");
        return 0;
    }
    if (setup_active_mode(client, &addr) == 0) {
        client->mode = ACTIVE;
        send_reply(client, RPL_COMMAND_OK, "PORT command successful.");
    }
    return 0;
}
