/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** Cook tests
*/

#include <gtest/gtest.h>
#include "../../src/Kitchen/Cook.hpp"
#include "../../src/Pizza/Pizza.hpp"

// Test Cook initialization
TEST(CookTest, Initialization)
{
    Cook cook(1);

    EXPECT_EQ(cook.getId(), 1);
    EXPECT_FALSE(cook.isBusy());
    EXPECT_EQ(cook.getTotalPizzasCooked(), 0);
}

// Test cooking a pizza
TEST(CookTest, CookPizza)
{
    Cook cook(1);
    Pizza::Pizza pizza(Pizza::Margarita, Pizza::S);

    auto future = cook.cookPizza(pizza, 0.1);

    EXPECT_TRUE(cook.isBusy());

    bool result = future.get();
    EXPECT_TRUE(result);
    EXPECT_FALSE(cook.isBusy());
    EXPECT_EQ(cook.getTotalPizzasCooked(), 1);
}

// Test cooking multiple pizzas sequentially
TEST(CookTest, MultiplePizzasSequentially)
{
    Cook cook(1);
    Pizza::Pizza pizza1(Pizza::Margarita, Pizza::S);
    Pizza::Pizza pizza2(Pizza::Regina, Pizza::M);

    auto future1 = cook.cookPizza(pizza1, 0.1);
    bool result1 = future1.get();
    EXPECT_TRUE(result1);

    auto future2 = cook.cookPizza(pizza2, 0.1);
    bool result2 = future2.get();
    EXPECT_TRUE(result2);

    EXPECT_EQ(cook.getTotalPizzasCooked(), 2);
}

// Test trying to cook a pizza while busy
TEST(CookTest, BusyCook)
{
    Cook cook(1);
    Pizza::Pizza pizza1(Pizza::Fantasia, Pizza::XL);
    Pizza::Pizza pizza2(Pizza::Americana, Pizza::M);

    auto future = cook.cookPizza(pizza1, 0.1);
    EXPECT_THROW(cook.cookPizza(pizza2, 0.1), std::runtime_error);

    future.get();

    EXPECT_FALSE(cook.isBusy());
    EXPECT_EQ(cook.getTotalPizzasCooked(), 1);
}
