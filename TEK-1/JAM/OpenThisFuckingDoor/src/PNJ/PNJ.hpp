/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** Player
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <unordered_map>

class PNJ : public Move {
    public:
        PNJ() = default;
        ~PNJ() = default;

        // Setters
        void setAnchor(float x, float y) {_anchor = std::pair<float, float>(x, y);}
        void setDialogs(std::vector<std::string> dialogs) {_dialogs = dialogs;}
        void addDialog(std::string str) {_dialogs.push_back(str);}

        // Getters
        std::pair<float, float> getAnchor(void) {return _anchor;}
        std::vector<std::string> getDialogs(void) {return _dialogs;}
    protected:
        std::pair<float, float> _anchor;
        std::vector<std::string> _dialogs;
    private:
};
