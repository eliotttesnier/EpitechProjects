/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Player.hpp"
#include "Game.hpp"
#include "blocks/platforms/AbstractPlatform.hpp"
#include <ctime>
#include <cmath>
#include <iostream>

const int WIDTH = 100;
const int HEIGHT = 250;
const int PPT = 50;
int z = WIDTH / 2;
int zz = HEIGHT / 2;

#include <iostream>

Player::Player(int player_id)
{
    _player_id = player_id;
    _position = {0.0f, 0.0f};
    _velocity = {0.0f, 0.0f};
    _wind = {0.f, 0.f};
    _clock = sf::Clock();
    _textureIdle = sf::Texture();
    if (_player_id == 0) {
        _textureIdle.loadFromFile("assets/player/BaptisteIdle(23x84).png");
        _rectIdle = (sf::IntRect){0, 0, 23, 84};
        _textureRun.loadFromFile("assets/player/BaptisteRun(45x84).png");
        _rectRun = (sf::IntRect){0, 0, 45, 84};
    } else {
        _textureIdle.loadFromFile("assets/player/TorchIdle(18x47).png");
        _rectIdle = (sf::IntRect){0, 0, 18, 47};
        _textureRun.loadFromFile("assets/player/TorchRun(18x47).png");   // TODO : Update texture for P2
        _rectRun = (sf::IntRect){0, 0, 18, 47};

        _pixels = new sf::Uint8[WIDTH * HEIGHT * 4];
        _texture_flame.create(WIDTH, HEIGHT);
        _sprite_flame = sf::Sprite(_texture_flame);
        _sprite_flame.setPosition(0, 0);
    }
    _sprite = sf::Sprite(_textureIdle);
    _sprite.setTextureRect(_rectIdle);
    _sprite.setOrigin({_rectIdle.width / 2.f, _rectIdle.height / 2.f});
    _sprite.setScale({1.0f, 1.0f});
}

Player::~Player() {
    delete[] _pixels;
}

void Player::right()
{
    // Fetch block on the right
    AbstractBlock *block = currentGame->getCurrentLevel()->getBlockAtPos({_position.x + 33.0f, _position.y});

    _sprite.setScale({1, 1});
    // If there is no block on the right
    if (block == nullptr) {
        _velocity.x += 0.4f;
    } else {
        // If the block is a platform
        if (dynamic_cast<AbstractPlatform *>(block) != nullptr) {
            bool isHit = dynamic_cast<AbstractPlatform *>(block)->hit({&_sprite});
            if (!isHit) { // If the platform is not hit (not colliding)
                _velocity.x += 0.2f; // Move the player
            }
        }
    }
}

void Player::left()
{
    // Fetch block on the left
    AbstractBlock *block = currentGame->getCurrentLevel()->getBlockAtPos({_position.x - 33.0f, _position.y});

    _sprite.setScale({-1, 1});
    // If there is no block on the left
    if (block == nullptr) {
        _velocity.x -= 0.4f;
    } else {
        // If the block is a platform
        if (dynamic_cast<AbstractPlatform *>(block) != nullptr) {
            bool isHit = dynamic_cast<AbstractPlatform *>(block)->hit({&_sprite});
            if (!isHit) { // If the platform is not hit (not colliding)
                _velocity.x -= 0.2f; // Move the player
            }
        }
    }
}

void Player::anim()
{
    float time = _clock.getElapsedTime().asSeconds();
    bool moving = false;

    if (_velocity.x == 0) {
        _sprite.setTexture(_textureIdle);
        _sprite.setTextureRect(_rectIdle);
        _sprite.setOrigin({_rectIdle.width / 2.f, _rectIdle.height / 2.f});
    } else {
         _sprite.setTexture(_textureRun);
        _sprite.setTextureRect(_rectRun);
        _sprite.setOrigin({_rectRun.width / 2.f, _rectRun.height / 2.f});
        moving = true;
    }
    if (time > 0.1) {
        _clock.restart();
        if (moving) {
            _rectRun.left += _rectRun.width;
             _rectRun.left = (_rectRun.left >= _rectRun.width * 8 ? 0 : _rectRun.left);
            _sprite.setTextureRect(_rectRun);
        } else {
            _rectIdle.left += _rectIdle.width;
            _rectIdle.left = (_rectIdle.left >= _rectIdle.width * 7 ? 0 : _rectIdle.left);
            _sprite.setTextureRect(_rectIdle);
        }
        if (_player_id == 1) {
            _wind = {0.f + _velocity.x * - 10.f, 0.f + _velocity.y};
            generate_particles(_array_of_particles);
            moving_particles(_array_of_particles, _wind);
            for (int i = 0; i < WIDTH * HEIGHT * 4; i++) {
                _pixels[i] = 0;
            }
        }
    }
}

void Player::action()
{
    //TODO Fetch block and check if type is actionnable then call action
}

void Player::jump()
{
    // Fetch block on the top and right under the player
    AbstractBlock *ceiling = currentGame->getCurrentLevel()->getBlockAtPos({_position.x, _position.y - 33.0f});
    AbstractBlock *ground = currentGame->getCurrentLevel()->getBlockAtPos({_position.x, _position.y + 33.0});

    // If there is no block under the player, or it's not a platform
    // then the player can't jump
    if (ground == nullptr || dynamic_cast<AbstractPlatform *>(ground) == nullptr) {
        return;
    }
    // If there is a block on the top and it's a platform
    if (ceiling != nullptr && dynamic_cast<AbstractPlatform *>(ceiling) != nullptr) {
        // If the platform is hit (colliding)
        if (dynamic_cast<AbstractPlatform *>(ceiling)->hit({&_sprite}))
            return;
    }
    // If the player can jump
    _velocity.y = -3.5f;
}

void Player::update()
{
    _position += _velocity;
    _sprite.setPosition(_position);
    _velocity = {0.0f, _velocity.y + 0.04f};
    // _velocity.y = 0;

    if (_velocity.y > 0.5f)
        _velocity.y = 0.5f;
    // Check if the player is on the ground
    AbstractBlock *block = currentGame->getCurrentLevel()->getBlockAtPos({_position.x, _position.y + 33.0f});
    if (block != nullptr && dynamic_cast<AbstractPlatform *>(block) != nullptr) {
        bool isHit = dynamic_cast<AbstractPlatform *>(block)->hit({&_sprite});
        if (isHit) {
            _velocity.y = 0;
        }
    }
    if (_player_id == 1) {
        _sprite_flame.setPosition(_position + (sf::Vector2f){-50.f, -140.f});
    }
}

void Player::draw(sf::RenderWindow &window)
{
    window.draw(_sprite);
    if (_player_id == 1)
        window.draw(_sprite_flame);
}

sf::Vector2f &Player::getPosition()
{
    return (_position);
}

sf::Sprite &Player::getSprite()
{
    return (_sprite);
}

sf::Texture &Player::getTextureIdle()
{
    return (_textureIdle);
}

sf::Vector2f &Player::getVelocity()
{
    return (_velocity);
}

void Player::setPosition(sf::Vector2f position)
{
    _position = position;
}

void Player::setTextureIdle(const std::string &texture_path)
{
    _textureIdle = sf::Texture();
    _textureIdle.loadFromFile(texture_path);
}

void Player::setVelocity(sf::Vector2f velocity)
{
    _velocity = velocity;
}

Player &Player::operator=(const Player &other) {
    if (&other == this)
        return *this;
    this->_position = other._position;
    this->_velocity = other._velocity;
    this->_player_id = other._player_id;
    this->_sprite = other._sprite;
    this->_textureIdle = other._textureIdle;
    this->_rectIdle = other._rectIdle;
    this->_textureRun = other._textureRun;
    this->_rectRun = other._rectRun;
    return *this;
}

static sf::Vector2f generate_pos_in_circle(float radius)
{
    double theta = 2.0 * M_PI * (float)std::rand() / RAND_MAX;
    double x = (float)std::rand() / (float)RAND_MAX * radius * cos(theta);
    double y = (float)std::rand() / (float)RAND_MAX * radius * sin(theta);
    return {(float) x, (float) y};
}

void Player::generate_particles(std::vector<Particule>& particles)
{
    std::size_t particles_to_generate = PPT + std::rand() % 80 - 40;
    for (std::size_t i = 0; i < particles_to_generate; i++) {
        Particule adding_part{};
        sf::Vector2f pos = generate_pos_in_circle(10.f);
        adding_part.x = pos.x + z;
        adding_part.y = pos.y + zz;
        particles.push_back(adding_part);
    }

    buffer_to_pixels(_array_of_particles, _pixels);
    _texture_flame.update(_pixels);
}

void Player::moving_particles(std::vector<Particule>& particles, const sf::Vector2f& wind)
{
    for (auto &particle: particles) {
        sf::Vector2f vector(0, -2.f);
        int move = std::rand() % 100;
        if (move < 20) {
            vector.x = -1;
        } else if (move > 80) {
            vector.x = 1;
        }
        vector += wind;
        particle.x += vector.x;
        particle.y += vector.y;

        //killing particles
        if (std::rand() % 100 / 100.f < 0.06f) {
            particle.will_destroy = true;
        }
    }
    particles.erase(std::remove_if(particles.begin(), particles.end(), [](Particule& particle) {return particle.will_destroy;}), particles.end());
}

static std::size_t sampleParticles(const std::vector<Particule>& particles, const sf::Vector2f& pos, float radius)
{
    std::size_t count = 0;
    for (const auto& particle: particles) {
        sf::Vector2f particle_pos = {particle.x, particle.y};
        float dist = std::sqrt(std::pow(particle_pos.x - pos.x, 2) + std::pow(particle_pos.y - pos.y, 2));
        if (dist < radius) {
            count++;
        }
    }
    return count;
}

void Player::buffer_to_pixels(std::vector<Particule>& particles, sf::Uint8 *pixels)
{
#pragma omp parallel for
    for (std::size_t y = 0; y < HEIGHT; y++) {
        for (std::size_t x = 0; x < WIDTH; x++) {
            sf::Vector2f pos = {(float) x, (float) y};
            std::size_t count = sampleParticles(particles, pos, 4.f);
            float ratio = std::sqrt(count / 120.f);
            float value = 255.f * ratio;
            value *= 1.1f;
            value = std::clamp(value, 0.f, 255.f);
            pixels[(x + y * WIDTH) * 4] = value;
            pixels[(x + y * WIDTH) * 4 + 1] = value / 2.f;
            pixels[(x + y * WIDTH) * 4 + 2] = 0;
            pixels[(x + y * WIDTH) * 4 + 3] = value * 0.8f;
        }
    }
}
