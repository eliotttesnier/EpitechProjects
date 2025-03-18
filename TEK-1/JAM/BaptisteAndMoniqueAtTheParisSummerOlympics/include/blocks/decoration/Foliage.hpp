/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once

#include "AbstractDecoration.hpp"

class Foliage : public AbstractDecoration {
public:
    Foliage(sf::Vector2f position, const std::string &texture_path);
    ~Foliage() override = default;
    Foliage(const Foliage &other) = default;

    // ---------- Methods ----------

    // ---------- Operator Overloads ----------
    Foliage &operator=(const Foliage &other);
};
