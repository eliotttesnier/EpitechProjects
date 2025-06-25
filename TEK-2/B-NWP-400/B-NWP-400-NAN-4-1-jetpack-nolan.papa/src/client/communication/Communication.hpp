/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Communication
*/

#ifndef COMMUNICATION_HPP_
#define COMMUNICATION_HPP_

#include <string>
#include <vector>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
#include <cstring>
#include <thread>
#include <chrono>
#include <algorithm>

#include <../../include/Player.hpp>
#include <../../include/Coin.hpp>
#include <../../include/Obstacle.hpp>

#define BUFFER_SIZE 2048

struct data_s {
    size_t dataSize;
};

typedef std::vector<struct data_s> dataInfos_t;

class Communication
{
    private:
        dataInfos_t _dataInfos;

        std::vector<uint8_t> _buffer;

        std::string _ip;
        std::string _port;
        int _socket;

        struct pollfd _fds[1];

        bool _needsToClose;
        bool _debug;

        std::string _errorMessage;

        bool _isConnected;
        bool _packetToSend;
        bool _isUsernameSent;

        std::string _username;

        bool _shouldSendStartGame;
        bool _gameStart;

        bool _flying;

        int _nbPlayers;
        bool _shouldGetNbPlayers;

        bool _gameEnd;

        std::vector<player_t> _players;
        std::vector<coinsPos_t> _coins;
        std::vector<obstacle_t> _obstacles;

        uint16_t _createHeader(uint8_t nbLists);
        uint16_t _createDataHeader(uint8_t dataCount, uint8_t dataType);

        void _sendUsername();
        void _sendStartGame();
        void _sendGetNbPlayers();
        void _sendClientInput();
        void _receiveServerData();

        bool _packetComplete(std::vector<uint8_t> packet);
        bool _checkMagicNb(std::vector<uint8_t> packet);

        bool _verifyFirstPacket(std::vector<uint8_t> packet);

        template<typename T>
        void _writeToVector(std::vector<uint8_t>& vec, size_t offset, const T& data) {
            static_assert(std::is_trivially_copyable<T>::value, "T must be trivially copyable");

            const uint8_t* rawData = reinterpret_cast<const uint8_t*>(&data);

            if (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__) {
                for (size_t i = 0; i < sizeof(T); i++) {
                    size_t index = sizeof(T) - 1 - i;

                    vec[offset + i] = rawData[index];
                }
            } else {
                for (size_t i = 0; i < sizeof(T); i++) {
                    vec[offset + i] = rawData[i];
                }
            }
        }
        template<typename T>
        void _writeRawStructToVector(std::vector<uint8_t>& vec, size_t offset, const T& data) {
            static_assert(std::is_trivially_copyable<T>::value, "T must be trivially copyable");
        
            const uint8_t* rawData = reinterpret_cast<const uint8_t*>(&data);
            if (offset + sizeof(T) > vec.size()) {
                vec.resize(offset + sizeof(T));
            }
        
            std::memcpy(vec.data() + offset, rawData, sizeof(T));
        }

    public:
        Communication();
        ~Communication();

        void connectToServer();
        void runCommunication();
        void closeConnection();

        std::string getError();

        void setIp(const std::string &ip);
        void setPort(const std::string &port);

        void setUsername(const std::string &username);
        void setUserFlying(bool flying);
        void setPacketToSend(bool packetToSend);

        void setShouldSendStartGame(bool startGame);

        void setNeedsToClose(bool needsToClose);

        std::vector<player_t> getPlayers();
        std::vector<coinsPos_t> getCoins();
        std::vector<obstacle_t> getObstacles();

        bool getGameStart();

        int getNbPlayers();

        void printDebug(std::string message, std::vector<int> types, bool sent, size_t size);
        void setDebugMode(bool debug);

        bool getGameEnd();
};

#endif /* !COMMUNICATION_HPP_ */
