/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** user
*/

#include "myftp.h"

int user_command(server_t *serv, client_t *client, char *username)
{
    (void)serv;
    if (!username || strlen(username) == 0) {
        send_reply(client, RPL_ERROR, "Invalid username");
        return 0;
    }
    client->state = PENDING_AUTH;
    strncpy(client->username, username, USERNAME_MAX_LEN - 1);
    client->username[USERNAME_MAX_LEN - 1] = '\0';
    send_reply(client, RPL_USERNAME_OK, "Username okay, need password.");
    return 0;
}
