/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** help
*/

#include "myftp.h"

static const command_help_t COMMAND_HELP[] = {
    {"USER",
        "USER <SP> <username> <CRLF> : Specify user for authentication"},
    {"PASS",
        "PASS <SP> <password> <CRLF> : Specify password for authentication"},
    {"CWD",
        "CWD <SP> <pathname> <CRLF> : Change working directory"},
    {"CDUP",
        "CDUP <CRLF> : Change to parent directory"},
    {"QUIT",
        "QUIT <CRLF> : Close connection"},
    {"DELE",
        "DELE <SP> <pathname> <CRLF> : Delete file"},
    {"PWD",
        "PWD <CRLF> : Print working directory"},
    {"PASV",
        "PASV <CRLF> : Enter passive mode"},
    {"PORT",
        "PORT <SP> <host-port> <CRLF> : Enter active mode"},
    {"HELP",
        "HELP [<SP> <string>] <CRLF> : List available commands"},
    {"NOOP",
        "NOOP <CRLF> : Do nothing"},
    {"RETR",
        "RETR <SP> <pathname> <CRLF> : Download file"},
    {"STOR",
        "STOR <SP> <pathname> <CRLF> : Upload file"},
    {"LIST",
        "LIST [<SP> <pathname>] <CRLF> : List files"},
    {"MKD",
        "MKD <SP> <pathname> <CRLF> : Create directory"},
    {"RMD",
        "RMD <SP> <pathname> <CRLF> : Remove directory"},
    {"RNFR",
        "RNFR <SP> <pathname> <CRLF> : Rename from"},
    {"RNTO",
        "RNTO <SP> <pathname> <CRLF> : Rename to"},
    {"CPFR",
        "CPFR <SP> <pathname> <CRLF> : Copy from"},
    {"CPTO",
        "CPTO <SP> <pathname> <CRLF> : Copy to"},
    {"SIZE",
        "SIZE <SP> <pathname> <CRLF> : Get file size"},
    {"MDTM",
        "MDTM <SP> <pathname> <CRLF> : Get file modification time"},
    {NULL, NULL}
};

static const char *get_command_help(const char *cmd)
{
    for (int i = 0; COMMAND_HELP[i].cmd != NULL; i++) {
        if (!strcasecmp(cmd, COMMAND_HELP[i].cmd))
            return COMMAND_HELP[i].help;
    }
    return NULL;
}

int help_command(server_t *serv, client_t *client, char *args)
{
    char *cmd = strtok(args, " \r\n");
    char *helpmsg = NULL;

    (void)serv;
    if (cmd) {
        helpmsg = get_command_help(cmd) ? strdup(get_command_help(cmd)) : NULL;
        if (helpmsg)
            send_reply(client, RPL_HELP_MESSAGE, helpmsg);
        else
            send_reply(client, RPL_HELP_MESSAGE, "Unknown command");
    } else {
        send_reply(client, RPL_HELP_MESSAGE,
            "Commands available: USER PASS PWD CWD CDUP DELE PASV PORT "
            "RETR STOR LIST QUIT HELP NOOP MKD RMD RNFR RNTO CPFR CPTO "
            "SIZE MDTM");
    }
    if (helpmsg)
        free(helpmsg);
    return 0;
}
