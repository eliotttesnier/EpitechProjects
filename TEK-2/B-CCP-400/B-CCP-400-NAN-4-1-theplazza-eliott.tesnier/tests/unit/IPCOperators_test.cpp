/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** Tests for IPC channel operator overloads
*/

#include <gtest/gtest.h>
#include "IPC/FifoIPCChannel.hpp"
#include <thread>
#include <chrono>
#include <atomic>
#include <memory>
#include <string>

// Helper function to clean up FIFO files
void cleanUpOperatorTestFifos(int id)
{
    std::string parentToChildPath = "/tmp/reception_to_kitchen_" + std::to_string(id) + ".fifo";
    std::string childToParentPath = "/tmp/kitchen_to_reception_" + std::to_string(id) + ".fifo";
    unlink(parentToChildPath.c_str());
    unlink(childToParentPath.c_str());
}

// Test the << and >> operators for strings
TEST(IPCOperators, StringOperators)
{
    cleanUpOperatorTestFifos(999);

    const std::string testMessage = "Testing operator overloads";
    std::string receivedMessage;

    std::atomic<bool> childReady(false);
    std::atomic<bool> parentReady(false);
    std::atomic<bool> messageReceived(false);

    std::thread childThread([&]() {
        Plazza::FifoIPCChannel child(999, Plazza::FifoIPCChannel::Mode::CHILD);
        childReady.store(true);

        while (!parentReady.load()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        for (int i = 0; i < 100 && !child.hasData(50); i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        child >> receivedMessage;
        messageReceived.store(!receivedMessage.empty());
    });

    Plazza::FifoIPCChannel parent(999, Plazza::FifoIPCChannel::Mode::PARENT);
    while (!childReady.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    parentReady.store(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    parent << testMessage;
    childThread.join();

    ASSERT_TRUE(messageReceived.load());
    EXPECT_EQ(testMessage, receivedMessage);

    cleanUpOperatorTestFifos(999);
}

// Test the << and >> operators for numeric types
TEST(IPCOperators, NumericOperators)
{
    cleanUpOperatorTestFifos(998);

    const int testValue = 42;
    int receivedValue = 0;

    std::atomic<bool> childReady(false);
    std::atomic<bool> parentReady(false);
    std::atomic<bool> valueReceived(false);

    std::thread childThread([&]() {
        Plazza::FifoIPCChannel child(998, Plazza::FifoIPCChannel::Mode::CHILD);
        childReady.store(true);

        while (!parentReady.load()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        for (int i = 0; i < 100 && !child.hasData(50); i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        child >> receivedValue;
        valueReceived.store(receivedValue != 0);
    });

    Plazza::FifoIPCChannel parent(998, Plazza::FifoIPCChannel::Mode::PARENT);
    while (!childReady.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    parentReady.store(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    parent << testValue;
    childThread.join();

    ASSERT_TRUE(valueReceived.load());
    EXPECT_EQ(testValue, receivedValue);

    cleanUpOperatorTestFifos(998);
}
