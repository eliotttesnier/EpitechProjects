/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "blocks/platforms/effect/AbstractEffectPlatform.hpp"

AbstractEffectPlatform::AbstractEffectPlatform(sf::Vector2f position, const std::string &texture_path) : AbstractPlatform(position, texture_path)
{ }

AbstractEffectPlatform::AbstractEffectPlatform(const JsonObject *object) : AbstractPlatform(object)
{ }

AbstractEffectPlatform &AbstractEffectPlatform::operator=(const AbstractEffectPlatform &other) {
    if (&other == this)
        return *this;
    AbstractPlatform::operator=(other);
    return *this;
}
