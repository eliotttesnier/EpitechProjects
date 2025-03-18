/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** tests_pwd
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "myftp.h"

server_t *create_server(void);
client_t *create_client(void);
void check_reply(int fd, const char *expected);
void setup_pipe(int *pipe_fd);
void redirect_all_std(void);

// PWD
Test(pwd_command, no_arguments)
{
    server_t *serv = create_server();
    client_t *client = create_client();
    char *args = NULL;
    int pipe_fd[2];

    setup_pipe(pipe_fd);
    client->control_fd = pipe_fd[1];

    cr_assert_eq(pwd_command(serv, client, args), 0);
    check_reply(pipe_fd[0], "257 \"/\" is the current directory\r\n");

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    free(client);
    free(serv->poll_fds);
    free(serv->clients);
    free(serv);
}
