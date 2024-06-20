/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** GameMap
*/

#include "GameMap.hpp"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <fstream>
#include "../Ground/Ground.hpp"
#include "../Wall/Wall.hpp"
#include "../Totem/Totem.hpp"
#include "../Door/Door.hpp"
#include "../Pillar/Pillar.hpp"
#include "../Warp/Warp_present.hpp"
#include "../Warp/Warp_futur.hpp"
#include "../Warp/Warp_past.hpp"
#include "Game.h"

GameMap::GameMap()
{
    Map mapBackPast;
    Map mapHitPas;
    _maps.push_back(std::make_pair(mapBackPast, mapHitPas));
    Map mapBackPres;
    Map mapHitPres;
    _maps.push_back(std::make_pair(mapBackPres, mapHitPres));
    Map mapBackFut;
    Map mapHitFut;
    _maps.push_back(std::make_pair(mapBackFut, mapHitFut));
}

GameMap::~GameMap() {}

std::vector<std::pair<Map, Map>> GameMap::getMaps()
{
    return _maps;
}

std::pair<Map, Map> GameMap::getMap(TimeLine timeLine)
{
    return _maps[timeLine];
}

void GameMap::setupMap(std::string path, MapType type, TimeLine timeLine)
{
    if (path.empty())
        return;
    std::ifstream f(path.c_str());
    json data = json::parse(f);

    int row = 0;
    int col = 0;
    std::vector<GameObject *> list;

    for (auto& tile : data["layers"][0]["data"]) {
        if (col == data["height"]) {
            col = 0;
            row++;
            if (type == BACKGROUND)
                _maps[timeLine].first.push_back(list);
            if (type == HITBOX)
                _maps[timeLine].second.push_back(list);
            list.clear();
        }
        if (row == data["width"])
            return;

        GameObject *object = getGameObject(col, row, getPath(data["tilesets"], tile.get<int>()), type, data["tilesets"], tile.get<int>());
        list.push_back(object);
        col++;
    }
}

GameObject *GameMap::getGameObject(int x, int y, std::string path, MapType type, json tileSet, int tile)
{
    if (type == BACKGROUND) {
        return new Ground(path, std::pair<int, int>(x * 100, y * 100), std::pair<int, int>(100, 100));
    }
    std::string objectType = getObjectType(tileSet, tile);
    if (objectType == "Wall")
        return new Wall(path, std::pair<int, int>(x * 100, y * 100), std::pair<int, int>(100, 100));
    if (objectType == "Totem")
        return new Totem(path, std::pair<int, int>(x * 100, y * 100), std::pair<int, int>(160, 160));
    if (objectType == "Door")
        return new Door(path, std::pair<int, int>(x * 100, y * 100), std::pair<int, int>(100, 100));
    if (objectType == "Pillar")
        return new Pillar(path, std::pair<int, int>(x * 100, y * 100), std::pair<int, int>(100, 100));
    if (objectType == "Warp_present")
        return new Warp_present(path, std::pair<int, int>(x * 100, y * 100), std::pair<int, int>(94, 72));
    if (objectType == "Warp_futur")
        return new Warp_present(path, std::pair<int, int>(x * 100, y * 100), std::pair<int, int>(94, 72));
    if (objectType == "Warp_past")
        return new Warp_present(path, std::pair<int, int>(x * 100, y * 100), std::pair<int, int>(94, 72));
    return new GameObject();
}

std::string GameMap::getPath(json tileSet, int tile)
{
    for (auto& tileData : tileSet) {
        if (tileData["firstgid"] == tile) {
            return "./assets/" + tileData["source"].get<std::string>();
        }
    }
    return "";
}

std::string GameMap::getObjectType(json tileSet, int tile)
{
    for (auto& tileData : tileSet) {
        if (tileData["firstgid"] == tile) {
            return tileData["type"].get<std::string>();
        }
    }
    return "";
}