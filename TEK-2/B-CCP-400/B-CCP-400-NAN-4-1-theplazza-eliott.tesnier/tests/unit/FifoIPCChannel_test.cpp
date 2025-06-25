/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Tests for FifoIPCChannel
*/

#include <gtest/gtest.h>
#include "IPC/FifoIPCChannel.hpp"
#include <thread>
#include <chrono>
#include <unistd.h>
#include <future>
#include <atomic>

void cleanupFifos(int id)
{
    std::string parentToChildPath = "/tmp/reception_to_kitchen_" + std::to_string(id) + ".fifo";
    std::string childToParentPath = "/tmp/kitchen_to_reception_" + std::to_string(id) + ".fifo";
    unlink(parentToChildPath.c_str());
    unlink(childToParentPath.c_str());
}

TEST(FifoIPCChannel, SendReceive)
{
    cleanupFifos(123); // 123 -> unique ID for this test

    const std::string testMessage = "Hello, FIFO IPC World!";
    std::string receivedMessage;
    std::atomic<bool> childReady(false);
    std::atomic<bool> parentReady(false);
    std::atomic<bool> childReceivedMessage(false);

    std::thread childThread([&]() {
        Plazza::FifoIPCChannel child(123, Plazza::FifoIPCChannel::Mode::CHILD);

        childReady.store(true);

        while (!parentReady.load()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        for (int i = 0; i < 100 && !child.hasData(50); i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        receivedMessage = child.receive();
        childReceivedMessage.store(!receivedMessage.empty());
    });

    Plazza::FifoIPCChannel parent(123, Plazza::FifoIPCChannel::Mode::PARENT);

    while (!childReady.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    parentReady.store(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    ASSERT_TRUE(parent.send(testMessage));

    childThread.join();
    ASSERT_TRUE(childReceivedMessage.load());
    EXPECT_EQ(testMessage, receivedMessage);
}

// Test for bidirectional communication
TEST(FifoIPCChannel, Bidirectional)
{
    cleanupFifos(456); // 456 -> unique ID for this test

    const std::string parentMessage = "Hello from parent!";
    const std::string childMessage = "Hello from child!";
    std::string receivedByChild;
    std::string receivedByParent;
    std::atomic<bool> childReady(false);
    std::atomic<bool> parentReady(false);
    std::atomic<bool> childSuccess(false);
    std::atomic<bool> childSent(false);
    std::atomic<bool> messageReceived(false);

    std::thread childThread([&]() {
        Plazza::FifoIPCChannel child(456, Plazza::FifoIPCChannel::Mode::CHILD);

        childReady.store(true);

        while (!parentReady.load()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        for (int i = 0; i < 100 && !child.hasData(50); i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        receivedByChild = child.receive();
        messageReceived.store(true);

        if (!receivedByChild.empty()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(300));

            for (int i = 0; i < 5; i++) {
                if (child.send(childMessage)) {
                    childSuccess.store(true);
                    break;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }

            childSent.store(true);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    });

    Plazza::FifoIPCChannel parent(456, Plazza::FifoIPCChannel::Mode::PARENT);

    while (!childReady.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    parentReady.store(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    ASSERT_TRUE(parent.send(parentMessage));

    while (!messageReceived.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    while (!childSent.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    bool dataReceived = false;
    for (int i = 0; i < 10 && !dataReceived; i++) {
        dataReceived = parent.hasData(100);
        if (!dataReceived) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    receivedByParent = parent.receive();
    childThread.join();

    EXPECT_EQ(parentMessage, receivedByChild);
    EXPECT_EQ(childMessage, receivedByParent);
    EXPECT_TRUE(childSuccess.load());
}

// Test with multiple messages
TEST(FifoIPCChannel, MultipleMessages)
{
    cleanupFifos(789); // 789 -> unique ID for this test

    const int NUM_MESSAGES = 5;
    std::vector<std::string> messages = {
        "Message 1",
        "Message 2",
        "Message 3",
        "Message 4",
        "Message 5"
    };
    std::vector<std::string> receivedMessages;
    std::atomic<bool> childReady(false);
    std::atomic<bool> parentReady(false);
    std::atomic<bool> success(true);

    std::thread childThread([&]() {
        Plazza::FifoIPCChannel child(789, Plazza::FifoIPCChannel::Mode::CHILD);

        childReady.store(true);

        while (!parentReady.load()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        for (int i = 0; i < NUM_MESSAGES; i++) {
            for (int j = 0; j < 100 && !child.hasData(50); j++) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }

            std::string msg = child.receive();
            if (!msg.empty()) {
                receivedMessages.push_back(msg);
            } else {
                success.store(false);
                break;
            }
        }
    });

    Plazza::FifoIPCChannel parent(789, Plazza::FifoIPCChannel::Mode::PARENT);

    while (!childReady.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    parentReady.store(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    for (const auto &message : messages) {
        ASSERT_TRUE(parent.send(message));
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    childThread.join();

    ASSERT_TRUE(success.load());
    ASSERT_EQ(NUM_MESSAGES, static_cast<int>(receivedMessages.size()));
    for (int i = 0; i < NUM_MESSAGES; i++) {
        EXPECT_EQ(messages[i], receivedMessages[i]);
    }
}
