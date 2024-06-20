/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "blocks/platforms/AbstractPlatform.hpp"
#include "blocks/movingColor.hpp"

class AbstractMovingPlatform: public AbstractPlatform {
protected:
    sf::Vector2f _start_pos;
    sf::Vector2f _end_pos;
    float _speed;
    bool _should_move;
    MovingColor _color;

    AbstractMovingPlatform(sf::Vector2f start_pos, sf::Vector2f end_pos, float speed, const std::string &texture_path);
    AbstractMovingPlatform(const JsonObject *conf);
public:
    AbstractMovingPlatform(const AbstractMovingPlatform &other) = default;
    ~AbstractMovingPlatform() override = default;

    // ---------- Methods ----------
    void move();
    virtual bool hit(sf::Sprite *sprite) = 0;

    // ---------- Getters ----------
    sf::Vector2f getStartPos() const;
    sf::Vector2f getEndPos() const;
    float getSpeed() const;
    bool getShouldMove() const;
    MovingColor getColor() const;

    // ---------- Setters ----------
    void setStartPos(sf::Vector2f start_pos);
    void setEndPos(sf::Vector2f end_pos);
    void setSpeed(float speed);
    void setShouldMove(bool should_move);

    // ---------- Operator Overloads ----------
    AbstractMovingPlatform &operator=(const AbstractMovingPlatform &other);
};
