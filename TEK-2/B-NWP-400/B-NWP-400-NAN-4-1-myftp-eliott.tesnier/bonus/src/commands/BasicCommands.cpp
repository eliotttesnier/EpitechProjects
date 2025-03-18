/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** BasicCommands
*/

#include "../Client.hpp"

void Client::noop(std::string arg)
{
    (void)arg;
    execCommand("NOOP");
}

void Client::quit(std::string arg)
{
    (void)arg;
    execCommand("QUIT");
    closeSocket();
    exit(0);
}
