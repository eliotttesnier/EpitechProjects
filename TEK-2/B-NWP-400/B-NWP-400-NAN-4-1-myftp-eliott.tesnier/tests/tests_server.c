/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** tests_error_cases
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "myftp.h"

void redirect_all_std(void);

// No arguments
Test(myftp, no_arguments, .init = redirect_all_std)
{
    int ac = 1;
    char *av[] = {"./myftp", NULL};

    cr_assert_eq(myftp(ac, av), 84);
    cr_assert_stderr_eq_str("Usage: ./myftp port path\n");
}

// Not enough arguments
Test(myftp, not_enough_arguments, .init = redirect_all_std)
{
    int ac = 2;
    char *av[] = {"./myftp", "21", NULL};

    cr_assert_eq(myftp(ac, av), 84);
    cr_assert_stderr_eq_str("Usage: ./myftp port path\n");
}

// Too many arguments
Test(myftp, too_many_arguments, .init = redirect_all_std)
{
    int ac = 4;
    char *av[] = {"./myftp", "21", "/tmp", "extra", NULL};

    cr_assert_eq(myftp(ac, av), 84);
    cr_assert_stderr_eq_str("Usage: ./myftp port path\n");
}

// Invalid port
Test(myftp, invalid_port, .init = redirect_all_std)
{
    int ac = 3;
    char *av[] = {"./myftp", "abc", "/tmp", NULL};

    cr_assert_eq(myftp(ac, av), 84);
    cr_assert_stderr_eq_str("Invalid port number\n");
}

// Too long path
Test(myftp, too_long_path, .init = redirect_all_std)
{
    char path[1025] = {0};

    for (int i = 0; i < 1024; i++)
        path[i] = 'a';
    int ac = 3;
    char *av[] = {"./myftp", "21", path, NULL};

    cr_assert_eq(myftp(ac, av), 84);
    cr_assert_stderr_eq_str("Path is too long\n");
}

// Invalid path
Test(myftp, invalid_path, .init = redirect_all_std)
{
    int ac = 3;
    char *av[] = {"./myftp", "21", "/tmp/does_not_exist", NULL};

    cr_assert_eq(myftp(ac, av), 84);
    cr_assert_stderr_eq_str("Invalid root path\nFailed to initialize server\n");
}

// Clear server
Test(clear_server, clear_server, .init = redirect_all_std)
{
    server_t server = {0};

    server.socket_fd = 42;
    server.poll_fds = malloc(sizeof(struct pollfd) * 2);
    server.clients = malloc(sizeof(client_t) * 2);
    clear_server(&server);
    cr_assert_eq(server.socket_fd, 42);
}
