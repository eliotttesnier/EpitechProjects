/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** FIFO IPC channel implementation
*/

#include "FifoIPCChannel.hpp"

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <poll.h>
#include <cerrno>
#include <cstring>
#include <csignal>
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <string>
#include <mutex>

namespace Plazza {

FifoIPCChannel::FifoIPCChannel(int id, Mode mode, const std::string &basePath)
    : _id(id), _mode(mode), _basePath(basePath), _writeFd(-1), _readFd(-1), _isConnected(false)
{
    std::memset(&_pollFd, 0, sizeof(struct pollfd));

    std::stringstream parentToChildPathSS;
    parentToChildPathSS << _basePath << "/reception_to_kitchen_" << _id << ".fifo";
    std::stringstream childToParentPathSS;
    childToParentPathSS << _basePath << "/kitchen_to_reception_" << _id << ".fifo";

    if (_mode == Mode::PARENT) {
        _writePipePath = parentToChildPathSS.str();
        _readPipePath = childToParentPathSS.str();
    } else {
        _writePipePath = childToParentPathSS.str();
        _readPipePath = parentToChildPathSS.str();
    }

    if (createPipes() && openPipes())
        _isConnected = true;
}

FifoIPCChannel::~FifoIPCChannel()
{
    close();
}

bool FifoIPCChannel::createPipes()
{
    if (_mode == Mode::PARENT) {
        unlink(_writePipePath.c_str());
        unlink(_readPipePath.c_str());

        if (mkfifo(_writePipePath.c_str(), 0666) < 0) {
            std::cerr << "Failed to create write FIFO: " << strerror(errno) << std::endl;
            return false;
        }

        if (mkfifo(_readPipePath.c_str(), 0666) < 0) {
            std::cerr << "Failed to create read FIFO: " << strerror(errno) << std::endl;
            unlink(_writePipePath.c_str());
            return false;
        }
        return true;
    } else {
        int timeout = 50;
        struct stat wstat, rstat;

        for (int i = 0; i < timeout; i++) {
            if (stat(_readPipePath.c_str(), &rstat) == 0 && stat(_writePipePath.c_str(),
                &wstat) == 0) {
                return true;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        std::cerr << "Timeout waiting for FIFOs to be created" << std::endl;
        return false;
    }
}

bool FifoIPCChannel::openPipes()
{
    if (_mode == Mode::PARENT) {
        _readFd = open(_readPipePath.c_str(), O_RDONLY | O_NONBLOCK);
        if (_readFd < 0) {
            std::cerr << "Failed to open read FIFO: " << strerror(errno) << std::endl;
            return false;
        }

        _writeFd = open(_writePipePath.c_str(), O_WRONLY);
        if (_writeFd < 0) {
            std::cerr << "Failed to open write FIFO: " << strerror(errno) << std::endl;
            ::close(_readFd);
            _readFd = -1;
            return false;
        }

        int flags = fcntl(_writeFd, F_GETFL, 0);
        fcntl(_writeFd, F_SETFL, flags | O_NONBLOCK);
    } else {
        _writeFd = open(_writePipePath.c_str(), O_WRONLY | O_NONBLOCK);
        if (_writeFd < 0) {
            _writeFd = open(_writePipePath.c_str(), O_WRONLY);
            if (_writeFd < 0) {
                std::cerr << "Failed to open write FIFO: " << strerror(errno) << std::endl;
                return false;
            }

            int flags = fcntl(_writeFd, F_GETFL, 0);
            fcntl(_writeFd, F_SETFL, flags | O_NONBLOCK);
        }

        _readFd = open(_readPipePath.c_str(), O_RDONLY | O_NONBLOCK);
        if (_readFd < 0) {
            std::cerr << "Failed to open read FIFO: " << strerror(errno) << std::endl;
            ::close(_writeFd);
            _writeFd = -1;
            return false;
        }
    }

    _pollFd.fd = _readFd;
    _pollFd.events = POLLIN;

    return true;
}

bool FifoIPCChannel::send(const std::string &message)
{
    if (!isValid()) {
        std::cerr << "Cannot send, channel is not valid" << std::endl;
        return false;
    }

    signal(SIGPIPE, SIG_IGN);

    uint32_t length = message.length();

    int oldFlags = fcntl(_writeFd, F_GETFL);
    fcntl(_writeFd, F_SETFL, oldFlags & ~O_NONBLOCK);

    ssize_t headerWritten = 0;
    ssize_t bytesRemaining = sizeof(length);
    char* headerPtr = reinterpret_cast<char*>(&length);

    while (bytesRemaining > 0) {
        ssize_t result = ::write(_writeFd, headerPtr + headerWritten, bytesRemaining);
        if (result < 0) {
            if (errno == EINTR)
                continue;
            fcntl(_writeFd, F_SETFL, oldFlags);
            _isConnected = false;
            return false;
        } else if (result == 0) {
            std::cerr << "Write returned 0 bytes (pipe closed)" << std::endl;
            fcntl(_writeFd, F_SETFL, oldFlags);
            _isConnected = false;
            return false;
        }

        headerWritten += result;
        bytesRemaining -= result;
    }
    ssize_t written = 0;
    bytesRemaining = message.length();
    const char* msgPtr = message.c_str();

    while (bytesRemaining > 0) {
        ssize_t result = ::write(_writeFd, msgPtr + written, bytesRemaining);
        if (result < 0) {
            if (errno == EINTR)
                continue;
            std::cerr << "Data write error: " << strerror(errno) << std::endl;
            fcntl(_writeFd, F_SETFL, oldFlags);
            _isConnected = false;
            return false;
        } else if (result == 0) {
            std::cerr << "Write returned 0 bytes (pipe closed)" << std::endl;
            fcntl(_writeFd, F_SETFL, oldFlags);
            _isConnected = false;
            return false;
        }

        written += result;
        bytesRemaining -= result;
    }

    fcntl(_writeFd, F_SETFL, oldFlags);
    return true;
}

std::string FifoIPCChannel::receive()
{
    if (!isValid())
        return "";

    int flags = fcntl(_readFd, F_GETFL, 0);
    int oldFlags = flags;
    if (flags & O_NONBLOCK)
        fcntl(_readFd, F_SETFL, flags & ~O_NONBLOCK);

    uint32_t length;
    ssize_t headerRead = ::read(_readFd, &length, sizeof(length));

    fcntl(_readFd, F_SETFL, oldFlags);

    if (headerRead != sizeof(length)) {
        if (headerRead < 0) {
            std::cerr << "Header read error: " << strerror(errno) << std::endl;
            if (errno == EAGAIN || errno == EWOULDBLOCK)
                return "";

            _isConnected = false;
            return "";
        }
        if (headerRead == 0) {
            std::cerr << "Header read zero bytes (pipe closed)" << std::endl;
            _isConnected = false;
            return "";
        }

        std::cerr << "Incomplete header read" << std::endl;
        return "";
    }

    if (length > 10000) {
        std::cerr << "Message length too large: " << length << std::endl;
        return "";
    }

    if (oldFlags & O_NONBLOCK)
        fcntl(_readFd, F_SETFL, oldFlags & ~O_NONBLOCK);

    std::string message;
    message.resize(length);

    ssize_t bytesRead = ::read(_readFd, &message[0], length);

    fcntl(_readFd, F_SETFL, oldFlags);

    if (bytesRead != static_cast<ssize_t>(length)) {
        if (bytesRead < 0) {
            std::cerr << "Data read error: " << strerror(errno) << std::endl;
            _isConnected = false;
            return "";
        }

        if (bytesRead == 0) {
            std::cerr << "Data read zero bytes (pipe closed)" << std::endl;
            _isConnected = false;
            return "";
        }

        std::cerr << "Incomplete data read, got "
                  << bytesRead
                  << " of "
                  << length
                  << " bytes" << std::endl;
        return message.substr(0, bytesRead);
    }

    return message;
}

bool FifoIPCChannel::hasData(int timeoutMs)
{
    if (!isValid())
        return false;

    _pollFd.fd = _readFd;
    _pollFd.events = POLLIN;
    _pollFd.revents = 0;

    int result = poll(&_pollFd, 1, timeoutMs);

    if (result > 0) {
        if (_pollFd.revents & (POLLHUP | POLLERR | POLLNVAL)) {
            if (_pollFd.revents & POLLHUP) {
                _isConnected = false;
                return false;
            }
            std::cerr << "Poll error: ";
            if (_pollFd.revents & POLLERR)
                std::cerr << "POLLERR ";
            if (_pollFd.revents & POLLNVAL)
                std::cerr << "POLLNVAL ";
            std::cerr << std::endl;

            _isConnected = false;
            return false;
        }

        bool hasData = (_pollFd.revents & POLLIN) != 0;
        return hasData;
    } else if (result < 0) {
        std::cerr << "Poll error: " << strerror(errno) << std::endl;
        if (errno != EINTR) {
            _isConnected = false;
        }
        return false;
    }

    return false;
}

void FifoIPCChannel::close()
{
    if (_writeFd >= 0) {
        ::close(_writeFd);
        _writeFd = -1;
    }

    if (_readFd >= 0) {
        ::close(_readFd);
        _readFd = -1;
    }

    if (_mode == Mode::PARENT) {
        unlink(_writePipePath.c_str());
        unlink(_readPipePath.c_str());
    }

    _isConnected = false;
}

bool FifoIPCChannel::isValid() const
{
    return _isConnected && _writeFd >= 0 && _readFd >= 0;
}

}  // namespace Plazza
