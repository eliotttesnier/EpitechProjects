/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** GameMap
*/

#pragma once

#include "GameObject.hpp"
#include "json.hpp"

using json = nlohmann::json;

typedef std::vector<std::vector<GameObject *>> Map;
class GameMap {
    public:
        enum MapType {
            BACKGROUND = 0,
            HITBOX =1
        };
        enum TimeLine {
            PAST = 0,
            PRESENT = 1,
            FUTUR = 2
        };

        GameMap();
        ~GameMap();

        std::vector<std::pair<Map, Map>> getMaps();
        std::pair<Map, Map> getMap(TimeLine timeLine);
        void setupMap(std::string content, MapType type, TimeLine timeLine);

        class Error : public std::exception {
            public:
                Error (const std::string &msg)
                {
                    _msg = msg;
                }

                const char *what() const noexcept override
                {
                    return _msg.c_str();
                }
            private:
                std::string _msg;
        };
    protected:
    private:
        std::vector<std::pair<Map, Map>> _maps;
        GameObject *getGameObject(int x, int y, std::string path, MapType type, json tileSet, int tile);
        std::string getPath(json tileSet, int tile);
        std::string getObjectType(json tileSet, int tile);
};
