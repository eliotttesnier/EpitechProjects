/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** DataConnection
*/

#include "DataConnection.hpp"
#include "Colors.hpp"
#include <sstream>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int DataConnection::setupPassiveMode(std::string &dataIp, int &dataPort, int &controlSocket)
{
    const char* pasvCommand = "PASV\r\n";
    if (send(controlSocket, pasvCommand, strlen(pasvCommand), 0) == -1)
        return -1;

    memset(_buffer, 0, sizeof(_buffer));
    if (recv(controlSocket, _buffer, sizeof(_buffer) - 1, 0) == -1)
        return -1;

    std::string response(_buffer);
    if (response[0] == '5')
        return -1;

    size_t start = response.find('(');
    size_t end = response.find(')');
    std::string nums = response.substr(start + 1, end - start - 1);

    std::vector<int> values;
    std::stringstream ss(nums);
    std::string item;
    while (std::getline(ss, item, ','))
        values.push_back(std::stoi(item));

    dataPort = values[4] * 256 + values[5];
    dataIp = std::to_string(values[0]) + "." +
             std::to_string(values[1]) + "." +
             std::to_string(values[2]) + "." +
             std::to_string(values[3]);

    return 0;
}

int DataConnection::createDataSocket(const std::string &dataIp, int dataPort)
{
    int dataSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (dataSocket == -1)
        return -1;

    struct sockaddr_in dataAddr;
    dataAddr.sin_family = AF_INET;
    dataAddr.sin_port = htons(dataPort);
    dataAddr.sin_addr.s_addr = inet_addr(dataIp.c_str());

    if (connect(dataSocket, (struct sockaddr*)&dataAddr, sizeof(dataAddr)) == -1) {
        close(dataSocket);
        return -1;
    }
    return dataSocket;
}

void DataConnection::closeDataSocket(int dataSocket)
{
    close(dataSocket);
}

ssize_t DataConnection::receiveData(int dataSocket, char *buffer, size_t size)
{
    return recv(dataSocket, buffer, size - 1, 0);
}

std::string DataConnection::colorizeListingLine(const std::string& line)
{
    if (line.empty() || line.length() < 2)
        return line;

    std::string coloredLine = line;
    size_t lastSpace = line.find_last_of(' ');
    if (lastSpace == std::string::npos)
        return line;

    std::string filename = line.substr(lastSpace + 1);
    std::string prefix = line.substr(0, lastSpace + 1);

    char fileType = line[0];
    switch (fileType) {
        case 'd':
            return prefix + Colors::BLUE + filename + Colors::RESET;
        case 'l':
            return prefix + Colors::CYAN + filename + Colors::RESET;
        case '-':
            if (line.find('x') != std::string::npos)
                return prefix + Colors::GREEN + filename + Colors::RESET;
            return prefix + Colors::RESET + filename;
        case 'b':
        case 'c':
            return prefix + Colors::YELLOW + filename + Colors::RESET;
        case 'p':
        case 's':
            return prefix + Colors::MAGENTA + filename + Colors::RESET;
        default:
            return line;
    }
}