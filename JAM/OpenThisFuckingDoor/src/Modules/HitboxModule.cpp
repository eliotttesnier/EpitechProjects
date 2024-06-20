/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** No file there , just an epitech header example .
*/

#include "HitboxModule.hpp"
#include "PositionModule.hpp"
#include <cmath>
#include <algorithm>

HitboxModule::HitboxModule(GameObject *gameObject)
{
    if (gameObject->hasModule<HitboxModule>())
        throw Error("GameObject already has a HitboxModule!");
    if (gameObject->data.find("size") == gameObject->data.end())
        gameObject->data["size"] = std::pair<int, int>(0, 0);
    if (!gameObject->hasModule<PositionModule>())
        gameObject->addModule<PositionModule>();
}

bool HitboxModule::contact(GameObject *gameObject, GameObject *otherObject)
{
    if (!gameObject->hasModule<HitboxModule>() || !otherObject->hasModule<HitboxModule>())
        return (false);
    if (gameObject != otherObject) {
        double distance = calculateDistance(gameObject, otherObject);
        if (distance - 0.01 < 0)
            return (true);
    }
    return (false);
}

double HitboxModule::calculateDistance(GameObject *obj1, GameObject *obj2)
{
    double center_1_x = std::any_cast<double>(obj1->data["x"]) + std::any_cast<std::pair<int, int>>(obj1->data["size"]).first / 2;
    double center_1_y = std::any_cast<double>(obj1->data["y"]) + std::any_cast<std::pair<int, int>>(obj1->data["size"]).second / 2;
    double center_2_x = std::any_cast<double>(obj2->data["x"]) + std::any_cast<std::pair<int, int>>(obj2->data["size"]).first / 2;
    double center_2_y = std::any_cast<double>(obj2->data["y"]) + std::any_cast<std::pair<int, int>>(obj2->data["size"]).second / 2;

    double distance_x = abs(center_1_x - center_2_x);
    double distance_y = abs(center_1_y - center_2_y);

    distance_x -= (std::any_cast<std::pair<int, int>>(obj1->data["size"]).first + std::any_cast<std::pair<int, int>>(obj2->data["size"]).first) / 2;
    distance_y -= (std::any_cast<std::pair<int, int>>(obj1->data["size"]).second + std::any_cast<std::pair<int, int>>(obj2->data["size"]).second) / 2;

    distance_x = std::max(0.0, distance_x);
    distance_y = std::max(0.0, distance_y);

    return (sqrt(distance_x * distance_x + distance_y * distance_y));
}
