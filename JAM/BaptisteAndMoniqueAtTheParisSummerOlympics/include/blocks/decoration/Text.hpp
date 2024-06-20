/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** Text
*/

#pragma once
#include "blocks/decoration/AbstractDecoration.hpp"

class Text : public AbstractDecoration {
protected:
    std::string _str;
    sf::Text _text;
public:
    Text(sf::Vector2f position, const std::string &text);
    Text(const Text &other) = default;
    ~Text() override = default;

    void draw(sf::RenderWindow &window) override;

    void setStr(const std::string& str);
    void setText(sf::Text text);

    std::string getStr();
    sf::Text getText();

    Text &operator=(const Text &other);
};
