/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** TimeModule
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "TimeModule.hpp"

TimeModule::TimeModule(GameObject *gameObject)
{
    if (gameObject->hasModule<TimeModule>())
        throw Error("GameObject already has a TimeModule!");
    if (gameObject->data.find("clock") == gameObject->data.end())
        gameObject->data["clock"] = new sf::Clock();
}

void TimeModule::update(GameObject *gameObject, std::vector<GameObject*> gameObjects)
{
    (void) gameObject;
    (void) gameObjects;
    return;
}