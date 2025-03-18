/*
** EPITECH PROJECT, 2024
** NTS
** File description:
** Parser
*/

#include "Parser.hpp"
#include "Error.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

// Constructor

/**
 * @brief Constructor for the Parser class.
 */
Parser::Parser()
{
    _ind = 0;

    // Special components
    _validComponents.push_back(std::make_pair("input", 1));
    _validComponents.push_back(std::make_pair("output", 1));
    _validComponents.push_back(std::make_pair("true", 1));
    _validComponents.push_back(std::make_pair("false", 1));
    _validComponents.push_back(std::make_pair("clock", 1));

    // Elementary components
    _validComponents.push_back(std::make_pair("and", 3));
    _validComponents.push_back(std::make_pair("or", 3));
    _validComponents.push_back(std::make_pair("xor", 3));
    _validComponents.push_back(std::make_pair("not", 2));

    // Gates components
    _validComponents.push_back(std::make_pair("4001", 14));
    _validComponents.push_back(std::make_pair("4011", 14));
    _validComponents.push_back(std::make_pair("4030", 14));
    _validComponents.push_back(std::make_pair("4069", 14));
    _validComponents.push_back(std::make_pair("4071", 14));
    _validComponents.push_back(std::make_pair("4081", 14));

    // Advanced components
    _validComponents.push_back(std::make_pair("4008", 16));
    _validComponents.push_back(std::make_pair("4013", 14));
    _validComponents.push_back(std::make_pair("4017", 15));
    _validComponents.push_back(std::make_pair("4040", 16));
    _validComponents.push_back(std::make_pair("4094", 16));
    _validComponents.push_back(std::make_pair("4512", 16));
    _validComponents.push_back(std::make_pair("4514", 24));
    _validComponents.push_back(std::make_pair("4801", 24));
    _validComponents.push_back(std::make_pair("2716", 24));
    _validComponents.push_back(std::make_pair("logger", 10));
}

/**
 * @brief Destructor for the Parser class.
 */
Parser::~Parser()
{
}

// Getters
/**
 * @brief Getter for the components attribute.
 *
 * @return const std::vector<std::pair<std::string, std::string>>& The components attribute.
 */
const std::vector<std::pair<std::string, std::string>> &Parser::getComponents() const
{
    return _components;
}

/**
 * @brief Getter for the links attribute.
 *
 * @return const std::vector<std::vector<std::string>>& The links attribute.
 */
const std::vector<std::vector<std::string>> &Parser::getLinks() const
{
    return _links;
}

// Member functions
/**
 * @brief Check if the file can be opened and if it has the right extension.
 *
 * @param filename The name of the file to check.
 */
void Parser::checkFile(const std::string &filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
        throw nts::InvalidFile("Error: could not open file.");
    if (filename.substr(filename.find_last_of(".") + 1) != "nts")
        throw nts::InvalidFile("Error: invalid file extension.");

    getFileContent(file);
    file.close();
}

/**
 * @brief Parse the file and store its content in the fileContent attribute.
 *
 * @param filename The name of the file to parse.
 */
void Parser::parseFile()
{
    parseChipsets();
    parseLinks();
}

/**
 * @brief Set the components of the circuit.
 *
 * @param circuit The circuit to set the components to.
 */
void Parser::setComponents(Circuit &circuit, Factory &factory)
{
    for (const auto &component : _components) {
        circuit.addComponent(component.first, component.second, factory);
    }
}

/**
 * @brief Set the links of the circuit.
 *
 * @param circuit The circuit to set the links to.
 */
void Parser::setLinks(Circuit &circuit)
{
    for (const auto &link : _links) {
        circuit.linkComponents(link[0], std::stoi(link[1]), link[2], std::stoi(link[3]));
    }
}

// Private functions
/**
 * @brief Check if a type is valid.
 *
 * @param type The type to check.
 *
 * @return bool if type is valid
 */
bool Parser::isTypeValid(const std::string &type)
{
    for (const auto &component : _validComponents) {
        if (component.first == type)
            return true;
    }
    return false;
}

/**
 * @brief Check if a name is valid.
 *
 * @param name The name to check.
 *
 * @return bool if name is valid
 */
bool Parser::isNameValid(const std::string &name)
{
    for (const auto &component : _components) {
        if (component.first == name)
            return false;
    }
    return true;
}

/**
 * @brief Check if a pin is valid.
 *
 * @param name The name of the component.
 * @param pin The pin to check.
 *
 * @return bool if pin is valid
 */
bool Parser::isValidPin(const std::string &name, const std::string &pin)
{
    auto it = std::find_if(_components.begin(), _components.end(),
        [&name](const auto &pair) { return pair.first == name; });

    try {
        int pinNum = std::stoi(pin);
        if (pinNum <= 0)
            return false;

        std::string type = it->second;
        auto validComp = std::find_if(_validComponents.begin(), _validComponents.end(),
            [&type](const auto &pair) { return pair.first == type; });

        return pinNum <= static_cast<int>(validComp->second);
    } catch (const std::invalid_argument&) {
        return false;
    } catch (const std::out_of_range&) {
        return false;
    }
}

/**
 * @brief Get the content of the file (without comments) and store it in the fileContent attribute.
 *
 * @param file The file to get the content from.
 */
void Parser::getFileContent(std::ifstream &file)
{
    std::string line;
    std::string formatted;

    while (!file.eof())
    {
        std::getline(file, line);

        if (line.empty())
            continue;
        if (line[line.find_first_not_of(" \t")] == '#')
            continue;
        if (line.find_first_not_of(" \t") == std::string::npos)
            continue;
        line = line.substr(0, line.find('#'));
        formatted = formatLine(line);
        _fileContent.push_back(formatted);
    }
}

/**
 * @brief Format a line by removing the comments and the extra spaces.
 *
 * @param line The line to format.
 *
 * @return std::string The formatted line.
 */
std::string Parser::formatLine(const std::string &line)
{
    std::string formatted;
    bool inWord = false;

    for (char c : line) {
        if (c != ' ' && c != '\t') {
            formatted += c;
            inWord = true;
        } else if (inWord) {
            formatted += ' ';
            inWord = false;
        }
    }
    if (!formatted.empty() && formatted.back() == ' ')
        formatted.pop_back();
    return formatted;}

/**
 * @brief Parse the chipsets of the file.
 */
void Parser::parseChipsets()
{
    int size = _fileContent.size();
    std::string type;
    std::string name;

    if (_fileContent.empty())
        throw nts::InvalidFile("Error: empty file.");
    if (_fileContent[0] != ".chipsets:")
        throw nts::InvalidFile("Error: missing \".chipsets:\" statement.");

    for (_ind = 1; _ind < size; _ind++) {
        if (_fileContent[_ind] == ".links:")
            break;
        if (_fileContent[_ind] == ".chipsets:")
            throw nts::InvalidFile("Error: multiple \".chipsets:\" statements.");

        if (_fileContent[_ind].find(' ') == std::string::npos)
            throw nts::InvalidFile("Error: invalid component format.");

        type = _fileContent[_ind].substr(0, _fileContent[_ind].find(' '));
        name = _fileContent[_ind].substr(_fileContent[_ind].find(' ') + 1);

        if (!isTypeValid(type))
            throw nts::InvalidFile("Error: unknown type: \"" + type + "\".");
        if (!isNameValid(name))
            throw nts::InvalidFile("Error: multiple components with the same name: \"" + name + "\".");

        _components.push_back(std::make_pair(name, type));
    }
    if (_components.empty())
        throw nts::InvalidFile("Error: no components found.");
}

/**
 * @brief Parse the links of the file.
 */
void Parser::parseLinks()
{
    int size = _fileContent.size();
    std::string name1;
    std::string pin1;
    std::string name2;
    std::string pin2;

    if (_ind == size || _fileContent[_ind] != ".links:")
        throw nts::InvalidFile("Error: missing \".links:\" statement.");

    for (_ind++; _ind < size; _ind++) {
        if (_fileContent[_ind] == ".links:")
            throw nts::InvalidFile("Error: multiple \".links:\" statements.");

        if (_fileContent[_ind].find(' ') == std::string::npos)
            throw nts::InvalidFile("Error: invalid link format.");

        std::string line1 = _fileContent[_ind].substr(0, _fileContent[_ind].find(' '));
        std::string line2 = _fileContent[_ind].substr(_fileContent[_ind].find(' ') + 1);

        if (line1.find(':') == std::string::npos || line2.find(':') == std::string::npos)
            throw nts::InvalidFile("Error: invalid link format (missing colon).");

        name1 = line1.substr(0, line1.find(':'));
        pin1 = line1.substr(line1.find(':') + 1);
        name2 = line2.substr(0, line2.find(':'));
        pin2 = line2.substr(line2.find(':') + 1);

        if (std::none_of(_components.begin(), _components.end(),
            [&name1](const auto &pair) { return pair.first == name1; }))
            throw nts::InvalidFile("Error: unknown component: \"" + name1 + "\".");
        if (std::none_of(_components.begin(), _components.end(),
            [&name2](const auto &pair) { return pair.first == name2; }))
            throw nts::InvalidFile("Error: unknown component: \"" + name2 + "\".");

        if (!isValidPin(name1, pin1))
            throw nts::InvalidFile("Error: invalid pin: \"" + pin1 + "\" for component: \"" + name1 + "\".");
        if (!isValidPin(name2, pin2))
            throw nts::InvalidFile("Error: invalid pin: \"" + pin2 + "\" for component: \"" + name2 + "\".");

        _links.push_back({name1, pin1, name2, pin2});
    }
}
