/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** AEntity
*/

#ifndef AENTITY_HPP_
#define AENTITY_HPP_

#include "IEntity.hpp"

class Player;

class AEntity : public IEntity {
    protected:
        std::pair<double, double> _pos;
        std::string _asset;

    public:
        virtual ~AEntity() = default;

        virtual void onInteract(std::shared_ptr<Player> player) = 0;

        void setPos(std::pair<double, double> pos) override;
        std::pair<double, double> getPos() override;
};

#endif /* !AENTITY_HPP_ */
