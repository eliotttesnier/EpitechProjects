/*
** EPITECH PROJECT, 2024
** NTS
** File description:
** main
*/

#include "Simulator.hpp"
#include <iostream>

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage: ./nanotekspice [filename]" << std::endl;
        return 84;
    }

    Simulator simulator(av[1]);

    simulator.runShell();
    return simulator.getReturnCode();
}
