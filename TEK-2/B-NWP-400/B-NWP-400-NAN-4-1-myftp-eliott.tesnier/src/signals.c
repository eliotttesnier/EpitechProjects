/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** signals
*/

#include "myftp.h"
#include <sys/wait.h>

static void handle_signal(int sig)
{
    if (sig == SIGCHLD)
        return;
    exit(0);
}

int setup_signal_handlers(void)
{
    struct sigaction sa;

    sa.sa_handler = handle_signal;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) == -1 ||
        sigaction(SIGTERM, &sa, NULL) == -1 ||
        sigaction(SIGCHLD, &sa, NULL) == -1) {
        return error("Failed to setup signal handlers");
    }
    return 0;
}

static void notify_transfer_status(client_t *client, int status)
{
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        send_reply(client, RPL_DATA_CONNECTION_CLOSE, "Transfer complete.");
    } else {
        send_reply(client, RPL_ERROR, "Transfer failed.");
    }
}

static bool handle_client_transfer(server_t *serv, pid_t pid, int status)
{
    for (int i = 0; i < serv->nb_clients; i++) {
        if (serv->clients[i].data_pid == pid) {
            serv->clients[i].data_pid = -1;
            notify_transfer_status(&serv->clients[i], status);
            return true;
        }
    }
    return false;
}

void handle_child_signal(server_t *serv)
{
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);

    while (pid > 0) {
        handle_client_transfer(serv, pid, status);
        pid = waitpid(-1, &status, WNOHANG);
    }
}
