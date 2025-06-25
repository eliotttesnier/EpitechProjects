/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** GameState
*/

#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include "../../../include/Coin.hpp"
#include "../../../include/Obstacle.hpp"
#include "../../../include/Player.hpp"
#include "../entities/IEntity.hpp"
#include "../entities/ElectricEntity.hpp"
#include "../entities/CoinEntity.hpp"
#include "../Player.hpp"

#include <map>

class GameState
{
    private:
        float _playerPosX;

        std::map<std::size_t, std::shared_ptr<Player>> _playersEntities;
        std::vector<player_t> _players;
        std::vector<coinsPos_t> _coins;
        std::vector<obstacle_t> _electricity;

    public:
        GameState(std::vector<std::shared_ptr<Player>> players,
                  std::vector<std::vector<std::shared_ptr<IEntity>>> map);
        ~GameState();

        std::vector<player_t> getPlayers() const;
        std::vector<coinsPos_t> getCoins();
        std::vector<coinsPos_t> getPlayerNotCollectedCoins(int id);
        std::vector<obstacle_t> getElectricity();
};

#endif /* !GAMESTATE_HPP_ */
