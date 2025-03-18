/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** server
*/

#include "myftp.h"

static int check_root_dir(char *root_dir, server_t *serv)
{
    if (chdir(root_dir) != 0)
        return error("Invalid root path\n");
    if (getcwd(serv->complete_root_dir, PATH_MAX_LEN) == NULL)
        return error("Failed to get current working directory\n");
    serv->root_dir[0] = '/';
    serv->root_dir[1] = '\0';
    return 0;
}

int init_server(server_t *serv, int port, char *root_dir)
{
    if (check_root_dir(root_dir, serv) != 0)
        return 84;
    serv->socket_fd = setup_server_socket(port);
    if (serv->socket_fd < 0)
        return 84;
    serv->port = port;
    if (init_poll_structures(serv) < 0)
        return 84;
    return 0;
}

void clear_server(server_t *serv)
{
    if (serv->socket_fd >= 0)
        close(serv->socket_fd);
    free(serv->poll_fds);
    free(serv->clients);
}

int valid_args(int ac, char **av)
{
    if (ac != 3)
        return error("Usage: ./myftp port path\n");
    if (atoi(av[1]) <= 0)
        return error("Invalid port number\n");
    if (strlen(av[2]) >= PATH_MAX_LEN)
        return error("Path is too long\n");
    return 0;
}

int myftp(int ac, char **av)
{
    server_t server = {0};
    int port;

    if (valid_args(ac, av) != 0)
        return 84;
    port = atoi(av[1]);
    if (setup_signal_handlers() != 0)
        return error("Failed to setup signal handlers\n");
    if (init_server(&server, port, av[2]) != 0) {
        clear_server(&server);
        return error("Failed to initialize server\n");
    }
    printf("Server started on port %d\n", port);
    run_server(&server);
    clear_server(&server);
    return 0;
}
