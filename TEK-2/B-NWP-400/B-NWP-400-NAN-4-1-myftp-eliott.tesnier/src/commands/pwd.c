/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** pwd
*/

#include "myftp.h"

int pwd_command(server_t *serv, client_t *client, char *args)
{
    char buffer[BUFFER_SIZE] = {0};

    (void)args;
    (void)serv;
    snprintf(buffer, sizeof(buffer), "\"%s\" is the current directory",
        client->current_dir);
    send_reply(client, RPL_PATHNAME_CREATED, buffer);
    return 0;
}
