/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** IEntity
*/

#ifndef IENTITY_HPP_
#define IENTITY_HPP_

#include <memory>
#include <string>

class Player;

class IEntity {
    public:
        virtual ~IEntity() = default;

        virtual void onInteract(std::shared_ptr<Player> player) = 0;

        virtual void setPos(std::pair<double, double> pos) = 0;
        virtual std::pair<double, double> getPos() = 0;
};

#endif /* !IENTITY_HPP_ */
