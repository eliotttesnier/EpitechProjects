/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** Parser
*/

#include <string>
#include <utility>
#include <memory>
#include <vector>

#include "Parser.hpp"
#include "Error.hpp"
#include "entities/VoidEntity.hpp"
#include "entities/CoinEntity.hpp"
#include "entities/ElectricEntity.hpp"

/**
 * @brief Initializes the parser with the map file path.
 *
 * @param mapPath The path to the map file.
 */
Parser::Parser(std::string mapPath)
{
    _mapPath = mapPath;

    std::ifstream file(_mapPath);
    std::string line;
    int lineCount = 0;
    int lineLength = -1;

    validateMapFile(file);
    while (std::getline(file, line)) {
        line = line.substr(0, line.find('\n'));
        lineCount++;

        if (lineLength == -1)
            lineLength = line.length();
        else if (line.length() != static_cast<size_t>(lineLength))
            throw InvalidMap("Invalid map: inconsistent line lengths");

        validateMapCharacters(line);

        std::vector<std::shared_ptr<IEntity>> row;
        for (std::size_t i = 0; i < line.length(); i++) {
            row.emplace_back(createEntity(line[i], i, lineCount - 1));
        }
        _map.push_back(row);
    }

    validateMapDimensions(lineCount, lineLength);
    file.close();
}

/**
 * @brief Destructor for the Parser class.
 */
Parser::~Parser()
{
    for (auto &row : _map) {
        for (auto &entity : row) {
            entity.reset();
        }
        row.clear();
        row.shrink_to_fit();
    }
    _map.clear();
    _map.shrink_to_fit();
}

/**
 * @brief Validates if the map file can be opened successfully.
 *
 * @param file The input file stream representing the map file.
 *
 * @throw an exception if the file cannot be opened.
 */
void Parser::validateMapFile(std::ifstream &file)
{
    if (!file.is_open())
        throw InvalidMap("Cannot open map file: " + _mapPath);
}

/**
 * @brief Validates the dimensions of the map to ensure it matches expected parameters.
 *
 * @param lineCount The number of lines in the map.
 * @param lineLength The length of a single line in the map.
 *
 * @throw an exception if the map does not meet the expected size or if the lines have inconsistent lengths.
 */
void Parser::validateMapDimensions(int lineCount, int lineLength)
{
    if (lineCount != MAP_SIZE)
        throw InvalidMap(
            "Invalid map dimensions: expected " +
                std::to_string(MAP_SIZE) +
                " lines, got " +
                std::to_string(lineCount)
        );

    if (lineLength <= 0)
        throw InvalidMap("Invalid map dimensions: empty map");
}

/**
 * @brief Validates the characters in a given line of the map.
 *
 * @param line A single line from the map file to check.
 *
 * @throw an exception if any character in the line is invalid (not one of the allowed characters).
 */
void Parser::validateMapCharacters(const std::string &line)
{
    if (line.empty())
        throw InvalidMap("Invalid map: empty line detected");

    for (char c : line) {
        if (c != VOID_CHAR && c != COIN_CHAR && c != ELECTRIC_CHAR)
            throw InvalidMap("Invalid map character detected: '" + std::string(1, c) + "'");
    }
}

/**
 * @brief Creates an entity based on the character from the map.
 *
 * Depending on the character ('V' for Void, 'C' for Coin, 'E' for Electric), a corresponding entity is created.
 *
 * @param c The character from the map that determines the type of entity to create.
 * @param x The x-coordinate of the entity on the map.
 * @param y The y-coordinate of the entity on the map.
 * @return A shared pointer to the created entity.
 */
std::shared_ptr<IEntity> Parser::createEntity(char c, int x, int y)
{
    switch (c) {
        case VOID_CHAR:
            return std::make_shared<VoidEntity>(std::pair(x, y));
        case COIN_CHAR:
            return std::make_shared<CoinEntity>(std::pair(x, y));
        case ELECTRIC_CHAR:
            return std::make_shared<ElectricEntity>(std::pair(x, y));
        default:
            return std::make_shared<VoidEntity>(std::pair(x, y));
    }
}

/**
 * @brief Gets the map.
 *
 * @return A 2D vector of shared pointers to `IEntity` representing the parsed map.
 */
std::vector<std::vector<std::shared_ptr<IEntity>>> Parser::getMap() const
{
    return _map;
}
