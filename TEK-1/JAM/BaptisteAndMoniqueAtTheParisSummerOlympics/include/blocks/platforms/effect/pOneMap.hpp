/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "blocks/platforms/effect/AbstractEffectPlatform.hpp"
#include "Game.hpp"

class POneMap : public AbstractEffectPlatform {
   public:
    POneMap() = default;
    POneMap(sf::Vector2f position, const std::string &texture_path);
    POneMap(const POneMap &other) = default;
    POneMap(const JsonObject *conf);
    ~POneMap() = default;
    void applyEffect();
    bool hit(sf::Sprite *sprite) override;

    POneMap &operator=(const POneMap &other);
};
