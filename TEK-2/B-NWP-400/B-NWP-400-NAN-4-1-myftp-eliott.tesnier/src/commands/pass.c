/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** pass
*/

#include "myftp.h"

int pass_command(server_t *serv, client_t *client, char *password)
{
    (void)serv;
    (void)password;
    if (client->state == AUTHENTICATED) {
        send_reply(client, RPL_ERROR, "Already logged in");
        return 0;
    }
    if (client->state != PENDING_AUTH) {
        send_reply(client, RPL_NEED_ACCOUNT, "Need USER first");
        return 0;
    }
    if (strcasecmp(client->username, "Anonymous") == 0) {
        client->state = AUTHENTICATED;
        send_reply(client, RPL_LOGGED_IN, "User logged in, proceed.");
    } else {
        client->state = CONNECTED;
        send_reply(client, RPL_NOT_LOGGED_IN, "Authentication failed.");
    }
    return 0;
}
