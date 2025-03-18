/*
** EPITECH PROJECT, 2024
** NTS
** File description:
** Parser
*/

#pragma once

#include "Circuit.hpp"
#include "Factory.hpp"
#include <vector>

class Parser {
    public:
        // Constructor
        Parser();
        ~Parser();

        // Getters
        const std::vector<std::pair<std::string, std::string>> &getComponents() const;
        const std::vector<std::vector<std::string>> &getLinks() const;

        // Member functions
        void checkFile(const std::string &filename);
        void parseFile();
        void setComponents(Circuit &circuit, Factory &factory);
        void setLinks(Circuit &circuit);

    private:
        std::vector<std::pair<std::string, std::size_t>> _validComponents;
        bool isTypeValid(const std::string &type);
        bool isNameValid(const std::string &name);
        bool isValidPin(const std::string &name, const std::string &pin);

        std::vector<std::pair<std::string, std::string>> _components;
        std::vector<std::vector<std::string>> _links;
        std::vector<std::string> _fileContent;
        int _ind;

        void getFileContent(std::ifstream &file);
        std::string formatLine(const std::string &line);

        void parseChipsets();
        void parseLinks();
};
