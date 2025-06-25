/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** main
*/

#include <unistd.h>

#include <string>
#include <iostream>

#include "Display.hpp"

struct ClientArgs {
    std::string host;
    int port;
    bool debug;
};

void displayUsage()
{
    std::cout << "USAGE: ./jetpack_client -h <ip> -p <port> [-d]" << std::endl;
    std::cout << "\t-h <ip>\t\tip address to connect to" << std::endl;
    std::cout << "\t-p <port>\tport to connect to" << std::endl;
    std::cout << "\t-d\t\tenable debug mode" << std::endl;
}

ClientArgs parseArgs(int ac, char **av)
{
    ClientArgs args = {"", -1, false};
    int opt;

    while ((opt = getopt(ac, av, "h:p:d")) != -1) {
        switch (opt) {
            case 'h':
                args.host = optarg;
                break;
            case 'p':
                try {
                    args.port = std::stoi(optarg);
                } catch (const std::exception &e) {
                    std::cerr << "Invalid port: " << optarg << std::endl;
                    displayUsage();
                    exit(84);
                }
                break;
            case 'd':
                args.debug = true;
                break;
            default:
                displayUsage();
                exit(84);
        }
    }

    return args;
}

void validateArgs(const ClientArgs &args)
{
    if (args.host.empty() || args.port == -1) {
        std::cerr << "Missing required arguments" << std::endl;
        displayUsage();
        exit(84);
    }

    if (args.host.find_first_not_of("0123456789.") != std::string::npos) {
        std::cerr << "Invalid IP address: " << args.host << std::endl;
        displayUsage();
        exit(84);
    }

    if (args.port <= 0) {
        std::cerr << "Port must be positive" << std::endl;
        displayUsage();
        exit(84);
    }
}

int main(int ac, char **av)
{
    if (ac < 5) {
        displayUsage();
        return 84;
    }

    ClientArgs args = parseArgs(ac, av);
    validateArgs(args);

    if (args.debug)
        std::cout << "\033[32m[DEBUG] \033[0m" << "Debug mode enabled" << std::endl;

    Display display(args.host, std::to_string(args.port), args.debug);
    display.run();
    return 0;
}
