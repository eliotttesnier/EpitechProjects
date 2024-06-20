/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** AbstractPushable
*/

#pragma once
#include "blocks/platforms/AbstractPlatform.hpp"

class AbstractPushable : public AbstractPlatform {
protected:
    AbstractPushable(sf::Vector2f position, const std::string &texture_path);
    AbstractPushable(const JsonObject *object);
public:
    AbstractPushable(const AbstractPushable &other) = default;
    ~AbstractPushable() override = default;

    AbstractPushable &operator=(const AbstractPushable &other);
};
