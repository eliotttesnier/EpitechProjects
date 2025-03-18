/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** testes_dele
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
Test(dele_command, no_arguments)
{
    server_t *serv = create_server();
    client_t *client = create_client();
    char *args = NULL;
    int pipe_fd[2];

    setup_pipe(pipe_fd);
    client->control_fd = pipe_fd[1];

    cr_assert_eq(dele_command(serv, client, args), 0);
    check_reply(pipe_fd[0], "501 Missing path argument\r\n");

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    free(client);
    free(serv->poll_fds);
    free(serv->clients);
    free(serv);
}

// Invalid file
Test(dele_command, invalid_file)
{
    server_t *serv = create_server();
    client_t *client = create_client();
    char *args = "not_a_file";
    int pipe_fd[2];

    setup_pipe(pipe_fd);
    client->control_fd = pipe_fd[1];

    cr_assert_eq(dele_command(serv, client, args), 0);
    check_reply(pipe_fd[0], "550 Failed to delete file\r\n");

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    free(client);
    free(serv->poll_fds);
    free(serv->clients);
    free(serv);
}

// Valid file
Test(dele_command, valid_file)
{
    int file_fd = open("tests/tmp.txt", O_CREAT | O_RDWR, 0644);

    server_t *serv = create_server();
    client_t *client = create_client();
    char *args = "tests/tmp.txt";
    int pipe_fd[2];

    setup_pipe(pipe_fd);
    client->control_fd = pipe_fd[1];

    cr_assert_eq(dele_command(serv, client, args), 0);
    check_reply(pipe_fd[0], "250 File deleted\r\n");

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    free(client);
    free(serv->poll_fds);
    free(serv->clients);
    free(serv);
    close(file_fd);
    remove("tests/tmp.txt");
}

// Valid file root test
Test(dele_command, valid_file_root)
{
    int file_fd = open("tests/tmp2.txt", O_CREAT | O_RDWR, 0644);

    server_t *serv = create_server();
    client_t *client = create_client();
    char *args = "/tests/tmp2.txt";
    int pipe_fd[2];

    setup_pipe(pipe_fd);
    client->control_fd = pipe_fd[1];

    cr_assert_eq(dele_command(serv, client, args), 0);
    check_reply(pipe_fd[0], "250 File deleted\r\n");

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    free(client);
    free(serv->poll_fds);
    free(serv->clients);
    free(serv);
    close(file_fd);
    remove("tests/tmp2.txt");
}
