/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** KitchenProcess
*/
#include <iostream>
#include <string>
#include <memory>

#include "KitchenProcess.hpp"
#include "../IPC/FifoIPCChannel.hpp"
#include "../Utils/Logger.hpp"


/**
 * @brief Constructor
 *
 * @param config The configuration for the kitchen
 * @param kitchenId The unique ID for this kitchen
 */
KitchenProcess::KitchenProcess(const Config& config, int kitchenId)
    : Process(),
      _config(config),
      _kitchenId(kitchenId),
      _kitchen(nullptr),
      _ipcChannel(nullptr)
{
    cleanupFifos();
}

/**
 * @brief Destructor
 */
KitchenProcess::~KitchenProcess()
{
    if (isParent()) {
        cleanupFifos();
    }
}

/**
 * @brief Get the kitchen instance (only valid in parent process)
 *
 * @return Shared pointer to the kitchen instance
 */
std::shared_ptr<Kitchen> KitchenProcess::getKitchen() const
{
    return _kitchen;
}

/**
 * @brief Get the kitchen ID
 *
 * @return The kitchen ID
 */
int KitchenProcess::getKitchenId() const
{
    return _kitchenId;
}

/**
 * @brief Check if the kitchen is valid and operational
 *
 * @return true if kitchen is valid, false otherwise
 */
bool KitchenProcess::isKitchenValid() const
{
    if (!isParent() || !_kitchen) {
        return false;
    }

    return isAlive() && _kitchen->isValid();
}

/**
 * @brief Setup IPC channel for communication
 *
 * @param channel The IPC channel to use
 */
void KitchenProcess::setIpcChannel(std::shared_ptr<Plazza::IIPCChannel> channel)
{
    _ipcChannel = channel;
    if (_kitchen) {
        _kitchen->setIpcChannel(channel);
    }
}

/**
 * @brief Child process logic - runs the kitchen operation
 */
void KitchenProcess::childProcess()
{
    try {
        _kitchen = std::make_shared<Kitchen>(
            _config,
            _kitchenId,
            Kitchen::ProcessType::CHILD
        );

        _ipcChannel = std::make_shared<Plazza::FifoIPCChannel>(
            _kitchenId,
            Plazza::FifoIPCChannel::Mode::CHILD
        );

        _kitchen->setIpcChannel(_ipcChannel);
        _kitchen->initialize();

        _kitchen->operate();
    } catch (const std::exception& e) {
        std::cerr << "Kitchen " << _kitchenId << " child process error: "
                  << e.what() << std::endl;
        _exit(1);
    }
}

/**
 * @brief Parent process logic - sets up parent-side kitchen
 */
void KitchenProcess::parentProcess()
{
    try {
        _kitchen = std::make_shared<Kitchen>(
            _config,
            _kitchenId,
            Kitchen::ProcessType::PARENT
        );

        _ipcChannel = std::make_shared<Plazza::FifoIPCChannel>(
            _kitchenId,
            Plazza::FifoIPCChannel::Mode::PARENT
        );

        _kitchen->setIpcChannel(_ipcChannel);
        _kitchen->initialize();

        Logger::getInstance().logKitchenStatus(_kitchenId,
            "Kitchen process created successfully (PID: " + std::to_string(getPid()) + ")");
    } catch (const std::exception& e) {
        std::cerr << "Kitchen " << _kitchenId << " parent setup error: "
                  << e.what() << std::endl;
        Logger::getInstance().log(Logger::LogLevel::ERROR,
            "Kitchen " + std::to_string(_kitchenId) + " parent setup failed: " + e.what());
    }
}

/**
 * @brief Handle fork failure
 */
void KitchenProcess::onForkFailure()
{
    std::cerr << "Failed to fork kitchen process " << _kitchenId << std::endl;
    Logger::getInstance().log(Logger::LogLevel::ERROR,
        "Failed to fork kitchen process " + std::to_string(_kitchenId));

    cleanupFifos();
}

/**
 * @brief Clean up FIFO files for this kitchen
 */
void KitchenProcess::cleanupFifos()
{
    std::string parentToChildPath = "/tmp/reception_to_kitchen_"
                                  + std::to_string(_kitchenId) + ".fifo";
    std::string childToParentPath = "/tmp/kitchen_to_reception_"
                                  + std::to_string(_kitchenId) + ".fifo";

    unlink(parentToChildPath.c_str());
    unlink(childToParentPath.c_str());
}
