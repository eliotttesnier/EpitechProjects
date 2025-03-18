/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** FileCommands
*/

#include "../Client.hpp"
#include "../Colors.hpp"
#include <fstream>

void Client::ls(std::string arg)
{
    std::string dataIp;
    int dataPort;

    if (_dataConnection.setupPassiveMode(dataIp, dataPort, _socket) == -1)
        return;

    int dataSocket = _dataConnection.createDataSocket(dataIp, dataPort);
    if (dataSocket == -1)
        return;

    sendRequest("LIST" + (arg.empty() ? "" : " " + arg));
    receiveResponse();
    printResponse(_response);

    if (_response[0] == '5') {
        _dataConnection.closeDataSocket(dataSocket);
        return;
    }

    char dataBuffer[4096];
    ssize_t bytes;
    std::string accumulated;

    while ((bytes = _dataConnection.receiveData(dataSocket, dataBuffer, sizeof(dataBuffer))) > 0) {
        dataBuffer[bytes] = '\0';
        accumulated += dataBuffer;
    }

    std::istringstream stream(accumulated);
    std::string line;
    while (std::getline(stream, line)) {
        if (!line.empty()) {
            if (line.back() == '\r')
                line.pop_back();
            std::cout << _dataConnection.colorizeListingLine(line) << std::endl;
        }
    }

    _dataConnection.closeDataSocket(dataSocket);
    receiveResponse();
    printResponse(_response);
}

void Client::cat(std::string arg)
{
    if (arg.empty()) {
        printError("Usage: cat <filename>");
        return;
    }

    std::string dataIp;
    int dataPort;

    if (_dataConnection.setupPassiveMode(dataIp, dataPort, _socket) == -1)
        return;

    int dataSocket = _dataConnection.createDataSocket(dataIp, dataPort);
    if (dataSocket == -1)
        return;

    sendRequest("RETR " + arg);
    receiveResponse();
    printResponse(_response);

    if (_response[0] == '5') {
        _dataConnection.closeDataSocket(dataSocket);
        return;
    }

    char dataBuffer[4096];
    ssize_t bytes;

    while ((bytes = _dataConnection.receiveData(dataSocket, dataBuffer, sizeof(dataBuffer))) > 0) {
        dataBuffer[bytes] = '\0';
        std::cout << dataBuffer;
    }
    std::cout << std::endl;

    _dataConnection.closeDataSocket(dataSocket);
    receiveResponse();
    printResponse(_response);
}

void Client::get(std::string arg)
{
    if (arg.empty()) {
        printError("Usage: get <filename>");
        return;
    }

    std::string dataIp;
    int dataPort;

    if (_dataConnection.setupPassiveMode(dataIp, dataPort, _socket) == -1)
        return;

    int dataSocket = _dataConnection.createDataSocket(dataIp, dataPort);
    if (dataSocket == -1)
        return;

    sendRequest("RETR " + arg);
    receiveResponse();
    printResponse(_response);

    if (_response[0] == '5') {
        _dataConnection.closeDataSocket(dataSocket);
        return;
    }

    std::ofstream file(arg, std::ios::binary);
    if (!file.is_open()) {
        printError("Cannot create local file");
        _dataConnection.closeDataSocket(dataSocket);
        return;
    }

    char dataBuffer[4096];
    ssize_t bytes;

    while ((bytes = _dataConnection.receiveData(dataSocket, dataBuffer, sizeof(dataBuffer))) > 0) {
        file.write(dataBuffer, bytes);
    }

    file.close();
    _dataConnection.closeDataSocket(dataSocket);
    receiveResponse();
    printResponse(_response);
}

void Client::touch(std::string arg)
{
    if (arg.empty()) {
        printError("Usage: touch <filename>");
        return;
    }

    std::string dataIp;
    int dataPort;

    if (_dataConnection.setupPassiveMode(dataIp, dataPort, _socket) == -1)
        return;

    int dataSocket = _dataConnection.createDataSocket(dataIp, dataPort);
    if (dataSocket == -1)
        return;

    sendRequest("STOR " + arg);
    receiveResponse();
    printResponse(_response);

    if (_response[0] == '5') {
        _dataConnection.closeDataSocket(dataSocket);
        return;
    }

    // Send empty file
    _dataConnection.closeDataSocket(dataSocket);
    receiveResponse();
    printResponse(_response);
}

void Client::put(std::string arg)
{
    if (arg.empty()) {
        printError("Usage: put <filename>");
        return;
    }

    std::ifstream file(arg, std::ios::binary);
    if (!file.is_open()) {
        printError("Cannot open local file");
        return;
    }

    std::string dataIp;
    int dataPort;

    if (_dataConnection.setupPassiveMode(dataIp, dataPort, _socket) == -1)
        return;

    int dataSocket = _dataConnection.createDataSocket(dataIp, dataPort);
    if (dataSocket == -1)
        return;

    sendRequest("STOR " + arg);
    receiveResponse();
    printResponse(_response);

    if (_response[0] == '5') {
        _dataConnection.closeDataSocket(dataSocket);
        return;
    }

    char dataBuffer[4096];
    while (!file.eof()) {
        file.read(dataBuffer, sizeof(dataBuffer));
        std::streamsize bytes = file.gcount();
        if (bytes > 0) {
            send(dataSocket, dataBuffer, bytes, 0);
        }
    }

    file.close();
    _dataConnection.closeDataSocket(dataSocket);
    receiveResponse();
    printResponse(_response);
}
