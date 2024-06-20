/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** main
*/

#include "GameMenu/GameMenu.hpp"
#include "Game.hpp"
#include "button.hpp"

Game game;

void displayMap(Map map)
{
    std::vector<GameObject *> vec;
    for (auto &elem1 : map) {
        for (auto &elem2 : elem1) {
            vec.push_back(elem2);
            elem2->update(vec);
            vec.clear();
        }
    }
}

int main(int argc, char **argv)
{
    int event;
    (void) argc;
    (void) argv;

    game.playMusic();
    while (game.isWindowOpen()) {
        event = game.getKeyEvent();
        game.clearWindow();
        if (game.getScene() == GAMEMENU)
            game.getGameMenu()->displayGameMenu();
        if (game.getScene() == OPTION)
            game.getOptionMenu()->displayOptionMenu();
        if (game.getScene() == GAMEPLAY) {
            displayMap(game.getGameMap()->getMap(game.getTimeLine()).first);
            displayMap(game.getGameMap()->getMap(game.getTimeLine()).second);
            std::vector<GameObject *> caca;
            caca.push_back(game.getPlayer());
            game.getPlayer()->update(caca);
            game.displayFilter();
            game.getPlayer()->displayPlayer();
        }
        if (game.getScene() == CREDIT)
            game.getCreditMenu()->displayCredit();
        game.DisplayWindow();
    }
    (void) event;
    return 0;
}
