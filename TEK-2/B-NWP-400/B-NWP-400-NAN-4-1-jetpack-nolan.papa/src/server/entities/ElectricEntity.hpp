/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** ElectricEntity
*/

#ifndef ELECTRICENTITY_HPP_
#define ELECTRICENTITY_HPP_

#include "AEntity.hpp"
#include "Player.hpp"
class ElectricEntity : public AEntity {
    public:
        ElectricEntity(std::pair<int, int> pos);
        ~ElectricEntity() = default;

        void onInteract(std::shared_ptr<Player> player) override;
};

#endif /* !ELECTRICENTITY_HPP_ */
