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
        Config(float multiplier, int cooksPerKitchen, int regenerationTimeMs);
        ~Config() = default;

        float getMultiplier() const;
        int getCooksPerKitchen() const;
        int getRegenerationTimeMs() const;

        static Config parseArguments(int argc, char **argv);
        static void printUsage(const std::string &programName);

    private:
        float _multiplier;
        int _cooksPerKitchen;
        int _regenerationTimeMs;

        static void validateArguments(int argc, char **argv);
        static float parseMultiplier(const std::string &arg);
        static int parseCooksPerKitchen(const std::string &arg);
        static int parseRegenerationTime(const std::string &arg);
};
