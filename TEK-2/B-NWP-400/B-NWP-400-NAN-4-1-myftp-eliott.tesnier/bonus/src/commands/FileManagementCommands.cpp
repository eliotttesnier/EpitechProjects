/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** FileManagementCommands
*/

#include "../Client.hpp"

void Client::mv(std::string arg)
{
    if (arg.empty()) {
        printError("Usage: mv <source> <destination>");
        return;
    }

    std::string source = arg.substr(0, arg.find_first_of(' '));
    std::string destination = arg.substr(arg.find_last_of(' ') + 1);

    if (source.empty() || destination.empty() || source == destination) {
        printError("Usage: mv <source> <destination>");
        return;
    }
    execCommand("RNFR " + source);
    execCommand("RNTO " + destination);
}

void Client::cp(std::string arg)
{
    if (arg.empty()) {
        printError("Usage: cp <source> <destination>");
        return;
    }

    std::string source = arg.substr(0, arg.find_first_of(' '));
    std::string destination = arg.substr(arg.find_last_of(' ') + 1);

    if (source.empty() || destination.empty() || source == destination) {
        printError("Usage: cp <source> <destination>");
        return;
    }

    execCommand("CPFR " + source);
    execCommand("CPTO " + destination);
}

void Client::rm(std::string arg)
{
    execCommand("DELE " + arg);
}
