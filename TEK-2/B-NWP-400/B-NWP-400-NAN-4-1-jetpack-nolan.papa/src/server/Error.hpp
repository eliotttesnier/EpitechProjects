/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <iostream>
#include <exception>

class InvalidMap : public std::exception {
    public:
        InvalidMap(const std::string &message) : _message(message) {}
        ~InvalidMap() = default;

        const char *what() const noexcept override { return _message.c_str(); }

    private:
        std::string _message;
};


#endif /* !ERROR_HPP_ */
