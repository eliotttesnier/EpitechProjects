/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** Text
*/

#include <utility>

#include "blocks/decoration/Text.hpp"

Text::Text(sf::Vector2f position, const std::string &text): AbstractDecoration(position, "")
{
    this->_str = text;
    this->_text.setString(text);
}

void Text::draw(sf::RenderWindow &window)
{
    window.draw(this->_text);
}

void Text::setStr(const std::string& str)
{
    this->_str = str;
    this->_text.setString(str);
}

void Text::setText(sf::Text text)
{
    this->_text = std::move(text);
}

std::string Text::getStr()
{
    return this->_str;
}

sf::Text Text::getText()
{
    return this->_text;
}

Text &Text::operator=(const Text &other)
{
    if (&other == this)
        return *this;
    AbstractDecoration::operator=(other);
    this->_str = other._str;
    this->_text = other._text;
    return *this;
}
