/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** AbstractDecoration
*/

#include "blocks/decoration/AbstractDecoration.hpp"

AbstractDecoration::AbstractDecoration(sf::Vector2f position, const std::string &texture_path) : AbstractBlock(position, texture_path)
{ }

AbstractDecoration &AbstractDecoration::operator=(const AbstractDecoration &other) {
    if (&other == this)
        return *this;
    AbstractBlock::operator=(other);
    return *this;
}
