/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** quit
*/

#include "myftp.h"

int quit_command(server_t *serv, client_t *client, char *args)
{
    (void)args;
    (void)serv;
    send_reply(client, RPL_CLOSING_CONTROL_CONNECTION, "Goodbye");
    return 1;
}
