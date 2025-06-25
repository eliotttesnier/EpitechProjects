/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** Cook
*/

#pragma once

#include <atomic>
#include <future>
#include <mutex>

#include "../Pizza/Pizza.hpp"

class Cook {
    public:
        Cook(int id);
        ~Cook();

        std::future<bool> cookPizza(const Pizza::Pizza& pizza, float cookingMultiplier);
        bool isBusy() const;
        int getId() const;
        int getTotalPizzasCooked() const;
        void cancelCurrentTask();

    private:
        int _id;
        std::atomic<bool> _isBusy;
        std::atomic<int> _totalPizzasCooked;
        std::atomic<bool> _shouldCancel;
        mutable std::mutex _stateMutex;

        bool performCooking(const Pizza::Pizza& pizza, float cookingMultiplier);
};
