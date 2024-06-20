/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** No file there , just an epitech header example .
*/

#include "CollisionModule.hpp"
#include "DisplayModule.hpp"
#include "MovementModule.hpp"
#include "RotatableModule.hpp"
#include "TimeModule.hpp"
#include "PositionModule.hpp"
#include "HitboxModule.hpp"

class PlayerModule : public Module {
    public:
        PlayerModule(GameObject *gameObject);
        ~PlayerModule() = default;

        void update(GameObject *gameObject, std::vector<GameObject*> gameObjects) override {(void) gameObject, (void) gameObjects;};
    private:
};