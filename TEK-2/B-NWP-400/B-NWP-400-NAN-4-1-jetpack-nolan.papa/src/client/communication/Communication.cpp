/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Communication
*/

#include <map>
#include <vector>
#include <string>
#include <iostream>

#include "Communication.hpp"

const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string BLUE = "\033[34m";
const std::string RESET = "\033[0m";

/**
 * @brief Constructs a Communication instance.
 *
 * Initializes the communication state with default values, including 
 * connection status, socket descriptor, and error messages.
 */
Communication::Communication()
{
    _errorMessage = "";
    _isConnected = false;
    _packetToSend = false;
    _socket = -1;
    _username = "";
    _isUsernameSent = false;
    _needsToClose = false;
    _flying = false;
    _fds[0].fd = -1;
    _fds[0].events = POLLIN;
    _debug = false;
    _shouldSendStartGame = false;
    _gameStart = false;
    _shouldGetNbPlayers = true;
    _nbPlayers = 0;
    _dataInfos = {
        {0},
        {sizeof(int)},
        {sizeof(size_t)},
        {sizeof(bool)},
        {sizeof(double)},
        {sizeof(float)},
        {sizeof(uint16_t)},
        {sizeof(player_t)},
        {sizeof(char) * 20},
        {sizeof(coinsPos_t)},
        {sizeof(obstacle_t)},
        {0},
        {sizeof(int)},
        {sizeof(bool)},
        {0},
        {0},
        {sizeof(int)},
        {sizeof(double)},
        {0},
        {sizeof(int)},
        {0},
    };
    _gameEnd = false;
}

/**
 * @brief Destructor for the Communication class.
 *
 * Cleans up the file descriptors and data structures used for communication.
 */
Communication::~Communication()
{
    if (_socket != -1)
        close(_socket);
    _socket = -1;
    _dataInfos.clear();
    _dataInfos.shrink_to_fit();
}

/**
 * @brief Retrieves and clears the last error message.
 *
 * Returns the last recorded error message and resets the error state.
 *
 * @return The last error message as a string.
 */
std::string Communication::getError()
{
    std::string message = _errorMessage;
    _errorMessage = "";
    return message;
}

/**
 * @brief Sets the IP address for the server connection.
 *
 * Stores the provided IP address for later use in the connection process.
 *
 * @param ip The IP address as a string.
 */
void Communication::setIp(const std::string &ip)
{
    _ip = ip;
}

/**
 * @brief Sets the port for the server connection.
 *
 * Updates the stored port number for establishing a connection.
 *
 * @param port The port number as a string.
 */
void Communication::setPort(const std::string &port)
{
    _port = port;
}

/**
 * @brief Sets the username for the communication session.
 *
 * Stores the given username to be sent to the server upon connection.
 *
 * @param username The username as a string.
 */
void Communication::setUsername(const std::string &username)
{
    _username = username;
}

/**
 * @brief Sets the flying state of the user.
 *
 * Updates the internal flag to indicate whether the user is flying or not.
 *
 * @param flying True if the user is flying, false otherwise.
 */
void Communication::setUserFlying(bool flying)
{
    _flying = flying;
}

/**
 * @brief Sets the flag to indicate if a packet should be sent.
 *
 * Updates the internal flag to signal that a packet needs to be sent.
 *
 * @param packetToSend True if a packet should be sent, false otherwise.
 */
void Communication::setPacketToSend(bool packetToSend)
{
    _packetToSend = packetToSend;
}

/**
 * @brief Sets the flag to indicate if the game should start.
 *
 * Updates the internal flag to signal that the game should start.
 *
 * @param startGame True if the game should start, false otherwise.
 */
void Communication::setShouldSendStartGame(bool startGame)
{
    _shouldSendStartGame = startGame;
}

/**
 * @brief Sets the termination flag for the communication thread.
 *
 * Updates the `_needsToClose` flag to signal the communication loop to stop.
 *
 * @param needsToClose True to request termination, false to keep running.
 */
void Communication::setNeedsToClose(bool needsToClose)
{
    _needsToClose = needsToClose;
}

/**
 * @brief Retrieves the list of players.
 *
 * Returns the list of players currently stored in the communication instance.
 *
 * @return A vector of player_t objects representing the players.
 */
std::vector<player_t> Communication::getPlayers()
{
    std::vector<player_t> players;
    players.reserve(_players.size());
    for (const auto &player : _players) {
        players.push_back(player);
    }
    _players.clear();
    _players.shrink_to_fit();
    return players;
}

/**
 * @brief Retrieves the list of coins.
 *
 * Returns the list of coins currently stored in the communication instance.
 *
 * @return A vector of coinsPos_t objects representing the coins.
 */
std::vector<coinsPos_t> Communication::getCoins()
{
    std::vector<coinsPos_t> coins;
    coins.reserve(_coins.size());
    for (const auto &coin : _coins) {
        coins.push_back(coin);
    }
    _coins.clear();
    _coins.shrink_to_fit();
    return coins;
}

/**
 * @brief Retrieves the list of obstacles.
 *
 * Returns the list of obstacles currently stored in the communication instance.
 * Uses move semantics to efficiently transfer ownership without copying.
 *
 * @return A vector of obstacle_t objects representing the obstacles.
 */
std::vector<obstacle_t> Communication::getObstacles()
{
    std::vector<obstacle_t> obstacles;
    obstacles.reserve(_obstacles.size());
    for (const auto &obstacle : _obstacles) {
        obstacles.push_back(obstacle);
    }
    _obstacles.clear();
    _obstacles.shrink_to_fit();
    return obstacles;
}

/**
 * @brief Retrieves the game start status.
 *
 * Returns the current game start status.
 *
 * @return True if the game has started, false otherwise.
 */
bool Communication::getGameStart()
{
    return _gameStart;
}

/**
 * @brief Gets the number of players.
 *
 * @returns the number of players currently connected.
 */
int Communication::getNbPlayers()
{
    _shouldGetNbPlayers = true;
    return _nbPlayers;
}

/**
 * @brief Gets the game end status.
 * 
 * @return True if the game has ended, false otherwise.
*/
bool Communication::getGameEnd()
{
    return _gameEnd;
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
 * @brief Verifies the first packet received from the server.
 *
 * Checks if the first packet received from the server is valid and meets
 * the expected criteria.
 *
 * @param packet The received packet to verify.
 * @return True if the packet is valid, false otherwise.
 */
bool Communication::_verifyFirstPacket(std::vector<uint8_t> packet)
{
    if (!_checkMagicNb(packet)) {
        _errorMessage = "Invalid magic number in initial packet: " +
            std::to_string((packet[0] << 8 | packet[1]) >> 4);
        return false;
    }

    uint8_t dataListCount = packet[1] & 0b00001111;
    packet.erase(packet.begin(), packet.begin() + 2);

    if (dataListCount != 1) {
        _errorMessage = "Invalid data list count in initial packet: " +
            std::to_string(dataListCount);
        return false;
    }

    uint16_t dataHeader = packet[0];
    dataHeader <<= 8;
    dataHeader |= packet[1];
    packet.erase(packet.begin(), packet.begin() + 2);
    uint8_t dataCount = dataHeader >> 6;
    uint8_t dataType = dataHeader & 0b111111;

    if (dataCount != 2) {
        _errorMessage = "Invalid data count in initial packet: " +
            std::to_string(dataCount);
        return false;
    }

    if (dataType != 2) {
        _errorMessage = "Invalid data type in initial packet: " +
            std::to_string(dataType);
        return false;
    }

    size_t id;
    std::memcpy(&id, packet.data(), sizeof(id));
    packet.erase(packet.begin(), packet.begin() + sizeof(id));

    if (id == 0) {
        _errorMessage = "Invalid ID in initial packet: " +
            std::to_string(id);
        return false;
    }

    size_t gameSpeed;
    std::memcpy(&gameSpeed, packet.data(), sizeof(gameSpeed));
    packet.erase(packet.begin(), packet.begin() + sizeof(gameSpeed));

    if (gameSpeed == 0) {
        _errorMessage = "Invalid game speed in initial packet: " +
            std::to_string(gameSpeed);
        return false;
    }
    return true;
}

/**
 * @brief Establishes a connection to the server.
 *
 * Creates a socket, configures the server address, and attempts to connect.
 * If successful, updates the connection status and socket descriptor.
 * If an error occurs, updates `_errorMessage` accordingly.
 */
void Communication::connectToServer()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        _errorMessage = "Failed to create socket";
        return;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(std::stoi(_port));
    if (inet_pton(AF_INET, _ip.c_str(), &serverAddr.sin_addr) <= 0) {
        _errorMessage = "Invalid IP address";
        close(sock);
        return;
    }

    if (connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        _errorMessage = "Failed to connect to server";
        close(sock);
        return;
    }

    _isConnected = true;
    _socket = sock;
    _fds[0].fd = _socket;
    _fds[0].events = POLLIN;
    _errorMessage = "";

    int ret = poll(_fds, 1, 5000);

    if (ret <= 0) {
        _errorMessage = "Timeout or error while waiting for server response";
        close(_socket);
        return;
    }

    std::vector<uint8_t> packet(BUFFER_SIZE);
    ssize_t bytesRead = read(_socket, packet.data(), BUFFER_SIZE);

    if (bytesRead <= 0) {
        _errorMessage = "Failed to read initial packet from server";
        close(_socket);
        return;
    }

    if (!_verifyFirstPacket(packet)) {
        close(_socket);
        return;
    }

    std::cout << GREEN << "[DEBUG] " << RESET
        << "Connected to server at " << _ip << ":" << _port << std::endl;

    runCommunication();
}

/**
 * @brief Sends the stored username to the server.
 *
 * Constructs a username packet and sends it over the socket.
 * If the client is not connected, sets an error message.
 */
void Communication::_sendUsername()
{
    if (!_isConnected) {
        _errorMessage = "Not connected to server";
        return;
    }

    uint16_t header = _createHeader(1);
    uint16_t dataHeader = _createDataHeader(1, 8);
    std::vector<uint8_t> packet(
        sizeof(header) + sizeof(dataHeader) + sizeof(uint8_t) * 20,
        0
    );

    size_t offset = 0;

    _writeToVector(packet, offset, header);
    offset += sizeof(header);

    _writeToVector(packet, offset, dataHeader);
    offset += sizeof(dataHeader);

    char username[20] = {0};

    std::strncpy(username, _username.c_str(), sizeof(username));
    _writeRawStructToVector(packet, offset, username);

    write(_socket, packet.data(), packet.size());
    printDebug("Sending username to server", {8}, true, packet.size());
    _packetToSend = false;
    packet.clear();
    packet.shrink_to_fit();
}

/**
 * @brief Sends the start game command to the server.
 *
 * Constructs a start game packet and sends it over the socket.
 * If the client is not connected, sets an error message.
 */
void Communication::_sendStartGame()
{
    if (!_isConnected) {
        _errorMessage = "Not connected to server";
        return;
    }
    uint16_t header = _createHeader(1);
    uint16_t dataHeader = _createDataHeader(1, 14);
    std::vector<uint8_t> packet(
        sizeof(header) + sizeof(dataHeader),
        0
    );

    _writeToVector(packet, 0, header);
    _writeToVector(packet, sizeof(header), dataHeader);

    write(_socket, packet.data(), packet.size());
    printDebug("Sending start game to server", {14}, true, packet.size());
    packet.clear();
    packet.shrink_to_fit();
}

/**
 * @brief Sends the request for the number of players to the server.
 *
 * Constructs a packet to request the number of players and sends it over the socket.
 * If the client is not connected, sets an error message.
 */
void Communication::_sendGetNbPlayers()
{
    if (!_isConnected) {
        _errorMessage = "Not connected to server";
        return;
    }
    uint16_t header = _createHeader(1);
    uint16_t dataHeader = _createDataHeader(1, 18);
    std::vector<uint8_t> packet(
        sizeof(header) + sizeof(dataHeader),
        0
    );

    _writeToVector(packet, 0, header);
    _writeToVector(packet, sizeof(header), dataHeader);

    write(_socket, packet.data(), packet.size());
    printDebug("Sending get number of players to server", {18}, true, packet.size());
    packet.clear();
    packet.shrink_to_fit();
}

/**
 * @brief Sends the flying state of the client to the server.
 *
 * Constructs a packet with the flying state and sends it over the socket.
 * If the client is not connected, sets an error message.
 */
void Communication::_sendClientInput()
{
    uint16_t header = _createHeader(1);
    uint16_t dataHeader = _createDataHeader(1, 13);
    std::vector<uint8_t> packet(
        sizeof(header) + sizeof(dataHeader) + sizeof(uint8_t),
        0
    );

    size_t offset = 0;

    _writeToVector(packet, offset, header);
    offset += sizeof(header);

    _writeToVector(packet, offset, dataHeader);
    offset += sizeof(dataHeader);

    _writeToVector(packet, offset, _flying);

    ssize_t bytesSent = write(_socket, packet.data(), packet.size());
    printDebug("Sending flying state to server", {13}, true, packet.size());
    if (bytesSent <= 0) {
        std::cerr << "_sendClientInput: No communication with server." << std::endl;
    }
    packet.clear();
    packet.shrink_to_fit();
}

/**
 * @brief Checks if the magic number in the packet is valid.
 *
 * Validates the magic number in the received packet to ensure it is correct.
 *
 * @param packet The received packet to check.
 * @return True if the magic number is valid, false otherwise.
 */

bool Communication::_checkMagicNb(std::vector<uint8_t> packet)
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
 * @brief Receives data from the server.
 *
 * Reads data from the socket and processes it. If an error occurs, sets an error message.
 */
void Communication::_receiveServerData()
{
    int ret = poll(_fds, 1, 0);

    if (ret < 0)
        return;

    if (ret > 0 && (_fds[0].revents & POLLIN)) {
        std::vector<uint8_t> packet(BUFFER_SIZE, 0);
        ssize_t bytesRead = read(_socket, packet.data(), BUFFER_SIZE);

        if (bytesRead <= 0) {
            _errorMessage = "Failed to read from server";
            return;
        }

        _buffer.insert(_buffer.end(), packet.begin(), packet.begin() + bytesRead);
    }

    while (true) {
        if (_buffer.size() == 0)
            return;

        if (!_checkMagicNb(_buffer)) {
            _errorMessage = "Invalid magic number in packet";
            return;
        }

        if (!_packetComplete(_buffer))
            return;

        uint8_t dataListCount = _buffer[1] & 0b00001111;
        _buffer.erase(_buffer.begin(), _buffer.begin() + 2);

        for (uint8_t i = 0; i < dataListCount; i++) {
            uint16_t dataHeader = _buffer[0];
            dataHeader <<= 8;
            dataHeader |= _buffer[1];
            _buffer.erase(_buffer.begin(), _buffer.begin() + 2);

            uint8_t nb = dataHeader >> 6;
            uint8_t dataType = dataHeader & 0b111111;

            if (dataType == 7)
                printDebug("Received player data", {7}, false, sizeof(player_t) * nb);
            else if (dataType == 9)
                printDebug("Received coins data", {9}, false, sizeof(coinsPos_t) * nb);
            else if (dataType == 10)
                printDebug("Received obstacles data", {10}, false, sizeof(obstacle_t) * nb);
            else if (dataType == 14)
                printDebug("Received start game data", {14}, false, sizeof(uint8_t));
            else if (dataType == 19)
                printDebug("Received number of players data", {19}, false, sizeof(_nbPlayers));
            else if (dataType == 20)
                printDebug("Received game end data", {20}, false, sizeof(uint8_t));
            else
                printDebug("Received unhandled data", {dataType}, false, 0);

            for (uint8_t j = 0; j < nb; j++) {
                if (dataType == 7) {
                    player_t player{};
                    std::memcpy(&player, _buffer.data(), sizeof(player_t));
                    _players.push_back(player);
                    _buffer.erase(_buffer.begin(), _buffer.begin() + sizeof(player_t));
                } else if (dataType == 9) {
                    coinsPos_t coin{};
                    std::memcpy(&coin, _buffer.data(), sizeof(coinsPos_t));
                    _coins.push_back(coin);
                    _buffer.erase(_buffer.begin(), _buffer.begin() + sizeof(coinsPos_t));
                } else if (dataType == 10) {
                    obstacle_t obstacle{};
                    std::memcpy(&obstacle, _buffer.data(), sizeof(obstacle_t));
                    _obstacles.push_back(obstacle);
                    _buffer.erase(_buffer.begin(), _buffer.begin() + sizeof(obstacle_t));
                } else if (dataType == 14) {
                    _gameStart = true;
                } else if (dataType == 19) {
                    std::memcpy(&_nbPlayers, _buffer.data(), sizeof(_nbPlayers));
                    _buffer.erase(_buffer.begin(), _buffer.begin() + sizeof(_nbPlayers));
                } else if (dataType == 20) {
                    _gameEnd = true;
                }
            }
        }
    }
}

/**
 * @brief Manages the communication loop with the server.
 *
 * Continuously checks the connection status, sends the username if needed,
 * handles packet transmission, and receives data from the server.
 * The loop terminates when `_needsToClose` is set to true.
 */
void Communication::runCommunication()
{
    while (!_needsToClose) {
        if (!_isConnected) {
            _errorMessage = "Not connected to server";
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }
        if (!_isUsernameSent) {
            _sendUsername();
            _isUsernameSent = true;
        }
        if (_shouldSendStartGame) {
            _sendStartGame();
            _shouldSendStartGame = false;
        }
        if (_shouldGetNbPlayers) {
            _sendGetNbPlayers();
            _shouldGetNbPlayers = false;
        }
        if (_packetToSend) {
            _sendClientInput();
            _packetToSend = false;
        }
        _receiveServerData();
    }
    closeConnection();
}

/**
 * @brief Closes the connection with the server.
 *
 * Closes the socket if connected and resets connection-related states.
 */
void Communication::closeConnection()
{
    if (_isConnected) {
        if (_socket != -1)
            close(_socket);
        _socket = -1;
    }
    _isConnected = false;
    _isUsernameSent = false;
}

/**
 * @brief Prints debug messages if debug mode is enabled.
 *
 *
 * @param packet The packet to print.
 */
void Communication::printDebug(
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
 * @brief Sets the debug mode for the communication instance.
 *
 * Enables or disables debug mode, affecting the verbosity of debug messages.
 *
 * @param debug True to enable debug mode, false to disable it.
 */
void Communication::setDebugMode(bool debug)
{
    _debug = debug;
}
