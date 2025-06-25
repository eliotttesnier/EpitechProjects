/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** IngredientStock_test
*/

#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include "Kitchen/IngredientStock.hpp"
#include "Pizza/Pizza.hpp"

class IngredientStockTest : public ::testing::Test {
protected:
    void SetUp() override {
        stock = std::make_unique<IngredientStock>(100);
    }

    void TearDown() override {
        if (stock) {
            stock->stopRegeneration();
        }
    }

    std::unique_ptr<IngredientStock> stock;
};

// Test basic initialization
TEST_F(IngredientStockTest, Initialization) {
    stock->initialize();

    auto stockLevels = stock->getStockLevels();

    EXPECT_EQ(stock->getIngredientLevel(Pizza::Ingredients::DOUGH), 5);
    EXPECT_EQ(stock->getIngredientLevel(Pizza::Ingredients::TOMATO), 5);
    EXPECT_EQ(stock->getIngredientLevel(Pizza::Ingredients::GRUYERE), 5);
    EXPECT_EQ(stock->getIngredientLevel(Pizza::Ingredients::HAM), 5);
    EXPECT_EQ(stock->getIngredientLevel(Pizza::Ingredients::MUSHROOMS), 5);
    EXPECT_EQ(stock->getIngredientLevel(Pizza::Ingredients::STEAK), 5);
    EXPECT_EQ(stock->getIngredientLevel(Pizza::Ingredients::EGGPLANT), 5);
    EXPECT_EQ(stock->getIngredientLevel(Pizza::Ingredients::GOAT_CHEESE), 5);
    EXPECT_EQ(stock->getIngredientLevel(Pizza::Ingredients::CHIEF_LOVE), 5);
}

// Test ingredient consumption
TEST_F(IngredientStockTest, ConsumeIngredients) {
    stock->initialize();

    Pizza::Pizza margarita(Pizza::Margarita, Pizza::S);

    EXPECT_TRUE(stock->hasEnoughIngredients(margarita));

    EXPECT_TRUE(stock->consumeIngredients(margarita));

    EXPECT_EQ(stock->getIngredientLevel(Pizza::Ingredients::DOUGH), 4);
    EXPECT_EQ(stock->getIngredientLevel(Pizza::Ingredients::TOMATO), 4);
    EXPECT_EQ(stock->getIngredientLevel(Pizza::Ingredients::GRUYERE), 4);

    EXPECT_EQ(stock->getIngredientLevel(Pizza::Ingredients::HAM), 5);
}

// Test ingredient consumption failure when not enough ingredients
TEST_F(IngredientStockTest, ConsumeIngredientsFailure) {
    stock->initialize();

    Pizza::Pizza margarita(Pizza::Margarita, Pizza::S);

    for (int i = 0; i < 5; i++) {
        EXPECT_TRUE(stock->consumeIngredients(margarita));
    }

    EXPECT_EQ(stock->getIngredientLevel(Pizza::Ingredients::DOUGH), 0);

    EXPECT_FALSE(stock->hasEnoughIngredients(margarita));
    EXPECT_FALSE(stock->consumeIngredients(margarita));
}

// Test automatic regeneration
TEST_F(IngredientStockTest, AutomaticRegeneration) {
    stock->initialize();
    stock->startRegeneration();

    Pizza::Pizza margarita(Pizza::Margarita, Pizza::S);
    EXPECT_TRUE(stock->consumeIngredients(margarita));

    EXPECT_EQ(stock->getIngredientLevel(Pizza::Ingredients::DOUGH), 4);

    std::this_thread::sleep_for(std::chrono::milliseconds(150));

    EXPECT_EQ(stock->getIngredientLevel(Pizza::Ingredients::DOUGH), 5);
    EXPECT_EQ(stock->getIngredientLevel(Pizza::Ingredients::TOMATO), 5);
    EXPECT_EQ(stock->getIngredientLevel(Pizza::Ingredients::GRUYERE), 5);
}

// Test manual regeneration
TEST_F(IngredientStockTest, ManualRegeneration) {
    stock->initialize();

    Pizza::Pizza margarita(Pizza::Margarita, Pizza::S);
    EXPECT_TRUE(stock->consumeIngredients(margarita));

    EXPECT_EQ(stock->getIngredientLevel(Pizza::Ingredients::DOUGH), 4);

    stock->forceRegeneration();

    EXPECT_EQ(stock->getIngredientLevel(Pizza::Ingredients::DOUGH), 5);
}

// Test thread safety (basic check)
TEST_F(IngredientStockTest, ThreadSafety) {
    stock->initialize();
    stock->startRegeneration();

    std::atomic<int> successfulConsumptions(0);
    std::vector<std::thread> threads;

    for (int i = 0; i < 10; i++) {
        threads.emplace_back([&]() {
            for (int j = 0; j < 3; j++) {
                Pizza::Pizza margarita(Pizza::Margarita, Pizza::S);
                if (stock->consumeIngredients(margarita)) {
                    successfulConsumptions++;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    EXPECT_GT(successfulConsumptions.load(), 0);
    EXPECT_LE(successfulConsumptions.load(), 30);
}
