/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "blocks/AbstractBlock.hpp"

class AbstractPlatform : public AbstractBlock {
protected:
    AbstractPlatform(sf::Vector2f position, const std::string &texture_path);
    AbstractPlatform(const JsonObject *object);
public:
    AbstractPlatform(const AbstractPlatform &other) = default;
    ~AbstractPlatform() override = default;

    // ---------- Methods ----------
    virtual bool hit(sf::Sprite *sprite) = 0;

    // ---------- Operator Overloads ----------
    AbstractPlatform &operator=(const AbstractPlatform &other);
};
