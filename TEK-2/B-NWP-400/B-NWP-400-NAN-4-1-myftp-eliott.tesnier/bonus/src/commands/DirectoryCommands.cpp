/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** DirectoryCommands
*/

#include "../Client.hpp"

void Client::mkdir(std::string arg)
{
    if (arg.empty()) {
        printError("Usage: mkdir <directory>");
        return;
    }

    execCommand("MKD " + arg);
}

void Client::rmdir(std::string arg)
{
    if (arg.empty()) {
        printError("Usage: rmdir <directory>");
        return;
    }

    execCommand("RMD " + arg);
}
