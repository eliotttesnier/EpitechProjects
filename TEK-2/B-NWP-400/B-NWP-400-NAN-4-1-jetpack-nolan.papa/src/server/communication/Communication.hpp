/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Communication
*/

#ifndef COMMUNICATION_HPP_
#define COMMUNICATION_HPP_

#include <map>
#include <sys/types.h>
#include <sys/socket.h>
#include <poll.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <../../include/Player.hpp>
#include <../../include/Coin.hpp>
#include <../../include/Obstacle.hpp>
#include "../Player.hpp"
#include "ClientData.hpp"
#include "GameState.hpp"

#define BUFFER_SIZE 1024
#define NB_CLIENTS 50
#define MIN_CLIENTS 2

struct data_s {
    size_t dataSize;
    ClientInput_t input;
};

typedef std::vector<struct data_s> dataInfos_t;

class Communication
{
    private:
        dataInfos_t _dataInfos;

        std::map<int, std::vector<uint8_t>> _buffer;

        int _serverSocket;
        struct pollfd _fds[NB_CLIENTS];
        bool _debug;

        uint16_t _createHeader(uint8_t nbLists);
        uint16_t _createDataHeader(uint8_t dataCount, uint8_t dataType);

        bool _packetComplete(std::vector<uint8_t> packet);

        bool _checkMagicNb(std::vector<uint8_t> packet);
        ClientData _fillClientData(int clientId);

        int _getNbPlayers();
        void _sendNbClientsToClient(int clientId);

        bool _gameStarted;

        void _sendStartToAllClients();

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

        bool startServer(int port);
        Player getNewClient();
        std::vector<ClientData> getClientsData();
        void sendGameState(GameState gameState);

        bool getGameStarted();

        void printDebugInfo(std::string message, std::vector<int> types, bool sent, size_t size);
        void setDebugMode(bool debug);

        bool isPlayerGone(int clientId);

        void sendGameEnd();
};

#endif /* !COMMUNICATION_HPP_ */
