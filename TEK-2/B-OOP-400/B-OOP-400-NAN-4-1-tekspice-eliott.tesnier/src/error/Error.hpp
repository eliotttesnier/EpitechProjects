/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** error
*/

#pragma once

#include <exception>
#include <string>

namespace nts {
    class InvalidFile : public std::exception {
        public:
            InvalidFile(const std::string &message) : _message(message) {};
            ~InvalidFile() override = default;

            const char *what() const noexcept override { return _message.c_str(); }

        private:
            std::string _message;
    };

    class InvalidInput : public std::exception {
        public:
            InvalidInput(const std::string &message) : _message(message) {};
            ~InvalidInput() override = default;

            const char *what() const noexcept override { return _message.c_str(); }

        private:
            std::string _message;
    };

    class InvalidArgument : public std::exception {
        public:
            InvalidArgument(const std::string &message) : _message(message) {};
            ~InvalidArgument() override = default;

            const char *what() const noexcept override { return _message.c_str(); }

        private:
            std::string _message;
    };
}
