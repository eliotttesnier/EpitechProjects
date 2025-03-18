/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** No file there , just an epitech header example .
*/

#include "../Game/GameObject.hpp"
#include "HitboxModule.hpp"
#include "functional"

class EventModule : public Module {
    public:
        EventModule(GameObject *gameObject);
        ~EventModule() = default;

        void update(GameObject *gameObject, std::vector<GameObject*> gameObjects) override;
        void setEventEffect(GameObject *gameobject, std::function<void(GameObject *, GameObject *)> funk);
    private:
};