/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <iostream>
#include <vector>
#include <memory>

#include "entities/CoinEntity.hpp"

class CoinEntity;

class Player {
    public:
        Player(std::string username, int id);
        ~Player() = default;

        // Getters
        void setPos(std::pair<double, double> pos);
        void setUsername(std::string username);
        void setId(int id);
        void setAlive(bool isAlive);
        void setJetpackActivated(bool isJetpackActivated);
        void setVelocity(std::pair<double, double> velocity);

        // Setters
        std::pair<double, double> getPos();
        std::pair<int, int> getGridPos();
        std::string getUsername();
        int getId();
        bool isAlive();
        bool isJetpackActivated();
        std::vector<std::shared_ptr<CoinEntity>> getCoinsCollected();
        std::pair<double, double> getVelocity();

        // Methods
        void collectCoin(std::shared_ptr<CoinEntity> coin);
        void die();
        void respawn();
        void applyForce(double x, double y);
        void updatePosition(double deltaTime);

    private:
        std::string _username;
        int _id;
        bool _isAlive;
        bool _isJetpackActivated;
        std::pair<double, double> _pos;
        std::pair<double, double> _velocity;
        std::vector<std::shared_ptr<CoinEntity>> _coinsCollected;
};

#endif /* !PLAYER_HPP_ */
