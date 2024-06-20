/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "blocks/decoration/Foliage.hpp"

Foliage::Foliage(sf::Vector2f position, const std::string &texture_path) : AbstractDecoration(position, texture_path)
{
}

Foliage &Foliage::operator=(const Foliage &other)
{
    if (&other == this)
        return *this;
    AbstractBlock::operator=(other);
    return *this;
}
