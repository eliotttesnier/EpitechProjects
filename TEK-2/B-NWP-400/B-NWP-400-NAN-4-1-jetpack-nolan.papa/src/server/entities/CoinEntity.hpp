/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** CoinEntity
*/

#ifndef COINENTITY_HPP_
#define COINENTITY_HPP_

#include "AEntity.hpp"
#include "Player.hpp"

class CoinEntity : public AEntity {
    public:
        CoinEntity(std::pair<int, int> pos);
        ~CoinEntity() = default;

        void onInteract(std::shared_ptr<Player> player) override;
};

#endif /* !COINENTITY_HPP_ */
