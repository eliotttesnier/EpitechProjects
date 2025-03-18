/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** tests_help
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "myftp.h"

server_t *create_server(void);
client_t *create_client(void);
void check_reply(int fd, const char *expected);
void setup_pipe(int *pipe_fd);
void redirect_all_std(void);

// No arguments
Test(help_command, no_arguments)
{
    server_t *serv = create_server();
    client_t *client = create_client();
    char *args = "\r\n";
    int pipe_fd[2];

    setup_pipe(pipe_fd);
    client->control_fd = pipe_fd[1];

    cr_assert_eq(help_command(serv, client, args), 0);
    check_reply(pipe_fd[0], "214 Commands available: USER PASS PWD CWD CDUP DELE PASV PORT RETR STOR LIST QUIT HELP NOOP MKD RMD RNFR RNTO CPFR CPTO SIZE MDTM\r\n");

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    free(client);
    free(serv->poll_fds);
    free(serv->clients);
    free(serv);
}

// Invalid command
Test(help_command, invalid_command)
{
    server_t *serv = create_server();
    client_t *client = create_client();
    char *args = "INVALID";
    int pipe_fd[2];

    setup_pipe(pipe_fd);
    client->control_fd = pipe_fd[1];

    cr_assert_eq(help_command(serv, client, args), 0);
    check_reply(pipe_fd[0], "214 Unknown command\r\n");

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    free(client);
    free(serv->poll_fds);
    free(serv->clients);
    free(serv);
}

// Valid command
Test(help_command, valid_command)
{
    server_t *serv = create_server();
    client_t *client = create_client();
    char *args = "USER";
    int pipe_fd[2];

    setup_pipe(pipe_fd);
    client->control_fd = pipe_fd[1];

    cr_assert_eq(help_command(serv, client, args), 0);
    check_reply(pipe_fd[0], "214 USER <SP> <username> <CRLF> : Specify user for authentication\r\n");

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    free(client);
    free(serv->poll_fds);
    free(serv->clients);
    free(serv);
}
