/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** tests_cwd
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
Test(cwd_command, no_arguments)
{
    server_t *serv = create_server();
    client_t *client = create_client();
    char *args = NULL;
    int pipe_fd[2];

    setup_pipe(pipe_fd);
    client->control_fd = pipe_fd[1];

    cr_assert_eq(cwd_command(serv, client, args), 0);
    check_reply(pipe_fd[0], "501 Missing path argument\r\n");

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    free(client);
    free(serv->poll_fds);
    free(serv->clients);
    free(serv);
}

// Past root
Test(cwd_command, past_root)
{
    server_t *serv = create_server();
    client_t *client = create_client();
    char *args = "/../../";
    int pipe_fd[2];

    setup_pipe(pipe_fd);
    client->control_fd = pipe_fd[1];

    cr_assert_eq(cwd_command(serv, client, args), 0);
    check_reply(pipe_fd[0], "550 Access denied\r\n");

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    free(client);
    free(serv->poll_fds);
    free(serv->clients);
    free(serv);
}

// Not existing directory
Test(cwd_command, not_existing_directory)
{
    server_t *serv = create_server();
    client_t *client = create_client();
    char *args = "not_existing_directory";
    int pipe_fd[2];

    setup_pipe(pipe_fd);
    client->control_fd = pipe_fd[1];

    cr_assert_eq(cwd_command(serv, client, args), 0);
    check_reply(pipe_fd[0], "550 Failed to change directory\r\n");

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    free(client);
    free(serv->poll_fds);
    free(serv->clients);
    free(serv);
}

// Valid directory
Test(cwd_command, valid_directory)
{
    server_t *serv = create_server();
    client_t *client = create_client();
    char *args = "tests";
    int pipe_fd[2];

    setup_pipe(pipe_fd);
    client->control_fd = pipe_fd[1];

    cr_assert_eq(cwd_command(serv, client, args), 0);
    check_reply(pipe_fd[0], "250 Directory successfully changed\r\n");

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    free(client);
    free(serv->poll_fds);
    free(serv->clients);
    free(serv);
}

// Valid directory with absolute path
Test(cwd_command, valid_directory_absolute_path)
{
    server_t *serv = create_server();
    client_t *client = create_client();
    char *args = "/tests";
    int pipe_fd[2];

    setup_pipe(pipe_fd);
    client->control_fd = pipe_fd[1];

    cr_assert_eq(cwd_command(serv, client, args), 0);
    check_reply(pipe_fd[0], "250 Directory successfully changed\r\n");

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    free(client);
    free(serv->poll_fds);
    free(serv->clients);
    free(serv);
}
