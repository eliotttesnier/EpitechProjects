/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** Kitchen Thread Safety tests
*/

#include <gtest/gtest.h>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>
#include "../../src/Kitchen/Kitchen.hpp"
#include "../../src/Kitchen/ThreadPool.hpp"
#include "../../src/Kitchen/Cook.hpp"
#include "../../src/Pizza/Pizza.hpp"
#include "../../src/Config/Config.hpp"

class KitchenThreadSafetyTest : public ::testing::Test {
protected:
    void SetUp() override {
        config = std::make_unique<Config>(2.0f, 3, 1000);
        kitchen = std::make_unique<Kitchen>(*config, 1);
        kitchen->initialize();
    }

    void TearDown() override {
        if (kitchen) {
            kitchen->shutdown();
        }
    }

    std::unique_ptr<Config> config;
    std::unique_ptr<Kitchen> kitchen;
};

// Test concurrent pizza queue operations
TEST_F(KitchenThreadSafetyTest, ConcurrentQueueOperations) {
    const int numThreads = 10;
    const int pizzasPerThread = 20;
    std::atomic<int> pizzasAdded(0);
    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([&, i]() {
            for (int j = 0; j < pizzasPerThread; ++j) {
                Pizza::Pizza pizza(Pizza::Margarita, Pizza::S);
                kitchen->addPizzaToQueue(pizza);
                pizzasAdded++;
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        });
    }

    std::atomic<int> pizzasProcessed(0);
    std::thread processor([&]() {
        while (pizzasProcessed < numThreads * pizzasPerThread) {
            auto pizza = kitchen->getNextPizza();
            if (pizza.has_value()) {
                pizzasProcessed++;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    });

    for (auto& t : threads) {
        t.join();
    }
    processor.join();

    EXPECT_EQ(pizzasAdded.load(), numThreads * pizzasPerThread);
    EXPECT_EQ(pizzasProcessed.load(), numThreads * pizzasPerThread);
    EXPECT_EQ(kitchen->getQueueSize(), 0);
}

// Test thread pool with concurrent tasks
TEST_F(KitchenThreadSafetyTest, ThreadPoolConcurrentTasks) {
    ThreadPool pool(4);
    pool.initialize();

    const int numTasks = 50;
    std::vector<std::future<bool>> results;
    std::atomic<int> completedTasks(0);

    std::vector<std::thread> submitters;
    for (int i = 0; i < 5; ++i) {
        submitters.emplace_back([&]() {
            for (int j = 0; j < 10; ++j) {
                Pizza::Pizza pizza(Pizza::Margarita, Pizza::S);
                try {
                    auto future = pool.addTask(pizza, 0.1f);
                    {
                        static std::mutex resultsMutex;
                        std::lock_guard<std::mutex> lock(resultsMutex);
                        results.push_back(std::move(future));
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Error submitting task: " << e.what() << std::endl;
                }
            }
        });
    }

    for (auto& t : submitters) {
        t.join();
    }

    for (auto& future : results) {
        if (future.valid()) {
            try {
                bool result = future.get();
                if (result) {
                    completedTasks++;
                }
            } catch (const std::exception& e) {
                std::cerr << "Task failed: " << e.what() << std::endl;
            }
        }
    }

    pool.shutdown();
    EXPECT_GT(completedTasks.load(), 0);
    EXPECT_LE(completedTasks.load(), numTasks);
}

// Test cook thread safety
TEST_F(KitchenThreadSafetyTest, CookThreadSafety) {
    Cook cook(1);
    std::atomic<int> successfulCooks(0);
    std::atomic<int> failedCooks(0);
    std::vector<std::thread> threads;

    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&]() {
            try {
                Pizza::Pizza pizza(Pizza::Margarita, Pizza::S);
                auto future = cook.cookPizza(pizza, 0.1f);
                bool result = future.get();
                if (result) {
                    successfulCooks++;
                } else {
                    failedCooks++;
                }
            } catch (const std::exception& e) {
                failedCooks++;
            }
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    EXPECT_EQ(successfulCooks.load(), 1);
    EXPECT_EQ(failedCooks.load(), 9);
    EXPECT_FALSE(cook.isBusy());
}

// Test kitchen shutdown with active tasks
TEST_F(KitchenThreadSafetyTest, SafeShutdownWithActiveTasks) {
    for (int i = 0; i < 5; ++i) {
        Pizza::Pizza pizza(Pizza::Regina, Pizza::M);
        kitchen->addPizzaToQueue(pizza);
    }

    std::vector<std::thread> workers;
    std::atomic<bool> shouldStop(false);

    for (int i = 0; i < 3; ++i) {
        workers.emplace_back([&]() {
            while (!shouldStop.load()) {
                auto pizza = kitchen->getNextPizza();
                if (pizza.has_value()) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
            }
        });
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    shouldStop = true;
    kitchen->shutdown();

    for (auto& w : workers) {
        w.join();
    }

    EXPECT_FALSE(kitchen->isValid());
    SUCCEED();
}

// Test last activity time updates are thread-safe
TEST_F(KitchenThreadSafetyTest, LastActivityThreadSafety) {
    std::vector<std::thread> threads;
    std::atomic<int> updates(0);

    for (int i = 0; i < 20; ++i) {
        threads.emplace_back([&]() {
            for (int j = 0; j < 100; ++j) {
                kitchen->updateLastActivity();
                updates++;
                std::this_thread::sleep_for(std::chrono::microseconds(10));
            }
        });
    }

    std::thread checker([&]() {
        for (int i = 0; i < 50; ++i) {
            kitchen->isIdle();
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    });

    for (auto& t : threads) {
        t.join();
    }
    checker.join();

    EXPECT_EQ(updates.load(), 20 * 100);
    SUCCEED();
}

// Test kitchen getter methods
TEST_F(KitchenThreadSafetyTest, KitchenGetterMethods) {
    EXPECT_EQ(kitchen->getKitchenId(), 1);
    EXPECT_EQ(kitchen->getMaxCapacity(), 6);
    EXPECT_EQ(kitchen->getCurrentLoad(), 0);
    EXPECT_EQ(kitchen->getTotalCooks(), 3);
    EXPECT_EQ(kitchen->getBusyCooks(), 0);
    EXPECT_EQ(kitchen->getIdleCooks(), 3);
    EXPECT_FALSE(kitchen->isSaturated());

    auto stock = kitchen->getIngredientStock();
    EXPECT_FALSE(stock.empty());

    std::string statusData = kitchen->getStatusData();
    EXPECT_FALSE(statusData.empty());

    std::vector<std::string> parts;
    std::stringstream ss(statusData);
    std::string part;

    while (std::getline(ss, part, '|')) {
        parts.push_back(part);
    }

    EXPECT_GE(parts.size(), 6);
    EXPECT_EQ(std::stoi(parts[0]), 1);
    EXPECT_EQ(std::stoi(parts[1]), 0);
    EXPECT_EQ(std::stoi(parts[2]), 3);
    EXPECT_EQ(std::stoi(parts[3]), 3);
    EXPECT_EQ(std::stoi(parts[4]), 0);
    EXPECT_EQ(std::stoi(parts[5]), 6);

    if (parts.size() > 6 && !parts[6].empty()) {
        EXPECT_TRUE(parts[6].find(':') != std::string::npos);
    }
}

// Test kitchen status changes with load
TEST_F(KitchenThreadSafetyTest, KitchenStatusChangesWithLoad) {
    for (int i = 0; i < 5; ++i) {
        Pizza::Pizza pizza(Pizza::Regina, Pizza::M);
        kitchen->addPizzaToQueue(pizza);
    }

    EXPECT_GT(kitchen->getCurrentLoad(), 0);
    EXPECT_LE(kitchen->getCurrentLoad(), kitchen->getMaxCapacity());

    for (int i = 0; i < 10; ++i) {
        Pizza::Pizza pizza(Pizza::Regina, Pizza::M);
        kitchen->addPizzaToQueue(pizza);
    }

    std::atomic<int> processCount(0);
    std::thread processor([&]() {
        for (int i = 0; i < 8; ++i) {
            auto pizza = kitchen->getNextPizza();
            if (pizza.has_value()) {
                processCount++;
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }
    });
    processor.join();

    EXPECT_EQ(processCount.load(), 8);
    EXPECT_EQ(kitchen->getQueueSize(), 7);

    bool shouldBeSaturated = kitchen->getCurrentLoad() >= kitchen->getMaxCapacity();
    EXPECT_EQ(kitchen->isSaturated(), shouldBeSaturated);
}
