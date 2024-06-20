/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** AbstractCollecitble
*/

#pragma once
#include "blocks/AbstractBlock.hpp"

class AbstractCollectible : public AbstractBlock{
    protected:
        bool _hasBeenCollected{};

        AbstractCollectible(sf::Vector2f position, const std::string &texture_path);
        AbstractCollectible(const JsonObject *object);
    public:
        AbstractCollectible(const AbstractCollectible &other) = default;
        ~AbstractCollectible() override = default;

        void setCollected(bool collected);

        bool getCollected() const;
        AbstractCollectible &operator=(const AbstractCollectible &other);
};
