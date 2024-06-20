/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "blocks/platforms/moving/AbstractMovingPlatform.hpp"
#include <iostream>
#include <cmath>

AbstractMovingPlatform::AbstractMovingPlatform(sf::Vector2f start_pos, sf::Vector2f end_pos, float speed, const std::string &texture_path) : AbstractPlatform(start_pos, texture_path)
{
    _should_move = false;
    _start_pos = start_pos;
    _end_pos = end_pos;
    _speed = speed;
}

AbstractMovingPlatform::AbstractMovingPlatform(const JsonObject *conf) : AbstractPlatform(conf)
{
    _should_move = false;
    JsonObject *data = conf->getValue<JsonObject>("data");
    _start_pos = (sf::Vector2f){static_cast<float>(data->getValue<JsonObject>("start_pos")->getFloat("x")), static_cast<float>(data->getValue<JsonObject>("start_pos")->getFloat("y"))};
    _end_pos = (sf::Vector2f){static_cast<float>(data->getValue<JsonObject>("end_pos")->getFloat("x")), static_cast<float>(data->getValue<JsonObject>("end_pos")->getFloat("y"))};
    _speed = data->getFloat("speed");
    if (data->getString("color") == "red") {
        _color = MovingColor::RED;
    } else if (data->getString("color") == "blue") {
        _color = MovingColor::BLUE;
    } else if (data->getString("color") == "green") {
        _color = MovingColor::GREEN;
    } else if (data->getString("color") == "yellow") {
        _color = MovingColor::YELLOW;
    } else if (data->getString("color") == "purple") {
        _color = MovingColor::PURPLE;
    } else if (data->getString("color") == "white") {
        _color = MovingColor::WHITE;
    } else {
        std::cerr << "Error: invalid color" << std::endl;
    }
}

void AbstractMovingPlatform::setEndPos(sf::Vector2f endpos)
{
    _end_pos = endpos;
}

void AbstractMovingPlatform::setStartPos(sf::Vector2f startpos)
{
    _start_pos = startpos;
}

void AbstractMovingPlatform::setSpeed(float speed)
{
    _speed = speed;
}

void AbstractMovingPlatform::setShouldMove(bool shouldmove)
{
    _should_move = shouldmove;
}

sf::Vector2f AbstractMovingPlatform::getStartPos() const
{
    return _start_pos;
};

sf::Vector2f AbstractMovingPlatform::getEndPos() const
{
    return _end_pos;
};

float AbstractMovingPlatform::getSpeed() const
{
    return _speed;
};

bool AbstractMovingPlatform::getShouldMove() const
{
    return _should_move;
};

MovingColor AbstractMovingPlatform::getColor() const
{
    return _color;
};

void AbstractMovingPlatform::move()
{
    static float resx = 0.0f;
    static float resy = 0.0f;

    std::lerp(_start_pos.x, _end_pos.x, resx);
    if (_should_move && resx < 1.0f) {
        resx += 0.01f;
    } else if (!_should_move && resx > 0.0f) {
        resx -= 0.01f;
    }
    std::lerp(_start_pos.y, _end_pos.y, resy);
    if (_should_move && resy < 1.0f) {
        resy += 0.01f;
    } else if (!_should_move && resy > 0.0f) {
        resy -= 0.01f;
    }
    _position = (sf::Vector2f){resx, resy};
}

AbstractMovingPlatform &AbstractMovingPlatform::operator=(const AbstractMovingPlatform &other) {
    if (&other == this)
        return *this;
    AbstractPlatform::operator=(other);
    return *this;
}
