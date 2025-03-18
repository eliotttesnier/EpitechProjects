/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** tests_pass
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "myftp.h"

server_t *create_server(void);
client_t *create_client(void);
void check_reply(int fd, const char *expected);
void setup_pipe(int *pipe_fd);
void redirect_all_std(void);

// Already logged in
Test(pass_command, already_logged_in)
{
    server_t *serv = create_server();
    client_t *client = create_client();
    char *args = NULL;
    int pipe_fd[2];

    setup_pipe(pipe_fd);
    client->control_fd = pipe_fd[1];
    client->state = AUTHENTICATED;

    cr_assert_eq(pass_command(serv, client, args), 0);
    check_reply(pipe_fd[0], "500 Already logged in\r\n");

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    free(client);
    free(serv->poll_fds);
    free(serv->clients);
    free(serv);
}

// Need USER first
Test(pass_command, need_user_first)
{
    server_t *serv = create_server();
    client_t *client = create_client();
    char *args = NULL;
    int pipe_fd[2];

    setup_pipe(pipe_fd);
    client->control_fd = pipe_fd[1];
    client->state = CONNECTED;

    cr_assert_eq(pass_command(serv, client, args), 0);
    check_reply(pipe_fd[0], "332 Need USER first\r\n");

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    free(client);
    free(serv->poll_fds);
    free(serv->clients);
    free(serv);
}

// Anonymous user
Test(pass_command, anonymous_user)
{
    server_t *serv = create_server();
    client_t *client = create_client();
    char *args = NULL;
    int pipe_fd[2];

    setup_pipe(pipe_fd);
    client->control_fd = pipe_fd[1];
    client->state = PENDING_AUTH;
    strncpy(client->username, "Anonymous", USERNAME_MAX_LEN - 1);

    cr_assert_eq(pass_command(serv, client, args), 0);
    cr_assert_eq(client->state, AUTHENTICATED);
    check_reply(pipe_fd[0], "230 User logged in, proceed.\r\n");

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    free(client);
    free(serv->poll_fds);
    free(serv->clients);
    free(serv);
}

// Invalid user
Test(pass_command, invalid_user)
{
    server_t *serv = create_server();
    client_t *client = create_client();
    char *args = NULL;
    int pipe_fd[2];

    setup_pipe(pipe_fd);
    client->control_fd = pipe_fd[1];
    client->state = PENDING_AUTH;
    strncpy(client->username, "test", USERNAME_MAX_LEN - 1);

    cr_assert_eq(pass_command(serv, client, args), 0);
    cr_assert_eq(client->state, CONNECTED);
    check_reply(pipe_fd[0], "530 Authentication failed.\r\n");

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    free(client);
    free(serv->poll_fds);
    free(serv->clients);
    free(serv);
}
