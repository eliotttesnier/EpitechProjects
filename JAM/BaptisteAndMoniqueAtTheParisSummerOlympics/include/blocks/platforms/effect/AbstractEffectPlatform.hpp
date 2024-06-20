/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "blocks/platforms/AbstractPlatform.hpp"

class AbstractEffectPlatform : public AbstractPlatform {
protected:
    AbstractEffectPlatform(sf::Vector2f position, const std::string &texture_path);
    AbstractEffectPlatform(const JsonObject *object);
public:
    AbstractEffectPlatform(const AbstractEffectPlatform &other) = default;
    ~AbstractEffectPlatform() override = default;

    // ---------- Methods ----------
    /**
     * @brief Apply the effect of the platform on all player
     * This functions should hold the logic of the player selection and the effect application
     * so not all players are affected by the effect
     */
    virtual void applyEffect() = 0;

    // ---------- Operator Overloads ----------
    AbstractEffectPlatform &operator=(const AbstractEffectPlatform &other);
};
