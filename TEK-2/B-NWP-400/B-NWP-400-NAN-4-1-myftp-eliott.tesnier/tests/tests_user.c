/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** tests_user
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "myftp.h"

server_t *create_server(void)
{
    server_t *serv = malloc(sizeof(server_t));

    serv->root_dir[0] = '/';
    serv->root_dir[1] = '\0';
    getcwd(serv->complete_root_dir, PATH_MAX_LEN);
    serv->complete_root_dir[PATH_MAX_LEN - 1] = '\0';
    serv->port = 4242;
    serv->socket_fd = 0;
    serv->nb_clients = 0;
    serv->poll_fds = malloc(sizeof(struct pollfd) * (MAX_CLIENTS + 1));
    serv->clients = malloc(sizeof(client_t) * MAX_CLIENTS);
    return serv;
}

client_t *create_client()
{
    client_t *client = malloc(sizeof(client_t));

    client->control_fd = 0;
    client->data_fd = 0;
    client->data_pid = 0;
    client->state = CONNECTED;
    client->mode = NONE;
    client->passive_listen_fd = 0;
    client->username[0] = 'A';
    client->username[1] = 'n';
    client->username[2] = 'o';
    client->username[3] = 'n';
    client->username[4] = 'y';
    client->username[5] = 'm';
    client->username[6] = 'o';
    client->username[7] = 'u';
    client->username[8] = 's';
    client->username[9] = '\0';
    client->current_dir[0] = '/';
    client->current_dir[1] = '\0';
    getcwd(client->complete_current_dir, PATH_MAX_LEN);
    client->complete_current_dir[PATH_MAX_LEN - 1] = '\0';
    return client;
}

void redirect_all_std(void);

void setup_pipe(int *pipe_fd)
{
    if (pipe(pipe_fd) == -1) {
        cr_assert_fail("Failed to create pipe");
    }
}

void check_reply(int fd, const char *expected)
{
    char buffer[BUFFER_SIZE];
    int n = read(fd, buffer, BUFFER_SIZE - 1);

    buffer[n] = '\0';
    cr_assert_str_eq(buffer, expected);
}

// No arguments
Test(user_command, no_arguments)
{
    server_t *serv = create_server();
    client_t *client = create_client();
    char *args = NULL;
    int pipe_fd[2];

    setup_pipe(pipe_fd);
    client->control_fd = pipe_fd[1];

    cr_assert_eq(user_command(serv, client, args), 0);
    check_reply(pipe_fd[0], "500 Invalid username\r\n");

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    free(client);
    free(serv->poll_fds);
    free(serv->clients);
    free(serv);
}

// Empty username
Test(user_command, empty_username)
{
    server_t *serv = create_server();
    client_t *client = create_client();
    char *args = "";
    int pipe_fd[2];

    setup_pipe(pipe_fd);
    client->control_fd = pipe_fd[1];

    cr_assert_eq(user_command(serv, client, args), 0);
    check_reply(pipe_fd[0], "500 Invalid username\r\n");

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    free(client);
    free(serv->poll_fds);
    free(serv->clients);
    free(serv);
}

// Valid username
Test(user_command, valid_username)
{
    server_t *serv = create_server();
    client_t *client = create_client();
    char *args = "anonymous";
    int pipe_fd[2];

    setup_pipe(pipe_fd);
    client->control_fd = pipe_fd[1];

    cr_assert_eq(user_command(serv, client, args), 0);
    check_reply(pipe_fd[0], "331 Username okay, need password.\r\n");

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    free(client);
    free(serv->poll_fds);
    free(serv->clients);
    free(serv);
}
