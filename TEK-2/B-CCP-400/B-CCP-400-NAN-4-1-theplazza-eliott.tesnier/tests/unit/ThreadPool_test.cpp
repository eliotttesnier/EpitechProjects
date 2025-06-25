/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** ThreadPool unit tests
*/

#include <gtest/gtest.h>
#include <chrono>
#include <thread>
#include <vector>
#include "../../src/Kitchen/ThreadPool.hpp"
#include "../../src/Pizza/Pizza.hpp"

class ThreadPoolTest : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test ThreadPool constructor with valid number of threads
TEST_F(ThreadPoolTest, Constructor_ValidThreadCount) {
    ThreadPool pool(4);
    ASSERT_EQ(pool.getTotalWorkers(), 4);
    ASSERT_EQ(pool.getBusyWorkers(), 0);
}

// Test ThreadPool constructor with zero threads (should default to 1)
TEST_F(ThreadPoolTest, Constructor_ZeroThreads) {
    ThreadPool pool(0);
    ASSERT_EQ(pool.getTotalWorkers(), 1);
    ASSERT_EQ(pool.getBusyWorkers(), 0);
}

// Test ThreadPool constructor with negative threads (should default to 1)
TEST_F(ThreadPoolTest, Constructor_NegativeThreads) {
    ThreadPool pool(-2);
    ASSERT_EQ(pool.getTotalWorkers(), 1);
    ASSERT_EQ(pool.getBusyWorkers(), 0);
}

// Test initialization of the thread pool
TEST_F(ThreadPoolTest, Initialize) {
    ThreadPool pool(2);
    pool.initialize();

    ASSERT_EQ(pool.getTotalWorkers(), 2);
    ASSERT_EQ(pool.getBusyWorkers(), 0);
    pool.shutdown();
}

// Test adding a task
TEST_F(ThreadPoolTest, AddTask) {
    ThreadPool pool(2);
    pool.initialize();

    Pizza::Pizza pizza(Pizza::Margarita, Pizza::S);
    auto future = pool.addTask(pizza, 0.1f);

    future.wait();

    ASSERT_TRUE(future.get());

    pool.shutdown();
}

// Test shutdown while tasks are running
TEST_F(ThreadPoolTest, ShutdownWithTasks) {
    ThreadPool pool(3);
    pool.initialize();

    std::vector<std::future<bool>> results;

    float shortCookingTime = 0.1f;

    for (int i = 0; i < 3; i++) {
        Pizza::Pizza pizza(Pizza::Regina, Pizza::M);
        results.push_back(pool.addTask(pizza, shortCookingTime));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    pool.shutdown();

    for (auto& future : results) {
        if (future.valid()) {

            std::future_status status = future.wait_for(std::chrono::milliseconds(500));

            if (status == std::future_status::ready) {
                try {
                    future.get();
                } catch (const std::exception& e) {
                    std::cerr << "Task exception: " << e.what() << std::endl;
                }
            }
        }
    }

    SUCCEED();
}

// Test adding a task after shutdown (should throw)
TEST_F(ThreadPoolTest, AddTaskAfterShutdown) {
    ThreadPool pool(2);
    pool.initialize();
    pool.shutdown();

    Pizza::Pizza pizza(Pizza::Margarita, Pizza::S);

    ASSERT_THROW({
        pool.addTask(pizza, 1.0f);
    }, std::runtime_error);
}

// Test different pizza types with different cooking times
TEST_F(ThreadPoolTest, DifferentPizzaTypes) {
    ThreadPool pool(4);
    pool.initialize();

    std::vector<std::pair<Pizza::Pizza, float>> pizzas = {
        {Pizza::Pizza(Pizza::Margarita, Pizza::S), 0.1f},
        {Pizza::Pizza(Pizza::Regina, Pizza::M), 0.1f},
        {Pizza::Pizza(Pizza::Americana, Pizza::L), 0.1f},
        {Pizza::Pizza(Pizza::Fantasia, Pizza::XL), 0.1f}
    };

    std::vector<std::future<bool>> results;

    for (const auto& pair : pizzas) {
        results.push_back(pool.addTask(pair.first, pair.second));
    }

    for (auto& future : results) {
        future.wait();
        ASSERT_TRUE(future.get());
    }

    pool.shutdown();
}

// Test reinitializing the thread pool
TEST_F(ThreadPoolTest, Reinitialize) {
    {
        ThreadPool pool(2);
        pool.initialize();

        ASSERT_EQ(pool.getTotalWorkers(), 2);
        ASSERT_EQ(pool.getBusyWorkers(), 0);

        pool.shutdown();
    }
    {
        ThreadPool pool(3);
        pool.initialize();

        ASSERT_EQ(pool.getTotalWorkers(), 3);
        ASSERT_EQ(pool.getBusyWorkers(), 0);

        Pizza::Pizza pizza(Pizza::Margarita, Pizza::S);
        auto future = pool.addTask(pizza, 0.1f);

        future.wait();
        ASSERT_TRUE(future.get());

        pool.shutdown();
    }
}

// Test initialize when already running
TEST_F(ThreadPoolTest, InitializeWhenRunning) {
    ThreadPool pool(2);
    pool.initialize();

    pool.initialize();

    ASSERT_EQ(pool.getTotalWorkers(), 2);
    pool.shutdown();
}

// Test destructor calls shutdown
TEST_F(ThreadPoolTest, DestructorCallsShutdown) {
    {
        ThreadPool pool(2);
        pool.initialize();

    }
    SUCCEED();
}

// Test error handling in addTask with invalid pizza type
TEST_F(ThreadPoolTest, AddTaskWithInvalidPizza) {
    ThreadPool pool(1);
    pool.initialize();

    Pizza::PizzaSize invalidSize = static_cast<Pizza::PizzaSize>(999);
    Pizza::Pizza pizza(Pizza::Margarita, invalidSize);

    auto future = pool.addTask(pizza, 1.0f);
    future.wait();

    pool.shutdown();
    SUCCEED();
}
