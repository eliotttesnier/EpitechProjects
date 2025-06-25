/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** Exceptions
*/

#pragma once

#include <exception>
#include <string>

namespace Exceptions {
    /**
     * @brief Base exception class for CLI parsing errors
     */
    class CLIParsingException : public std::exception {
        public:
            /**
             * @brief Constructor with error message
             * @param message The error message
             */
            CLIParsingException(const std::string &message) : _message(message) {}

            /**
             * @brief Get the error message
             * @return const char* The error message
             */
            const char* what() const noexcept override {
                return _message.c_str();
            }

        private:
            std::string _message;
    };

    /**
     * @brief Exception for invalid number of arguments
     */
    class InvalidArgumentCountException : public CLIParsingException {
        public:
            InvalidArgumentCountException()
                : CLIParsingException("Invalid number of arguments") {}
    };

    /**
     * @brief Exception for invalid multiplier value
     */
    class InvalidMultiplierException : public CLIParsingException {
        public:
            InvalidMultiplierException(const std::string &value)
                : CLIParsingException("Invalid multiplier value: " + value + ". Must be a float >= 0.0") {}
    };

    /**
     * @brief Exception for invalid cooks per kitchen value
     */
    class InvalidCooksException : public CLIParsingException {
        public:
            InvalidCooksException(const std::string &value)
                : CLIParsingException("Invalid cooks per kitchen value: " + value + ". Must be a positive integer (>= 1)") {}
    };

    /**
     * @brief Exception for invalid regeneration time value
     */
    class InvalidRegenerationTimeException : public CLIParsingException {
        public:
            InvalidRegenerationTimeException(const std::string &value)
                : CLIParsingException("Invalid regeneration time value: " + value +
                                      ". Must be a positive integer (>= 1) in milliseconds") {}
    };
}
