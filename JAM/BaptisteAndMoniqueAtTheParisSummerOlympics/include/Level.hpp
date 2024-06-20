/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "blocks/AbstractBlock.hpp"
#include "blocks/BlockFactory.hpp"

#define MAP_WIDTH 40
#define MAP_HEIGHT 30

class Level {
protected:
    AbstractBlock **_blocks;
    std::size_t _nbBlocks;
    sf::Texture _skyTexture;
    sf::Sprite _skySprite;
    sf::Vector2f _startPosP1;
    sf::Vector2f _startPosP2;
    sf::Vector2f _endPosP1;
    sf::Vector2f _endPosP2;
    sf::Font _font;
    sf::Text _time;
    sf::Clock _clock;

public:
    Level(const std::string &filePath, const BlockFactory &blockFactory);
    Level(const std::string &skyPath, AbstractBlock **blocks, std::size_t nbBlocks, sf::Vector2f startPosP1, sf::Vector2f startPosP2, sf::Vector2f endPosP1, sf::Vector2f endPosP2);
    Level(const Level& other) = delete;
    ~Level();

    // ---------- Methods ----------
    void draw(sf::RenderWindow *window);
    void update();
    void reset();

    // ---------- Setters ----------
    void setBlocks(AbstractBlock **blocks, std::size_t nbBlocks);
    void setSkyTexture(const sf::Texture& texture);
    void setSkySprite(sf::Sprite sprite);
    void setStartPosP1(sf::Vector2f position);
    void setStartPosP2(sf::Vector2f position);
    void setEndPosP1(sf::Vector2f position);
    void setEndPosP2(sf::Vector2f position);

    // ---------- Getters ----------
    AbstractBlock **getBlocks();
    std::size_t getNbBlocks() const;
    sf::Texture getSkyTexture();
    sf::Sprite getSkySprite();
    AbstractBlock *getBlockAtPos(sf::Vector2f pos);
    sf::Vector2f getStartPosP1();
    sf::Vector2f getStartPosP2();
    sf::Vector2f getEndPosP1();
    sf::Vector2f getEndPosP2();
    sf::Clock &getClock();
};
