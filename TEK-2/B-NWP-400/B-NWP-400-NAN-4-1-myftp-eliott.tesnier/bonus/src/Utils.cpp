/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** Utils
*/

#include "Client.hpp"
#include "Colors.hpp"

void Client::printResponse(std::string response)
{
    if (response.empty())
        return;

    std::string codeColor = Colors::YELLOW;

    if (response.at(0) == '5') {
        codeColor = Colors::RED;
    }
    std::cout << codeColor << response.substr(0, 3) << Colors::BLUE << response.substr(3) << Colors::RESET;
}

void Client::printError(std::string error)
{
    std::cerr << Colors::RED << "Error: " << error << Colors::RESET << std::endl;
}
