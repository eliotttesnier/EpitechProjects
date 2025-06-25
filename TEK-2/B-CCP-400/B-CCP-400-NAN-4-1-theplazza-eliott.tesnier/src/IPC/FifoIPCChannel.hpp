/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** FIFO IPC channel implementation
*/

#pragma once

#include "IIPCChannel.hpp"
#include <string>
#include <poll.h>
#include <sys/types.h>
#include <memory>

namespace Plazza {
    class FifoIPCChannel : public IIPCChannel {
    public:
        enum class Mode {
            PARENT,
            CHILD
        };

        FifoIPCChannel(int id, Mode mode, const std::string &basePath = "/tmp");
        ~FifoIPCChannel() override;

        bool send(const std::string &message) override;
        std::string receive() override;
        bool hasData(int timeoutMs = 0) override;
        void close() override;
        bool isValid() const override;

    private:
        bool createPipes();
        bool openPipes();

    private:
        int _id;
        Mode _mode;
        std::string _basePath;
        std::string _writePipePath;
        std::string _readPipePath;
        int _writeFd;
        int _readFd;
        struct pollfd _pollFd;
        bool _isConnected;
    };
}
