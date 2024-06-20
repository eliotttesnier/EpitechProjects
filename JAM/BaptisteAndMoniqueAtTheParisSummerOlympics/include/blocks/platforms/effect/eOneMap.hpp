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

class EOneMap : public AbstractEffectPlatform {
   public:
    EOneMap() = default;
    EOneMap(sf::Vector2f position, const std::string &texture_path);
    EOneMap(const EOneMap &other) = default;
    EOneMap(const JsonObject *conf);
    ~EOneMap() = default;
    void applyEffect();
    bool hit(sf::Sprite *sprite) override;

    EOneMap &operator=(const EOneMap &other);
};
