/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** IIPCChannel interface
*/

#pragma once

#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <sstream>

namespace Plazza {
    class IIPCChannel {
    public:
        virtual ~IIPCChannel() = default;

        virtual bool send(const std::string &message) = 0;
        virtual std::string receive() = 0;
        virtual bool hasData(int timeoutMs = 0) = 0;
        virtual void close() = 0;
        virtual bool isValid() const = 0;

        template<typename T>
        friend IIPCChannel& operator<<(IIPCChannel& channel, const T& data);

        template<typename T>
        friend IIPCChannel& operator>>(IIPCChannel& channel, T& data);
    };

    template<typename T>
    IIPCChannel& operator<<(IIPCChannel& channel, const T& data) {
        std::stringstream ss;
        ss << data;
        channel.send(ss.str());
        return channel;
    }

    template<>
    inline IIPCChannel& operator<<(IIPCChannel& channel, const std::string& data) {
        channel.send(data);
        return channel;
    }

    template<typename T>
    IIPCChannel& operator>>(IIPCChannel& channel, T& data) {
        std::string message = channel.receive();
        if (!message.empty()) {
            std::stringstream ss(message);
            ss >> data;
        }
        return channel;
    }

    template<>
    inline IIPCChannel& operator>>(IIPCChannel& channel, std::string& data) {
        data = channel.receive();
        return channel;
    }
}
