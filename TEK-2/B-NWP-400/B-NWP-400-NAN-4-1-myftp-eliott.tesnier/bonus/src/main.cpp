/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** main
*/

#include "Client.hpp"

int main(int ac, char **av)
{
    if (ac != 3) {
        std::cerr << "Usage: ./myftp [ip] [port]" << std::endl;
        return 84;
    }

    Client client(av[1], av[2]);
    client.run();
    return 0;
}
