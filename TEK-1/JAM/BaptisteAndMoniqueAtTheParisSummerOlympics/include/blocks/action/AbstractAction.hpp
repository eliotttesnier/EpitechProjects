/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "blocks/platforms/moving/AbstractMovingPlatform.hpp"

class AbstractAction : public AbstractBlock {
    protected:
        AbstractMovingPlatform *_movingPlatform;
        AbstractAction(sf::Vector2f position, const std::string &texture_path, AbstractMovingPlatform *movingPlatform);
        AbstractAction(const JsonObject *conf);
    public:
        virtual ~AbstractAction() override = default;
        virtual void execute() = 0;
};
