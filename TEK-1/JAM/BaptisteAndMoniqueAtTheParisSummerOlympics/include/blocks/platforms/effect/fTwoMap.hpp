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

class FTwoMap : public AbstractEffectPlatform {
   public:
    FTwoMap() = default;
    FTwoMap(sf::Vector2f position, const std::string &texture_path);
    FTwoMap(const FTwoMap &other) = default;
    FTwoMap(const JsonObject *conf);
    ~FTwoMap() = default;
    void applyEffect();
    bool hit(sf::Sprite *sprite) override;

    FTwoMap &operator=(const FTwoMap &other);
};
