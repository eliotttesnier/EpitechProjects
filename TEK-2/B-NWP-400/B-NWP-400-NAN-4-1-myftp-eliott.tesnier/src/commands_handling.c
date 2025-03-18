/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** commands
*/

#include "myftp.h"
#include <ctype.h>

const command_t commands[] = {
    {"USER", user_command, false},
    {"PASS", pass_command, false},
    {"QUIT", quit_command, false},
    {"HELP", help_command, false},
    {"NOOP", noop_command, false},
    {"PWD", pwd_command, true},
    {"CWD", cwd_command, true},
    {"CDUP", cdup_command, true},
    {"DELE", dele_command, true},
    {"PASV", pasv_command, true},
    {"PORT", port_command, true},
    {"RETR", retr_command, true},
    {"STOR", stor_command, true},
    {"LIST", list_command, true},
    {"MKD", mkd_command, true},
    {"RMD", rmd_command, true},
    {"RNFR", rnfr_command, true},
    {"RNTO", rnto_command, true},
    {"CPFR", cpfr_command, true},
    {"CPTO", cpto_command, true},
    {"SIZE", size_command, true},
    {"MDTM", mdtm_command, true},
    {NULL, NULL, false}
};

static void parse_command(char *buffer, char *cmd, char *args)
{
    char *token;

    cmd[0] = '\0';
    args[0] = '\0';
    if (!buffer || !buffer[0])
        return;
    while (*buffer && isspace(*buffer))
        buffer++;
    if (!*buffer)
        return;
    token = strtok(buffer, " \t\r\n");
    if (!token)
        return;
    strncpy(cmd, token, BUFFER_SIZE - 1);
    cmd[BUFFER_SIZE - 1] = '\0';
    token = strtok(NULL, " \t\r\n");
    if (token) {
        strncpy(args, token, BUFFER_SIZE - 1);
        args[BUFFER_SIZE - 1] = '\0';
    }
}

int handle_client_command(server_t *serv, client_t *client, char *buffer)
{
    char cmd[BUFFER_SIZE] = {0};
    char args[BUFFER_SIZE] = {0};

    parse_command(buffer, cmd, args);
    if (cmd[0] == '\0') {
        send_reply(client, RPL_ERROR, "Invalid command");
        return 0;
    }
    for (int i = 0; commands[i].name; i++) {
        if (strcmp(commands[i].name, cmd) == 0 && commands[i].need_auth &&
            client->state != AUTHENTICATED) {
            send_reply(client, RPL_NOT_LOGGED_IN, "Not authenticated");
            return 0;
        }
        if (strcmp(commands[i].name, cmd) == 0)
            return commands[i].handler(serv, client, args);
    }
    send_reply(client, RPL_ERROR, "Unknown command");
    return 0;
}
