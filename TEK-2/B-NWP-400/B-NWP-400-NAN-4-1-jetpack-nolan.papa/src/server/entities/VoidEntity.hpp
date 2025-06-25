/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** VoidEntity
*/

#ifndef VOIDENTITY_HPP_
#define VOIDENTITY_HPP_

#include "AEntity.hpp"
#include "Player.hpp"
class VoidEntity : public AEntity {
    public:
        VoidEntity(std::pair<int, int> pos);
        ~VoidEntity() = default;

        void onInteract(std::shared_ptr<Player> player) override;
};

#endif /* !VOIDENTITY_HPP_ */
