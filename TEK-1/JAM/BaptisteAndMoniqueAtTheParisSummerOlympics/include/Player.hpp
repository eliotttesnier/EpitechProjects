/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/


#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

struct Particule {
    float x;
    float y;
    bool will_destroy;
};

class Player {
protected:
    sf::Texture _textureIdle;
    sf::Texture _textureRun;
    sf::IntRect _rectIdle;
    sf::IntRect _rectRun;
    sf::Sprite _sprite;
    sf::Vector2f _position;
    sf::Vector2f _velocity;
    int _player_id;
    sf::Clock _clock;

    sf::Texture _texture_flame;
    sf::Sprite _sprite_flame;
    std::vector<Particule> _array_of_particles;
    sf::Uint8 *_pixels;
    sf::Vector2f _wind;

public:
    explicit Player(int player_id = 0);
    Player(const Player &other) = default;
    ~Player();

    // ---------- Methods ----------
    void right();
    void left();
    void action();
    void jump();
    void update();
    void anim();
    void draw(sf::RenderWindow &window);

    // ---------- Setters ----------
    void setTextureIdle(const std::string &texture_path);
    void setPosition(sf::Vector2f position);
    void setVelocity(sf::Vector2f velocity);

    void moving_particles(std::vector<Particule>& particles, const sf::Vector2f& wind);
    void generate_particles(std::vector<Particule>& particles);
    void buffer_to_pixels(std::vector<Particule>& particles, sf::Uint8 *pixels);

    // ---------- Getters ----------
    sf::Vector2f &getPosition();
    sf::Vector2f &getVelocity();
    sf::Sprite &getSprite();
    sf::Texture &getTextureIdle();

    // ---------- Operator Overloads ----------
    Player &operator=(const Player &other);
};
