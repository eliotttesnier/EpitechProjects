/*
** EPITECH PROJECT, 2024
** NTS
** File description:
** Simulator
*/

#pragma once

#include <string>
#include <memory>
#include "Parser.hpp"
#include "Circuit.hpp"
#include "Factory.hpp"

class Simulator {
    public:
        Simulator(const std::string &filename);
        ~Simulator();

        // Getters
        Circuit &getCircuit() const;
        int getReturnCode() const;

        // Member functions
        void initCircuit(const std::string &filename);
        void runShell();

        // Shell functions
        void parseInput(const std::string &input);
        void userSetInput(const std::string &input);
        void userExit();
        void userDisplay();
        void userSimulate();
        void userLoop();

    private:
        std::string _filename;

        std::unique_ptr<Circuit> _circuit;
        Parser _parser;
        Factory _factory;

        bool _exit;
        bool _loop;

        int _returnCode;
};
