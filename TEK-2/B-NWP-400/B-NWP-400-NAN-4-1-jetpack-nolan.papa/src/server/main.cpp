/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** main
*/

#include <unistd.h>

#include <string>
#include <iostream>
#include <vector>

#include "Parser.hpp"
#include "Game.hpp"

struct ServerArgs {
    int port;
    std::string mapPath;
    bool debug;
};

void displayUsage()
{
    std::cout << "USAGE: ./jetpack_server -p <port> -m <map> [-d]" << std::endl;
    std::cout << "\t-p <port>\tport to listen on" << std::endl;
    std::cout << "\t-m <map>\tpath to map file" << std::endl;
    std::cout << "\t-d\t\tenable debug mode" << std::endl;
}

ServerArgs parseArgs(int ac, char **av)
{
    ServerArgs args = {-1, "", false};
    int opt;

    while ((opt = getopt(ac, av, "p:m:d")) != -1) {
        switch (opt) {
            case 'p':
                try {
                    args.port = std::stoi(optarg);
                } catch (const std::exception &e) {
                    std::cerr << "Invalid port: " << optarg << std::endl;
                    displayUsage();
                    exit(84);
                }
                break;
            case 'm':
                args.mapPath = optarg;
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

void validateArgs(const ServerArgs &args)
{
    if (args.port == -1 || args.mapPath.empty()) {
        std::cerr << "Missing required arguments" << std::endl;
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

    ServerArgs args = parseArgs(ac, av);
    validateArgs(args);

    if (args.debug)
        std::cout << "\033[32m[DEBUG] \033[0m" << "Debug mode enabled" << std::endl;

    std::vector<std::vector<std::shared_ptr<IEntity>>> map;

    try {
        Parser parser(args.mapPath);
        map = parser.getMap();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    try {
        Game game(map, args.port, args.debug);
        game.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
