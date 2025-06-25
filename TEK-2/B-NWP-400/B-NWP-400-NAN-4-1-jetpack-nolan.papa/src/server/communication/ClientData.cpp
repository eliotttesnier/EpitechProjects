/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** ClientData
*/

#include <string>
#include <vector>

#include "ClientData.hpp"

/**
 * @brief Checks if the client is currently flying.
 * @return True if the client is flying, false otherwise.
 */
bool ClientData::getIsFlying() const
{
    return _isFlying;
}

/**
 * @brief Sets the flying status of the client.
 * @param isFlying A boolean indicating whether the client is flying.
 */
void ClientData::setIsFlying(bool isFlying)
{
    _isFlying = isFlying;
}

/**
 * @brief Retrieves the name of the client.
 * @return A string containing the client's name.
 */
std::string ClientData::getName() const
{
    return _name;
}

/**
 * @brief Sets the name of the client.
 * @param name A string representing the client's name.
 */
void ClientData::setName(std::string name)
{
    _name = name;
}

/**
 * @brief Retrieves the list of inputs associated with the client.
 * @return A vector containing the client's inputs.
 */
std::vector<ClientInput_t> ClientData::getInputs() const
{
    return _inputs;
}

/**
 * @brief Sets the list of inputs for the client.
 * @param inputs A vector of ClientInput_t representing the client's inputs.
 */
void ClientData::setInputs(std::vector<ClientInput_t> inputs)
{
    _inputs = inputs;
}

/**
 * @brief Adds a single input to the client's input history.
 * @param input A ClientInput_t object representing the input to add.
 */
void ClientData::addInput(ClientInput_t input)
{
    _inputs.push_back(input);
}

/**
 * @brief Retrieves the ID of the client.
 * @return An integer representing the client's ID.
 */
int ClientData::getId() const
{
    return _id;
}

/**
 * @brief Sets the ID of the client.
 * @param id An integer representing the client's ID.
 */
void ClientData::setId(int id)
{
    _id = id;
}
