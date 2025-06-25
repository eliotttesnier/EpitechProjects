/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Communication
*/

#include <map>
#include <iostream>
#include <string>
#include <vector>

#include "Communication.hpp"

const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string BLUE = "\033[34m";
const std::string RESET = "\033[0m";

/**
 * @brief Constructs a Communication object.
 *
 * Initializes the server socket and sets up the file descriptors for client connections.
 */
Communication::Communication()
{
    _gameStarted = false;
    _serverSocket = -1;
    for (int i = 0; i < NB_CLIENTS; i += 1) {
        _fds[i].fd = -1;
        _fds[i].events = POLLIN;
    }
    _dataInfos = {
        {0, NONE},
        {sizeof(int), NONE},
        {sizeof(size_t), NONE},
        {sizeof(bool), NONE},
        {sizeof(double), NONE},
        {sizeof(float), NONE},
        {sizeof(uint16_t), NONE},
        {sizeof(player_t), NONE},
        {sizeof(char) * 20, CHANGE_NAME},
        {sizeof(coinsPos_t), NONE},
        {sizeof(obstacle_t), NONE},
        {0, NONE},
        {sizeof(int), NONE},
        {sizeof(bool), FLY},
        {0, NONE},
        {0, NONE},
        {sizeof(int), NONE},
        {sizeof(double), NONE},
        {0, NONE},
        {sizeof(int), NONE},
        {0, NONE},
    };
}

Communication::~Communication()
{
    for (int i = 0; i < NB_CLIENTS; i += 1) {
        if (_fds[i].fd != -1) {
            close(_fds[i].fd);
        }
    }
    _dataInfos.clear();
    _dataInfos.shrink_to_fit();
}

/**
 * @brief Counts the number of connected players.
 * 
 * Counts the number of players currently connected to the server by checking the file descriptors.
 * 
 * @return The number of connected players.
 */
int Communication::_getNbPlayers()
{
    int count = 0;
    for (int i = 0; i < NB_CLIENTS; i += 1) {
        if (_fds[i].fd != -1) {
            count += 1;
        }
    }
    return count;
}

/**
 * @brief Gets the game start status.
 *
 * Returns if the game has started or not.
 * 
 * @return the current game start status.
 */
bool Communication::getGameStarted()
{
    return _gameStarted;
}

/**
 * @brief Creates a header for the communication packet.
 *
 * Constructs a header based on the number of lists provided.
 *
 * @param nbLists The number of lists to include in the packet.
 * @return The constructed header as a 16-bit unsigned integer.
 */
uint16_t Communication::_createHeader(uint8_t nbLists)
{
    uint16_t header = 0;

    header |= 42;
    header <<= 6;
    header |= 42;
    header <<= 4;
    header |= nbLists;
    return header;
}

/**
 * @brief Creates a data header for the communication packet.
 *
 * Constructs a header based on the number of data items and their type.
 *
 * @param dataCount The number of data items to include in the packet.
 * @param dataType The type of data being sent.
 * @return The constructed data header as a 16-bit unsigned integer.
 */
uint16_t Communication::_createDataHeader(uint8_t dataCount, uint8_t dataType)
{
    uint16_t header = 0;

    header |= dataCount;
    header <<= 6;
    header |= dataType;
    return header;
}

/**
 * @brief Checks if the magic number in the packet is valid.
 *
 * Validates the magic number in the received packet to ensure it is correct.
 *
 * @param packet The received packet to check.
 * @return True if the magic number is valid, false otherwise.
 */
bool Communication::_checkMagicNb(std::vector<u_int8_t> packet)
{
    if (packet.size() < 2) {
        return false;
    }

    uint16_t expectedMagicNb = _createHeader(0);

    uint16_t receivedMagicNb = packet[0];
    receivedMagicNb <<= 8;
    receivedMagicNb |= packet[1];

    receivedMagicNb &= 0xFFF0;

    return receivedMagicNb == expectedMagicNb;
}

/**
 * @brief Checks if the packet is complete.
 *
 * Validates if the received packet is complete and can be processed.
 *
 * @param packet The received packet to check.
 * @return True if the packet is complete, false otherwise.
 */
bool Communication::_packetComplete(std::vector<u_int8_t> packet)
{
    size_t expectedSize = 0;

    if (packet.size() < expectedSize + 2) {
        return false;
    }

    uint16_t header = packet[0];
    header <<= 8;
    header |= packet[1];

    uint8_t nbLists = header & 0b00001111;

    expectedSize += 2;

    for (int i = 0; i < nbLists; i += 1) {
        if (packet.size() < expectedSize + 2) {
            return false;
        }

        uint16_t dataHeader = packet[expectedSize];
        dataHeader <<= 8;
        dataHeader |= packet[expectedSize + 1];

        uint8_t dataCount = dataHeader >> 6;
        uint8_t dataType = dataHeader & 0b111111;
        expectedSize += 2;

        if (packet.size() < expectedSize + dataCount * _dataInfos[dataType].dataSize) {
            return false;
        }

        expectedSize += dataCount * _dataInfos[dataType].dataSize;
    }
    return true;
}

/**
 * @brief Starts the server and binds it to the specified port.
 *
 * Initializes the server socket, binds it to the specified port, and starts listening for incoming connections.
 *
 * @param port The port number to bind the server to.
 * @return True if the server started successfully, false otherwise.
 */
bool Communication::startServer(int port)
{
    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverSocket < 0) {
        return false;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(_serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        close(_serverSocket);
        return false;
    }

    if (listen(_serverSocket, NB_CLIENTS) < 0) {
        close(_serverSocket);
        return false;
    }
    return true;
}

/**
 * @brief Accepts a new client connection.
 *
 * Waits for a new client to connect and returns a Player object representing the new client.
 *
 * @return A Player object representing the new client.
 */
Player Communication::getNewClient()
{
    struct pollfd serverFd;
    serverFd.fd = _serverSocket;
    serverFd.events = POLLIN;

    int ret = poll(&serverFd, 1, 0);
    if (ret < 0) {
        // Error occurred
        throw std::runtime_error("Error in poll");
    }
    if (ret == 0) {
        // No new client
        return Player("", -1);
    }
    if (serverFd.revents & POLLIN) {
        int clientSocket = accept(_serverSocket, nullptr, nullptr);
        if (clientSocket < 0) {
            // Error occurred
            throw std::runtime_error("Error accepting client");
        }
        for (int i = 0; i < NB_CLIENTS; i += 1) {
            if (_fds[i].fd == -1) {
                _fds[i].fd = clientSocket;
                _fds[i].events = POLLIN;

                if (_debug) {
                    std::cout << GREEN + "[DEBUG] " + RESET <<
                        "New client connected: " << clientSocket << std::endl;
                }

                _buffer[clientSocket] = std::vector<uint8_t>();

                uint16_t header = _createHeader(1);
                uint16_t dataHeader = _createDataHeader(2, 2);
                size_t playerId = clientSocket;
                size_t gameSpeed = 20;
                std::vector<uint8_t> packet(
                    sizeof(header) + sizeof(dataHeader) + sizeof(playerId) + sizeof(gameSpeed),
                    0
                );

                _writeToVector(packet, 0, header);
                _writeToVector(packet, sizeof(header), dataHeader);
                _writeToVector(packet, sizeof(header) + sizeof(dataHeader), playerId);
                _writeToVector(
                    packet,
                    sizeof(header) + sizeof(dataHeader) + sizeof(playerId),
                    gameSpeed
                );

                ssize_t bytesSent = write(clientSocket, packet.data(), packet.size());
                printDebugInfo(
                    "Sending welcome packet to socket (" + std::to_string(clientSocket) + ")",
                    {0},
                    true,
                    packet.size()
                );

                packet.clear();
                packet.shrink_to_fit();

                if (bytesSent <= 0) {
                    close(clientSocket);
                    _fds[i].fd = -1;
                    std::cerr << "Error sending data to client" << std::endl;
                    return Player("", -1);
                }

                return Player("Player" + std::to_string(i), clientSocket);
            }
        }
        std::cerr << "No available slots for new clients" << std::endl;
    }
    return Player("", -1);
}

/**
 * @brief Sends the start game signal to all connected clients.
 *
 * Constructs a packet containing the start game signal and sends it to all connected clients.
 */
void Communication::_sendStartToAllClients()
{
    uint16_t header = _createHeader(1);
    uint16_t dataHeader = _createDataHeader(1, 14);
    std::vector<uint8_t> packet(
        sizeof(header) + sizeof(dataHeader),
        0
    );

    _writeToVector(packet, 0, header);
    _writeToVector(packet, sizeof(header), dataHeader);

    for (int i = 0; i < NB_CLIENTS; i += 1) {
        if (_fds[i].fd == -1) {
            continue;
        }

        int clientSocket = _fds[i].fd;

        ssize_t bytesSent = write(clientSocket, packet.data(), packet.size());
        printDebugInfo(
            "Sending start game to socket (" + std::to_string(clientSocket) + ")",
            {14},
            true,
            packet.size()
        );

        if (bytesSent <= 0) {
            close(clientSocket);
            _fds[i].fd = -1;
            continue;
        }
    }
    packet.clear();
    packet.shrink_to_fit();
}

/**
 * @brief Sends the game end signal to all connected clients.
 *
 * Constructs a packet containing the game end signal and sends it to all connected clients.
 */
void Communication::sendGameEnd()
{
    uint16_t header = _createHeader(1);
    uint16_t dataHeader = _createDataHeader(1, 20);
    std::vector<uint8_t> packet(
        sizeof(header) + sizeof(dataHeader),
        0
    );

    _writeToVector(packet, 0, header);
    _writeToVector(packet, sizeof(header), dataHeader);

    for (int i = 0; i < NB_CLIENTS; i += 1) {
        if (_fds[i].fd == -1) {
            continue;
        }

        int clientSocket = _fds[i].fd;

        ssize_t bytesSent = write(clientSocket, packet.data(), packet.size());
        printDebugInfo(
            "Sending game end to socket (" + std::to_string(clientSocket) + ")",
            {20},
            true,
            packet.size()
        );

        if (bytesSent <= 0) {
            close(clientSocket);
            _fds[i].fd = -1;
            continue;
        }
    }
    packet.clear();
    packet.shrink_to_fit();
}

/**
 * @brief Sends the number of connected clients to a specific client.
 *
 * Constructs a packet containing the number of connected clients and sends it to the specified client.
 *
 * @param clientId The ID of the client to send the data to.
 */
void Communication::_sendNbClientsToClient(int clientId)
{
    uint16_t header = _createHeader(1);
    uint16_t dataHeader = _createDataHeader(1, 19);
    int nbClients = _getNbPlayers();
    std::vector<uint8_t> packet(
        sizeof(header) + sizeof(dataHeader) + sizeof(nbClients),
        0
    );

    _writeToVector(packet, 0, header);
    _writeToVector(packet, sizeof(header), dataHeader);
    _writeRawStructToVector(packet, sizeof(header) + sizeof(dataHeader), nbClients);

    ssize_t bytesSent = write(clientId, packet.data(), packet.size());
    printDebugInfo(
        "Sending number of clients to socket (" + std::to_string(clientId) + ")",
        {19},
        true,
        packet.size()
    );

    if (bytesSent <= 0) {
        std::cerr << "Error sending data to client" << std::endl;
    }
    packet.clear();
    packet.shrink_to_fit();
}

/**
 * @brief Fills the ClientData object with data from the received packet.
 *
 * Parses the received packet and extracts the relevant data to populate the ClientData object.
 *
 * @param packet The received packet containing client data.
 * @return A ClientData object populated with the extracted data.
 */
ClientData Communication::_fillClientData(int clientId)
{
    ClientData data;

    uint8_t dataListCount = _buffer[clientId][1] & 0b00001111;

    _buffer[clientId].erase(_buffer[clientId].begin(), _buffer[clientId].begin() + 2);

    for (uint8_t i = 0; i < dataListCount; i++) {
        uint16_t dataHeader = _buffer[clientId][0];
        dataHeader <<= 8;
        dataHeader |= _buffer[clientId][1];
        _buffer[clientId].erase(_buffer[clientId].begin(), _buffer[clientId].begin() + 2);

        uint8_t dataCount = dataHeader >> 6;
        uint8_t dataType = dataHeader & 0b111111;

        data.setId(clientId);

        for (uint8_t j = 0; j < dataCount; j++) {
            if (dataType == 8) {
                printDebugInfo(
                    "Received username from (" + std::to_string(clientId) + ")",
                    {8},
                    false,
                    _buffer[clientId].size()
                );
                _buffer[clientId].erase(
                    _buffer[clientId].begin(),
                    _buffer[clientId].begin() + 20
                );
                data.setName(
                    std::string(reinterpret_cast<char *>(_buffer[clientId].data()), 20)
                );
                data.addInput(CHANGE_NAME);
            } else if (dataType == 13) {
                printDebugInfo(
                    "Received player input from (" + std::to_string(clientId) + ")",
                    {13},
                    false,
                    _buffer[clientId].size()
                );
                _buffer[clientId].erase(
                    _buffer[clientId].begin(),
                    _buffer[clientId].begin() + 1
                );
                data.setIsFlying(_buffer[clientId][0] > 0);
                data.addInput(FLY);
            } else if (dataType == 14) {
                printDebugInfo(
                    "Received start game from (" + std::to_string(clientId) + ")",
                    {14},
                    false,
                    _buffer[clientId].size()
                );
                if (_getNbPlayers() >= MIN_CLIENTS) {
                    _gameStarted = true;
                    _sendStartToAllClients();
                }
            } else if (dataType == 18) {
                printDebugInfo(
                    "Received ask number of players from (" + std::to_string(clientId) + ")",
                    {18},
                    false,
                    _buffer[clientId].size()
                );
                _sendNbClientsToClient(clientId);
            }
        }
    }
    return data;
}

/**
 * @brief Retrieves the data from all connected clients.
 *
 * Polls the file descriptors for incoming data and processes the received packets.
 *
 * @return A vector of ClientData objects containing the data from each client.
 */
std::vector<ClientData> Communication::getClientsData()
{
    int ret = poll(_fds, NB_CLIENTS, 0);

    if (ret <= 0) {
        return {};
    }

    std::vector<ClientData> datas(NB_CLIENTS);

    for (int i = 0; i < NB_CLIENTS; i += 1) {
        if (!_fds[i].revents & POLLIN) {
            continue;
        }
        if (_fds[i].fd == -1) {
            continue;
        }
        int clientSocket = _fds[i].fd;

        std::vector<uint8_t> packet(BUFFER_SIZE);
        ssize_t bytesRead = read(clientSocket, packet.data(), BUFFER_SIZE);

        if (bytesRead <= 0) {
            close(clientSocket);
            _fds[i].fd = -1;
            _buffer.erase(clientSocket);
            continue;
        }

        _buffer[clientSocket].insert(
            _buffer[clientSocket].end(),
            packet.begin(),
            packet.begin() + bytesRead
        );

        if (!_checkMagicNb(_buffer[clientSocket]))
            continue;

        if (!_packetComplete(_buffer[clientSocket])) {
            std::cout << "Packet not complete" << std::endl;
            continue;
        }

        datas.push_back(_fillClientData(clientSocket));
    }

    return datas;
}

/**
 * @brief Sends the game state to all connected clients.
 *
 * Constructs a packet containing the game state information and sends it to all connected clients.
 *
 * @param gameState The current game state to be sent.
 */
void Communication::sendGameState(GameState gameState)
{
    std::vector<player_t> players = gameState.getPlayers();
    std::vector<obstacle_t> electricity = gameState.getElectricity();

    uint16_t header = _createHeader(3);
    uint16_t playerHeader = _createDataHeader(players.size(), 7);
    uint16_t electricityHeader = _createDataHeader(electricity.size(), 10);

    for (int i = 0; i < NB_CLIENTS; i += 1) {
        if (_fds[i].fd == -1) {
            continue;
        }

        size_t nbCoins = gameState.getPlayerNotCollectedCoins(_fds[i].fd).size();
        uint16_t coinHeader = _createDataHeader(nbCoins, 9);

        std::vector<uint8_t> packet(
            sizeof(header) + sizeof(playerHeader) + players.size() * sizeof(player_t) +
            sizeof(coinHeader) + nbCoins * sizeof(coinsPos_t) +
            sizeof(electricityHeader) + electricity.size() * sizeof(obstacle_t),
            0
        );

        size_t offset = 0;

        _writeToVector(packet, offset, header);
        offset += sizeof(header);

        _writeToVector(packet, offset, playerHeader);
        offset += sizeof(playerHeader);

        for (auto &player : players) {
            _writeRawStructToVector(packet, offset, player);
            offset += sizeof(player_t);
        }

        _writeToVector(packet, offset, electricityHeader);
        offset += sizeof(electricityHeader);

        for (auto &obstacle : electricity) {
            _writeRawStructToVector(packet, offset, obstacle);
            offset += sizeof(obstacle_t);
        }

        _writeToVector(packet, offset, coinHeader);
        offset += sizeof(coinHeader);

        for (auto &coin : gameState.getPlayerNotCollectedCoins(_fds[i].fd)) {
            _writeRawStructToVector(packet, offset, coin);
            offset += sizeof(coinsPos_t);
        }

        int clientSocket = _fds[i].fd;

        ssize_t bytesSent = write(clientSocket, packet.data(), packet.size());
        printDebugInfo(
            "Sending game state to socket (" + std::to_string(clientSocket) + ")",
            {7, 9, 10},
            true,
            packet.size()
        );

        packet.clear();
        packet.shrink_to_fit();

        if (bytesSent <= 0) {
            close(clientSocket);
            _fds[i].fd = -1;
            continue;
        }
    }
}

/**
 * @brief Sets the debug mode for the communication instance.
 *
 * Sets the debug mode to enable or disable debug messages.
 *
 * @param debug True to enable debug mode, false to disable it.
 */
void Communication::setDebugMode(bool debug)
{
    _debug = debug;
}

/**
 * @brief Prints debug messages if debug mode is enabled.
 *
 *
 * @param packet The packet to print.
 */
void Communication::printDebugInfo(
    std::string message,
    std::vector<int> types,
    bool sent,
    size_t size
)
{
    if (!_debug)
        return;

    std::map<int, std::string> typeNames = {
        {0, "Welcome Packet"},
        {1, "Int Value"},
        {2, "Size_t Value"},
        {3, "Bool Value"},
        {4, "Double Value"},
        {5, "Float Value"},
        {6, "Short Value"},
        {7, "Player Infos"},
        {8, "Username"},
        {9, "Coins Infos"},
        {10, "Obstacles Infos"},
        {11, "Command Enum"},
        {12, "Gamespeed Value"},
        {13, "Player Input (Boolean)"},
        {14, "Start Game"},
        {15, "Healthcheck"},
        {16, "Jetpack Force"},
        {17, "Velocity Limits"},
        {18, "Ask number of players"},
        {19, "Number of players"},
        {20, "Game ended"},
    };

    std::cout << BLUE << "----------------------------------------" << RESET << std::endl;
    std::cout << GREEN + "[DEBUG] " + RESET << message << std::endl;
    if (sent) {
        std::cout << GREEN + "[DEBUG] " + RESET  << "Sent: ";
    } else {
        std::cout << GREEN + "[DEBUG] " + RESET  << "Received: ";
    }

    bool first = true;
    for (auto type : types) {
        auto it = typeNames.find(type);
        if (it != typeNames.end()) {
            if (!first)
                std::cout << ", ";
            std::cout << RED << it->second << RESET;
        } else {
            if (!first)
                std::cout << ", ";
            std::cout << RED << "Unknown Type (" << type << ")" << RESET;
        }
        first = false;
    }
    std::cout << std::endl;
    std::cout << GREEN + "[DEBUG] " + RESET  << "Size: " << size << std::endl;
    std::cout << BLUE << "----------------------------------------" << RESET << std::endl;
}

/**
 * @brief Checks if a player has left the game.
 *
 * Checks if a player has disconnected from the server.
 *
 * @param clientId The ID of the client to check.
 * @return True if the player has left, false otherwise.
 */
bool Communication::isPlayerGone(int clientId)
{
    for (int i = 0; i < NB_CLIENTS; i += 1) {
        if (_fds[i].fd == clientId) {
            return false;
        }
    }
    return true;
}
