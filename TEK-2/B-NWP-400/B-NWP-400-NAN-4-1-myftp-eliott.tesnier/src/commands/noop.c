/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** noop
*/

#include "myftp.h"

int noop_command(server_t *serv, client_t *client, char *args)
{
    (void)args;
    (void)serv;
    send_reply(client, RPL_COMMAND_OK, "NOOP ok.");
    return 0;
}
