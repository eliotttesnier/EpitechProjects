/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** AbstractPushable
*/

#include "blocks/platforms/pushable/AbstractPushable.hpp"

AbstractPushable::AbstractPushable(sf::Vector2f position, const std::string &texture_path) : AbstractPlatform(position, texture_path)
{}

AbstractPushable::AbstractPushable(const JsonObject *object) : AbstractPlatform(object)
{}

AbstractPushable &AbstractPushable::operator=(const AbstractPushable &other) {
    if (&other == this)
        return *this;
    AbstractPlatform::operator=(other);
    return *this;
}
