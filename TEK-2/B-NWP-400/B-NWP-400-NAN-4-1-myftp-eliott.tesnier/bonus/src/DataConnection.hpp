/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** DataConnection
*/

#pragma once

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>

class DataConnection {
    public:
        DataConnection() = default;
        ~DataConnection() = default;

        int setupPassiveMode(std::string &dataIp, int &dataPort, int &controlSocket);
        int createDataSocket(const std::string &dataIp, int dataPort);
        void closeDataSocket(int dataSocket);
        ssize_t receiveData(int dataSocket, char *buffer, size_t size);
        std::string colorizeListingLine(const std::string& line);

    private:
        char _buffer[4096];
};
