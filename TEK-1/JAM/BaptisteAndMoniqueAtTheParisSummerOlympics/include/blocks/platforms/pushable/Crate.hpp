/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "blocks/platforms/pushable/AbstractPushable.hpp"

class Crate : public AbstractPushable {
protected:
public:
    Crate() = default;
    Crate(sf::Vector2f position, const std::string &texture_path);
    Crate(const JsonObject *conf);
    ~Crate() override = default;

    // ---------- Methods ----------
    bool hit(sf::Sprite *sprite) override;
};
