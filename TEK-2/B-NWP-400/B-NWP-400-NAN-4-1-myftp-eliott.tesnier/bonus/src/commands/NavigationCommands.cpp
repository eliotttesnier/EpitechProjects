/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** NavigationCommands
*/


#include "../Client.hpp"

void Client::cd(std::string arg)
{
    execCommand("CWD " + arg);
}

void Client::pwd(std::string arg)
{
    (void)arg;
    execCommand("PWD");
}

void Client::cdup(std::string arg)
{
    (void)arg;
    execCommand("CDUP");
}
