/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** Config
*/

#pragma once

#include <string>

class Config {
    public:
        Config() : _multiplier(1.0f), _cooksPerKitchen(1), _regenerationTimeMs(1000), _useGui(false) {}
        Config(float multiplier, int cooksPerKitchen, int regenerationTimeMs, bool useGui = false);
        ~Config() = default;

        float getMultiplier() const;
        int getCooksPerKitchen() const;
        int getRegenerationTimeMs() const;
        bool useGui() const;

        static Config parseArguments(int argc, char **argv);
        static void printUsage(const std::string &programName);

    private:
        float _multiplier;
        int _cooksPerKitchen;
        int _regenerationTimeMs;
        bool _useGui;

        static void validateArguments(int argc, char **argv);
        static float parseMultiplier(const std::string &arg);
        static int parseCooksPerKitchen(const std::string &arg);
        static int parseRegenerationTime(const std::string &arg);
};
