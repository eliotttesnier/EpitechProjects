/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** IReceptionInterface
*/

#pragma once

class Config;

class IReceptionInterface {
public:
    virtual ~IReceptionInterface() = default;
    virtual int run() = 0;

protected:
    IReceptionInterface() = default;
};
