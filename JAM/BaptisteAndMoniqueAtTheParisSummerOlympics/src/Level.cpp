/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <utility>
#include "Level.hpp"
#include "Game.hpp"
#include <iostream>

#include <iostream>

#define BLOCK_WIDTH ((float) WINDOW_WIDTH / MAP_WIDTH)
#define BLOCK_HEIGHT ((float) WINDOW_HEIGHT / MAP_HEIGHT)

Level::Level(const std::string &filePath, const BlockFactory &blockFactory)
{
    auto json = JsonObject::parseFile(filePath);
    auto blocks = json.getValue<JsonArray>("blocks");
    std::string skyPath = json.getString("sky");
    _skyTexture = sf::Texture();
    _skyTexture.loadFromFile(skyPath);
    _skySprite = sf::Sprite(_skyTexture);
    _skySprite.setScale({3.0f, 3.0f});
    _nbBlocks = blocks->size();

    _blocks = new AbstractBlock*[_nbBlocks];
    for (std::size_t i = 0; i < _nbBlocks; i++) {
        auto block = blocks->getValue<JsonObject>(i);
        _blocks[i] = blockFactory(block);
    }
    auto startPosP1 = json.getValue<JsonObject>("start_posP1");
    auto startPosP2 = json.getValue<JsonObject>("start_posP2");
    auto endPosP1 = json.getValue<JsonObject>("end_posP1");
    auto endPosP2 = json.getValue<JsonObject>("end_posP2");
    _startPosP1 = {static_cast<float>(startPosP1->getFloat("x")) * 33, static_cast<float>(startPosP1->getFloat("y")) * 33};
    _startPosP2 = {static_cast<float>(startPosP2->getFloat("x")) * 33, static_cast<float>(startPosP2->getFloat("y")) * 33};
    _endPosP1 = {static_cast<float>(endPosP1->getFloat("x")) * 33, static_cast<float>(endPosP1->getFloat("y")) * 33};
    _endPosP2 = {static_cast<float>(endPosP2->getFloat("x")) * 33, static_cast<float>(endPosP2->getFloat("y")) *33};
    _font.loadFromFile("assets/ASMAN.TTF");
    _time.setCharacterSize(34);
    _time.setFont(_font);
    _time.setFillColor(sf::Color::Black);
    _time.setPosition({1920 / 2 - 50, 30});
    _time.setString("Timer: 0s");
}

Level::Level(const std::string &skyPath, AbstractBlock **blocks, std::size_t nbBlocks, sf::Vector2f startPosP1, sf::Vector2f startPosP2, sf::Vector2f endPosP1, sf::Vector2f endPosP2)
{
    _skyTexture = sf::Texture();
    _skyTexture.loadFromFile(skyPath);
    _skySprite = sf::Sprite(_skyTexture);
    _blocks = blocks;
    _nbBlocks = nbBlocks;
    _startPosP1 = startPosP1;
    _startPosP2 = startPosP2;
    _endPosP1 = endPosP1;
    _endPosP1 = endPosP2;
    _font.loadFromFile("assets/ASMAN.TTF");
    _time.setCharacterSize(34);
    _time.setFont(_font);
    _time.setFillColor(sf::Color::Black);
    _time.setPosition({1920 / 2 - 50, 30});
    _time.setString("Timer: 0s");
}

Level::~Level()
{
    for (std::size_t i = 0; i < _nbBlocks; i++) {
        delete _blocks[i];
    }
}

void Level::draw(sf::RenderWindow *window)
{
    window->draw(_skySprite);
    currentGame->getPlayer1()->draw(*window);
    currentGame->getPlayer2()->draw(*window);
    for (std::size_t i = 0; i < _nbBlocks; i++) {
        if (_blocks[i] != nullptr)
            _blocks[i]->draw(*window);
    }
    _time.setString("Timer: " + std::to_string((int)_clock.getElapsedTime().asSeconds()) + "s");
    window->draw(_time);
}

void Level::reset()
{
    currentGame->getPlayer1()->setPosition(currentGame->getCurrentLevel()->getStartPosP1());
    currentGame->getPlayer2()->setPosition(currentGame->getCurrentLevel()->getStartPosP2());
    currentGame->getMusic().stop();
    currentGame->getMusic().play();
    currentGame->getCurrentLevel()->getClock().restart();
}

void Level::update()
{
}

void Level::setBlocks(AbstractBlock **blocks, std::size_t nbBlocks)
{
    for (std::size_t i = 0; i < _nbBlocks; i++) {
        delete _blocks[i];
    }
    _blocks = blocks;
    _nbBlocks = nbBlocks;
}

void Level::setSkyTexture(const sf::Texture& texture)
{
    _skyTexture = texture;
}

void Level::setSkySprite(sf::Sprite sprite)
{
    _skySprite = std::move(sprite);
}

void Level::setStartPosP1(sf::Vector2f position)
{
    _startPosP1 = position;
}

void Level::setStartPosP2(sf::Vector2f position)
{
    _startPosP2 = position;
}

void Level::setEndPosP1(sf::Vector2f position)
{
    _endPosP1 = position;
}

void Level::setEndPosP2(sf::Vector2f position)
{
    _endPosP2 = position;
}

AbstractBlock **Level::getBlocks()
{
    return _blocks;
}

AbstractBlock *Level::getBlockAtPos(sf::Vector2f position)
{
    if (position.x < 0 || position.y < 0 || position.x > WINDOW_WIDTH || position.y > WINDOW_HEIGHT)
        return nullptr;
    for (std::size_t i = 0; i < _nbBlocks; i++) {
        if (_blocks[i] == nullptr)
            continue;
        if (position.x >= _blocks[i]->getPosition().x && position.x <= _blocks[i]->getPosition().x + BLOCK_WIDTH &&
            position.y >= _blocks[i]->getPosition().y && position.y <= _blocks[i]->getPosition().y + BLOCK_HEIGHT)
            return _blocks[i];
    }
    return nullptr;
}

std::size_t Level::getNbBlocks() const
{
    return _nbBlocks;
}

sf::Texture Level::getSkyTexture()
{
    return _skyTexture;
}

sf::Sprite Level::getSkySprite()
{
    return _skySprite;
}

sf::Vector2f Level::getStartPosP1()
{
    return _startPosP1;
}

sf::Vector2f Level::getStartPosP2()
{
    return _startPosP2;
}

sf::Vector2f Level::getEndPosP1()
{
    return _endPosP1;
}

sf::Vector2f Level::getEndPosP2()
{
    return _endPosP2;
}

sf::Clock &Level::getClock()
{
    return _clock;
}
