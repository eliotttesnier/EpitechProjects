/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** Parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

#include "entities/IEntity.hpp"

#define MAP_SIZE 10
#define VOID_CHAR ' '
#define COIN_CHAR '*'
#define ELECTRIC_CHAR '#'

class Parser {
    private:
        std::string _mapPath;

        void validateMapFile(std::ifstream &file);
        void validateMapDimensions(int lineCount, int lineLength);
        void validateMapCharacters(const std::string &line);
        std::shared_ptr<IEntity> createEntity(char c, int x, int y);

        std::vector<std::vector<std::shared_ptr<IEntity>>> _map;

    public:
        Parser(std::string mapPath);
        ~Parser();

        std::vector<std::vector<std::shared_ptr<IEntity>>> getMap() const;
};

#endif /* !PARSER_HPP_ */
