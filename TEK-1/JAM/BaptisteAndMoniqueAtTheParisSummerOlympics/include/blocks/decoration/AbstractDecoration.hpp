/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** AbstractDecoration
*/

#pragma once
#include "blocks/AbstractBlock.hpp"

class AbstractDecoration : public AbstractBlock {
protected:
    AbstractDecoration(sf::Vector2f position, const std::string &texture_path);
public:
    AbstractDecoration(const AbstractDecoration &other) = default;
    ~AbstractDecoration() override = default;

    AbstractDecoration &operator=(const AbstractDecoration &other);
};
