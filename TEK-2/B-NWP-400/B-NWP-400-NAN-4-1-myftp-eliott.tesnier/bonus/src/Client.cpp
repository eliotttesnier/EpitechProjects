/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** Client
*/

#include "Client.hpp"
#include "Colors.hpp"
#include <regex>
#include <signal.h>

void signalHandler(int signum)
{
    std::cout << Colors::RESET << std::endl;
    if (signum == SIGQUIT) {
        std::cout << "Logout." << std::endl;
    }
    exit(0);
}

Client::Client(std::string ip, std::string port)
{
    _ip = ip;
    _port = port;
    _socket = 0;
    _host = nullptr;
    _proto = nullptr;
    _fd = 0;
    _ret = 0;
    _response = "";

    signal(SIGINT, signalHandler);  // Ctrl+C
    signal(SIGTERM, signalHandler); // Termination request
}

void Client::createSocket()
{
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == -1) {
        printError("socket creation failed");
        exit(84);
    }
}

void Client::connectToServer()
{
    _host = gethostbyname(_ip.c_str());
    if (_host == nullptr) {
        printError("host not found");
        exit(84);
    }
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(std::stoi(_port));
    _addr.sin_addr = *(struct in_addr *)_host->h_addr;
    _ret = connect(_socket, (struct sockaddr *)&_addr, sizeof(_addr));
    if (_ret == -1) {
        printError("connection failed");
        exit(84);
    }
    _ret = recv(_socket, _buffer, 4096, 0);
    if (_ret == -1) {
        printError("recv failed");
        exit(84);
    }
    _response = std::string(_buffer);
    printResponse(_response);
}

void Client::login()
{
    std::string user;
    std::string pass;

    std::cout << Colors::YELLOW << "Username: " << Colors::RESET;
    std::getline(std::cin, user);
    if (std::cin.eof()) {
        std::cout << Colors::RESET << std::endl;
        closeSocket();
        exit(0);
    }
    _username = user;
    sendRequest("USER " + user);
    receiveResponse();

    std::cout << Colors::YELLOW << "Password: " << Colors::RESET;
    std::getline(std::cin, pass);
    if (std::cin.eof()) {
        std::cout << Colors::RESET << std::endl;
        closeSocket();
        exit(0);
    }
    sendRequest("PASS " + pass);
    receiveResponse();
    printResponse(_response);

    if (_response.find("332") != std::string::npos || _response.at(0) == '5') {
        printError("login failed");
        login();
    }
}

void Client::run()
{
    createSocket();
    connectToServer();

    login();
    while (1) {
        printPrompt();
        std::string request;
        std::getline(std::cin, request);
        parseLine(request);

        if (std::cin.eof()) {
            std::cout << Colors::RESET << std::endl;
            closeSocket();
            exit(0);
        }
    }
    closeSocket();
}

void Client::printPrompt()
{
    std::string currentDir = "";
    sendRequest("PWD");
    receiveResponse();
    currentDir = _response.substr(_response.find_first_of('"') + 1);
    currentDir = currentDir.substr(0, currentDir.find_last_of('"'));


    std::cout << Colors::GREEN << "myftp: " << currentDir << Colors::RESET << " > ";
}

void Client::parseLine(std::string &line)
{
    line.erase(line.find_last_not_of(" \t") + 1);
    std::replace(line.begin(), line.end(), '\t', ' ');

    std::string command = line.substr(0, line.find(' '));
    std::string arg = "";
    size_t pos = line.find(' ');
    if (pos != std::string::npos) {
        arg = line.substr(pos + 1);
    }

    if (line.empty())
        return;

    if (_commands.find(command) == _commands.end()) {
        printError("command not found");
        return;
    }

    (this->*_commands[command])(arg);
}

void Client::execCommand(std::string command)
{
    sendRequest(command);
    receiveResponse();
    printResponse(_response);
}


void Client::sendRequest(std::string request)
{
    request += "\r\n";
    _ret = send(_socket, request.c_str(), request.length(), 0);

    if (_ret == -1) {
        printError("send failed");
        exit(84);
    }
}

void Client::receiveResponse()
{
    memset(_buffer, 0, sizeof(_buffer));
    _ret = recv(_socket, _buffer, sizeof(_buffer) - 1, 0);

    if (_ret == -1) {
        printError("recv failed");
        exit(84);
    }
    if (_ret == 0) {
        printError("Connection closed by server");
        exit(84);
    }
    _buffer[_ret] = '\0';
    _response = std::string(_buffer);
}

void Client::closeSocket()
{
    close(_socket);
}
