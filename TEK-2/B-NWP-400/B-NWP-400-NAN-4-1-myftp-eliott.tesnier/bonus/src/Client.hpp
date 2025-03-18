/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** Client
*/

#pragma once

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "DataConnection.hpp"

class Client {
    public:
        Client(std::string ip, std::string port);
        ~Client() = default;

        void run();

    private:
        std::string _username;
        std::string _ip;
        std::string _port;
        int _socket;
        struct sockaddr_in _addr;
        struct hostent *_host;
        struct protoent *_proto;
        int _fd;
        int _ret;
        char _buffer[4096];
        std::string _response;

        std::map<std::string, void (Client::*)(std::string)> _commands = {
            {"help", &Client::help},
            {"noop", &Client::noop},
            {"pwd", &Client::pwd},
            {"cd", &Client::cd},
            {"cdup", &Client::cdup},
            {"rm", &Client::rm},
            {"ls", &Client::ls},
            {"cat", &Client::cat},
            {"get", &Client::get},
            {"touch", &Client::touch},
            {"put", &Client::put},
            {"quit", &Client::quit},
            {"exit", &Client::quit},
            {"bye", &Client::quit},
            {"who", &Client::who},
            {"whoami", &Client::who},
            // Bonus
            {"mkdir", &Client::mkdir},
            {"rmdir", &Client::rmdir},
            {"mv", &Client::mv},
            {"rename", &Client::mv},
            {"cp", &Client::cp},
            {"copy", &Client::cp},
            {"size", &Client::size},
            {"mdtm", &Client::mdtm},
        };

        // Shell
        void printPrompt();
        void printResponse(std::string response);
        void printError(std::string error);
        void parseLine(std::string &line);
        void execCommand(std::string command);

        void createSocket();
        void connectToServer();
        void login();
        void sendRequest(std::string request);
        void receiveResponse();
        void closeSocket();

        // commands
        void help(std::string arg);
        void noop(std::string arg);
        void pwd(std::string arg);
        void cd(std::string arg);
        void cdup(std::string arg);
        void rm(std::string arg);
        void ls(std::string arg);
        void cat(std::string arg);
        void get(std::string arg);
        void touch(std::string arg);
        void put(std::string arg);
        void quit(std::string arg);
        void who(std::string arg);
        // Bonus
        void mkdir(std::string arg);
        void rmdir(std::string arg);
        void mv(std::string arg);
        void cp(std::string arg);
        void size(std::string arg);
        void mdtm(std::string arg);

        DataConnection _dataConnection;
};
