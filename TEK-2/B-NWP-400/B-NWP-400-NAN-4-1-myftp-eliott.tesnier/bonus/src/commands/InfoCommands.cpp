/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** InfoCommands
*/

#include "../Client.hpp"
#include "../Colors.hpp"
#include <regex>
#include <fstream>

void Client::help(std::string arg)
{
    (void)arg;
    std::ifstream file("help.txt");

    if (!file.is_open()) {
        printError("help file not found");
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        line = std::regex_replace(line, std::regex("GREEN "), Colors::GREEN);
        line = std::regex_replace(line, std::regex("YELLOW "), Colors::YELLOW);
        line = std::regex_replace(line, std::regex("BLUE "), Colors::BLUE);
        line = std::regex_replace(line, std::regex("RESET "), Colors::RESET);
        std::cout << line << std::endl;
    }
    file.close();
}

void Client::who(std::string arg)
{
    (void)arg;
    std::cout << Colors::YELLOW << "Username: " << Colors::RESET << _username << std::endl;
}


void Client::size(std::string arg)
{
    if (arg.empty()) {
        printError("Usage: size <filename>");
        return;
    }

    execCommand("SIZE " + arg);
}

void Client::mdtm(std::string arg)
{
    if (arg.empty()) {
        printError("Usage: mdtm <filename>");
        return;
    }

    execCommand("MDTM " + arg);
}
