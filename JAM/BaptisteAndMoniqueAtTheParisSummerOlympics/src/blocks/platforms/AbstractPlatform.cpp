/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "blocks/platforms/AbstractPlatform.hpp"

AbstractPlatform::AbstractPlatform(sf::Vector2f position, const std::string &texture_path) : AbstractBlock(position, texture_path)
{ }

AbstractPlatform::AbstractPlatform(const JsonObject *object) : AbstractBlock(object)
{ }

AbstractPlatform &AbstractPlatform::operator=(const AbstractPlatform &other) {
    if (&other == this)
        return *this;
    AbstractBlock::operator=(other);
    return *this;
}
