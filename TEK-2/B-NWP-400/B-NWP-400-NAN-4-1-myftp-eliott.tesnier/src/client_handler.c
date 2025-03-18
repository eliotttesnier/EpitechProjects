/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** client_handler
*/

#include "myftp.h"

void send_reply(client_t *client, reply_code_t code, char *msg)
{
    char buffer[BUFFER_SIZE];

    snprintf(buffer, sizeof(buffer), "%d %s\r\n", code, msg);
    write(client->control_fd, buffer, strlen(buffer));
}

void add_client(server_t *serv, int fd)
{
    int idx = serv->nb_clients;

    serv->clients[idx] = (client_t){0};
    serv->clients[idx].control_fd = fd;
    serv->clients[idx].data_fd = -1;
    serv->clients[idx].passive_listen_fd = -1;
    serv->clients[idx].state = CONNECTED;
    serv->clients[idx].mode = NONE;
    serv->clients[idx].buffer = calloc(1, BUFFER_SIZE);
    serv->clients[idx].rnfr_path = NULL;
    serv->clients[idx].cpfr_path = NULL;
    strncpy(serv->clients[idx].complete_current_dir, serv->complete_root_dir,
        PATH_MAX_LEN - 1);
    strncpy(serv->clients[idx].current_dir, serv->root_dir, PATH_MAX_LEN - 1);
    serv->poll_fds[idx + 1].fd = fd;
    serv->poll_fds[idx + 1].events = POLLIN;
    serv->nb_clients++;
    send_reply(&serv->clients[idx], RPL_SERVICE_READY,
        "Service ready for new user.");
}

void remove_client(server_t *serv, int i)
{
    client_t *client = &serv->clients[i - 1];

    close(client->control_fd);
    if (client->data_fd != -1)
        close(client->data_fd);
    if (client->passive_listen_fd != -1)
        close(client->passive_listen_fd);
    for (int j = i - 1; j < serv->nb_clients - 1; j++) {
        serv->clients[j] = serv->clients[j + 1];
        serv->poll_fds[j + 1] = serv->poll_fds[j + 2];
    }
    if (client->rnfr_path)
        free(client->rnfr_path);
    if (client->cpfr_path)
        free(client->cpfr_path);
    serv->nb_clients--;
}
