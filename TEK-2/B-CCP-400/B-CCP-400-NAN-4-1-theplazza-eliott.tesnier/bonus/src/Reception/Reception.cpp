/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** Reception
*/

#include <unistd.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <regex>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <limits>
#include <unordered_map>

#include "Reception.hpp"
#include "../Utils/ColorUtils.hpp"
#include "../Utils/Logger.hpp"
#include "../Process/KitchenProcess.hpp"
#include "../Pizza/PizzaConfig.hpp"

/**
 * @brief Constructor for the Reception class
 * @param config The parsed configuration object
 */
Reception::Reception(const Config &config)
    : _config(config), _running(false), _nextOrderId(1)
{
    Logger::getInstance();
    Logger::getInstance().log(Logger::LogLevel::INFO, "Reception initialized");
}

/**
 * @brief Destructor for the Reception class
 */
Reception::~Reception()
{
    std::unique_lock<std::mutex> lock(_kitchensMutex);
    Logger::getInstance().log(Logger::LogLevel::INFO, "Reception shutting down");

    for (auto& kitchen : _kitchens) {
        try {
            if (kitchen->getIpcChannel())
                kitchen->getIpcChannel()->close();
        } catch (const std::exception& e) {
            Logger::getInstance().log(Logger::LogLevel::ERROR,
                "Error closing kitchen IPC channel: " + std::string(e.what()));
        }
    }

    for (auto& process : _kitchenProcesses) {
        try {
            if (process->isAlive()) {
                Logger::getInstance().logKitchenStatus(process->getKitchenId(),
                    "Terminating kitchen process during Reception shutdown");

                if (!process->terminate(2000)) {
                    Logger::getInstance().logKitchenStatus(process->getKitchenId(),
                        "Failed to terminate gracefully, killing process");
                    process->kill();
                }
            }
        } catch (const std::exception& e) {
            Logger::getInstance().log(Logger::LogLevel::ERROR,
                "Error terminating kitchen process: " + std::string(e.what()));
        }
    }

    _kitchens.clear();
    _kitchenProcesses.clear();
    std::cout << ColorUtils::RED << ColorUtils::BOLD << std::endl
    << "Thank you for using The Plazza!" << ColorUtils::RESET << std::endl;
}

/**s
 * @brief Stop the reception processing
 */
void Reception::stop()
{
    _running = false;
}

/**
 * @brief Display the welcome message for the Plazza
 */
void Reception::displayWelcomeMessage() const
{
    std::cout << ColorUtils::BOLD << ColorUtils::CYAN << "=== Welcome to The Plazza ==="
              << ColorUtils::RESET << std::endl;
    std::cout << "Type 'help' to see available commands" << std::endl;
    std::cout << "Enter your pizza order using the format: TYPE SIZE xN; [TYPE SIZE xN; ...]"
              << std::endl;
}

/**
 * @brief Display help information
 */
void Reception::displayHelp() const
{
    std::cout << ColorUtils::BOLD << ColorUtils::CYAN << "=== The Plazza Help ==="
              << ColorUtils::RESET << std::endl;
    std::cout << "Available commands:" << std::endl;
    std::cout << "  - Pizza orders: TYPE SIZE xN; [TYPE SIZE xN; ...]" << std::endl;
    std::cout << "      TYPE: ";
    for (const auto& pizza : Pizza::PizzaConfig::getInstance().getAllPizzaNames()) {
        std::cout << pizza << " ";
    }
    std::cout << std::endl;
    std::cout << "      SIZE: S, M, L, XL, XXL" << std::endl;
    std::cout << "      N: quantity (1-max)" << std::endl;
    std::cout << "  - status: Display kitchen status" << std::endl;
    std::cout << "  - help: Display this help message" << std::endl;
    std::cout << "  - exit: Exit The Plazza" << std::endl;
}

/**
 * @brief Process a command from the user
 * @param command The command to process
 */
void Reception::processCommand(const std::string& command)
{
    std::string trimmedCommand = command;
    trimmedCommand.erase(0, trimmedCommand.find_first_not_of(" \t\n\r\f\v"));
    trimmedCommand.erase(trimmedCommand.find_last_not_of(" \t\n\r\f\v") + 1);

    if (trimmedCommand.empty())
        return;

    Logger::getInstance().log(Logger::LogLevel::INFO, "Processing command: " + trimmedCommand);

    if (trimmedCommand == "exit" || trimmedCommand == "quit") {
        Logger::getInstance().log(Logger::LogLevel::INFO, "Exit command received");
        stop();
        return;
    }

    if (trimmedCommand == "help") {
        displayHelp();
        return;
    }

    if (trimmedCommand == "status") {
        showStatus();
        return;
    }

    processOrderCommand(trimmedCommand);
}

/**
 * @brief Process an order command from the user
 *
 * @param command The order command string (e.g., "regina M x2; margarita L x1")
 */
void Reception::processOrderCommand(const std::string& command)
{
    bool hasValidOrders = false;
    bool hasInvalidOrders = false;

    auto [batch, totalPizzaCount] =
        validateAndParseOrders(command, hasValidOrders, hasInvalidOrders);

    if (hasInvalidOrders && !hasValidOrders) {
        std::cout << ColorUtils::YELLOW << "No valid orders to process."
                  << ColorUtils::RESET << std::endl;
        Logger::getInstance().log(Logger::LogLevel::WARNING, "No valid orders to process");
        return;
    }

    if (hasValidOrders && !hasInvalidOrders) {
        Logger::getInstance().log(Logger::LogLevel::INFO,
            "Processing " + std::to_string(batch.validCount()) + " valid orders");

        cleanupInvalidKitchens();

        int requiredKitchens = calculateRequiredKitchens(totalPizzaCount);
        std::cout << ColorUtils::CYAN << "Total pizzas: " << totalPizzaCount
                  << ", Estimated required kitchens: " << requiredKitchens
                  << ColorUtils::RESET << std::endl;
        Logger::getInstance().log(Logger::LogLevel::INFO,
            "Total pizzas: " + std::to_string(totalPizzaCount) +
            ", Estimated required kitchens: " + std::to_string(requiredKitchens));

        createNecessaryKitchens(requiredKitchens);

        int orderId = createNewOrder(batch.orders);
        for (auto& order : batch.orders) {
            if (!order.isValid)
                continue;

            order.orderId = orderId;

            Logger::getInstance().log(Logger::LogLevel::INFO,
                "Processing order: " + order.getDescription() +
                    " (Order #" + std::to_string(orderId) + ")");

            for (int i = 0; i < order.quantity; ++i) {
                bool orderAssigned = assignPizzaToKitchen(order);

                if (!orderAssigned)
                    orderAssigned = createKitchenAndAssignPizza(order);

                if (!orderAssigned) {
                    std::cerr << ColorUtils::RED << "Failed to assign order to any kitchen"
                            << ColorUtils::RESET << std::endl;
                    Logger::getInstance().logOrder(order, Logger::OrderStatus::FAILED);
                }
            }
        }

        std::cout << ColorUtils::BOLD << ColorUtils::CYAN << "Order #" << orderId
                  << " registered with " << totalPizzaCount << " pizzas."
                  << ColorUtils::RESET << std::endl;
    } else if (hasInvalidOrders) {
        std::cout << ColorUtils::RED
                  << "Order contains invalid entries. The entire order has been rejected."
                  << ColorUtils::RESET << std::endl;
        Logger::getInstance().log(Logger::LogLevel::WARNING,
                "Order rejected due to invalid entries");
    }
}

/**
 * @brief Split an order string into individual pizza orders
 *
 * @param orderString The full order string
 *
 * @return Vector of individual pizza order strings
 */
std::vector<std::string> Reception::splitOrderString(const std::string& orderString) const
{
    std::vector<std::string> result;
    std::stringstream ss(orderString);
    std::string item;

    while (std::getline(ss, item, ';')) {
        item.erase(0, item.find_first_not_of(" \t\n\r\f\v"));
        item.erase(item.find_last_not_of(" \t\n\r\f\v") + 1);

        if (!item.empty())
            result.push_back(item);
    }

    return result;
}

/**
 * @brief Parse a pizza order item string into a PizzaOrder struct
 *
 * @param orderItem The order item string (e.g., "regina M x2")
 *
 * @return A PizzaOrder struct with the parsed information
 */
Pizza::PizzaOrder Reception::parsePizzaOrder(const std::string& orderItem) const
{
    Pizza::PizzaOrder order;
    std::regex orderPattern("([a-zA-Z]+)\\s+([a-zA-Z]+)\\s+x(\\d+)");
    std::smatch matches;

    if (std::regex_match(orderItem, matches, orderPattern)) {
        if (matches.size() == 4) {
            std::string typeStr = matches[1].str();
            std::string sizeStr = matches[2].str();
            std::string quantityStr = matches[3].str();

            std::string typeLower = typeStr;
            std::transform(typeLower.begin(), typeLower.end(), typeLower.begin(),
                           [](unsigned char c){ return std::tolower(c); });

            typeStr = std::toupper(typeLower[0]);
            for (size_t i = 1; i < typeLower.length(); ++i) {
                typeStr += std::tolower(typeLower[i]);
            }

            order.pizzaId = stringToPizzaId(typeStr);
            if (order.pizzaId.empty()) {
                order.errorMessage = "Unknown pizza type: " + typeStr;
                return order;
            }

            order.size = stringToPizzaSize(sizeStr);
            if (order.size == static_cast<Pizza::PizzaSize>(0)) {
                order.errorMessage = "Invalid size: " + sizeStr;
                return order;
            }

            int quantity;
            if (!parseQuantity(quantityStr, quantity)) {
                order.errorMessage = "Invalid quantity: " + quantityStr;
                return order;
            }
            order.quantity = quantity;
            order.isValid = true;
            order.errorMessage = "";
        }
    } else {
        order.errorMessage = "Order format should be: TYPE SIZE xN";
    }

    return order;
}

/**
 * @brief Convert a string to a Pizza ID using configuration
 *
 * @param typeStr The pizza type as a string
 *
 * @return The corresponding pizza ID, or empty string if invalid
 */
std::string Reception::stringToPizzaId(const std::string& typeStr) const
{
    auto& config = Pizza::PizzaConfig::getInstance();
    return config.findPizzaIdByName(typeStr);
}

/**
 * @brief Convert a string to a PizzaSize
 *
 * @param sizeStr The pizza size as a string
 *
 * @return The corresponding PizzaSize enum value, or 0 if invalid
 */
Pizza::PizzaSize Reception::stringToPizzaSize(const std::string& sizeStr) const
{
    return Pizza::PizzaConfig::stringToSize(sizeStr);
}

/**
 * @brief Parse a quantity string into an integer
 *
 * @param quantityStr The quantity string
 * @param quantity Reference to store the parsed quantity
 *
 * @return true if parsing was successful, false otherwise
 */
bool Reception::parseQuantity(const std::string& quantityStr, int& quantity) const
{
    try {
        quantity = std::stoi(quantityStr);
        return (quantity >= 1);
    } catch (const std::exception& e) {
        return false;
    }
}

/**
 * @brief Display the kitchen status header
 */
void Reception::displayKitchenHeader() const
{
    std::cout << ColorUtils::CYAN << "=== Kitchen Status ===" << ColorUtils::RESET
              << std::endl;
}

/**
 * @brief Request status information from a kitchen
 *
 * @param kitchen The kitchen to request status from
 * @param statusData Output parameter to store the status data if received
 *
 * @return true if status was successfully received, false otherwise
 */
bool Reception::requestKitchenStatus(
    const std::shared_ptr<Kitchen>& kitchen,
    std::string& statusData) const
{
    if (!kitchen->isValid() ||
        !kitchen->getIpcChannel() ||
        !kitchen->getIpcChannel()->isValid()) {
        return false;
    }

    auto ipcChannel = kitchen->getIpcChannel();

    try {
        if (ipcChannel->send("STATUS_REQUEST")) {
            for (int attempt = 0; attempt < 5; ++attempt) {
                if (ipcChannel->hasData(100)) {
                    std::string response = ipcChannel->receive();
                    if (response.find("STATUS_DATA:") == 0) {
                        statusData = response.substr(12);
                        return true;
                    }
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        }
    } catch (const std::exception& e) {
        std::cerr << ColorUtils::RED << "Error getting status from kitchen #"
                  << kitchen->getKitchenId() << ": " << e.what()
                  << ColorUtils::RESET << std::endl;
    }

    return false;
}

/**
 * @brief Parse and display kitchen information from remote data
 *
 * @param statusData The pipe-delimited status data from the kitchen
 */
void Reception::displayKitchenWithRemoteData(const std::string& statusData) const
{
    try {
        std::vector<std::string> parts;
        std::string temp;
        std::stringstream ss(statusData);

        while (std::getline(ss, temp, '|')) {
            parts.push_back(temp);
        }

        if (parts.size() < 6) {
            throw std::runtime_error("Invalid status data format");
        }

        int id = std::stoi(parts[0]);
        int busyCooks = std::stoi(parts[1]);
        int idleCooks = std::stoi(parts[2]);
        int totalCooks = std::stoi(parts[3]);
        int currentLoad = std::stoi(parts[4]);
        int maxCapacity = std::stoi(parts[5]);

        std::unordered_map<std::string, int> ingredients;
        if (parts.size() > 6 && !parts[6].empty()) {
            std::stringstream ingredientStream(parts[6]);
            std::string ingredientPair;

            while (std::getline(ingredientStream, ingredientPair, ',')) {
                size_t colonPos = ingredientPair.find(':');
                if (colonPos != std::string::npos) {
                    std::string name = ingredientPair.substr(0, colonPos);
                    int quantity = std::stoi(ingredientPair.substr(colonPos + 1));
                    ingredients[name] = quantity;
                }
            }
        }


        std::cout << ColorUtils::BOLD << ColorUtils::CYAN << "Kitchen #" << id << ":"
                  << ColorUtils::RESET << std::endl;

        std::cout << "  - Cooks: " << busyCooks << " busy, "
                  << idleCooks << " idle, "
                  << totalCooks << " total" << std::endl;

        std::cout << "  - Current Load: " << currentLoad << "/" << maxCapacity << std::endl;

        std::cout << "  - Ingredients:" << std::endl;
        for (const auto& [ingredient, quantity] : ingredients) {
            std::cout << "    * " << ingredient << ": " << quantity << std::endl;
        }

        std::cout << std::endl;
    } catch (const std::exception& e) {
        std::cout << ColorUtils::RED << "Error parsing kitchen status"
                  << ColorUtils::RESET << std::endl;
    }
}

/**
 * @brief Show the status of all kitchens
 */
void Reception::showStatus() const
{
    checkKitchenConnections();
    displayKitchenHeader();

    std::lock_guard<std::mutex> lock(_kitchensMutex);

    int validCount = 0;
    for (const auto& kitchen : _kitchens) {
        if (kitchen->isValid())
            validCount++;
    }

    if (_kitchens.empty() || validCount == 0) {
        std::cout << "No active kitchens." << std::endl;
        return;
    }

    for (const auto& kitchen : _kitchens) {
        if (!kitchen->isValid() ||
            !kitchen->getIpcChannel() ||
            !kitchen->getIpcChannel()->isValid()) {
            continue;
        }

        std::string statusData;
        if (requestKitchenStatus(kitchen, statusData)) {
            displayKitchenWithRemoteData(statusData);
        }
    }
}

/**
 * @brief Create a new kitchen process and add it to the kitchen list
 */
void Reception::createNewKitchen()
{
    int kitchenId = _kitchens.size() + 1;

    try {
        auto kitchenProcess = std::make_shared<KitchenProcess>(_config, kitchenId);

        if (!kitchenProcess->start()) {
            throw std::runtime_error("Failed to start kitchen process");
        }

        if (kitchenProcess->isParent()) {
            std::lock_guard<std::mutex> lock(_kitchensMutex);
            _kitchenProcesses.push_back(kitchenProcess);
            _kitchens.push_back(kitchenProcess->getKitchen());

            Logger::getInstance().logKitchenStatus(kitchenId,
                "Kitchen process created successfully");
        }
    } catch (const std::exception& e) {
        std::cerr << "Failed to create kitchen " << kitchenId << ": "
                  << e.what() << std::endl;
        Logger::getInstance().log(Logger::LogLevel::ERROR,
            "Failed to create kitchen " + std::to_string(kitchenId) + ": " + e.what());
        throw;
    }
}

/**
 * @brief Check for messages from kitchens and handle them
 */
void Reception::checkKitchenMessages()
{
    std::unique_lock<std::mutex> lock(_kitchensMutex);

    for (auto it = _kitchens.begin(); it != _kitchens.end();) {
        auto& kitchen = *it;
        auto ipcChannel = kitchen->getIpcChannel();

        std::shared_ptr<KitchenProcess> kitchenProcess = nullptr;
        for (const auto& process : _kitchenProcesses) {
            if (process->getKitchenId() == kitchen->getKitchenId()) {
                kitchenProcess = process;
                break;
            }
        }

        bool processAlive = kitchenProcess && kitchenProcess->isAlive();

        if (!ipcChannel || !processAlive) {
            int kitchenId = kitchen->getKitchenId();
            Logger::getInstance().logKitchenStatus(kitchenId,
                "Kitchen process or IPC channel is no longer available");

            {
                std::lock_guard<std::mutex> loadLock(_loadsMutex);
                _kitchenLoads.erase(kitchenId);
            }

            it = _kitchens.erase(it);
            continue;
        }

        if (!ipcChannel->isValid()) {
            {
                std::lock_guard<std::mutex> loadLock(_loadsMutex);
                _kitchenLoads.erase(kitchen->getKitchenId());
            }

            if (kitchenProcess) {
                Logger::getInstance().logKitchenStatus(kitchen->getKitchenId(),
                    "IPC channel is no longer valid, terminating kitchen process");
                kitchenProcess->terminate(1000);
            }
            it = _kitchens.erase(it);
            continue;
        }

        try {
            if (ipcChannel->hasData(0)) {
                std::string message = ipcChannel->receive();
                if (message == "SHUTDOWN" || message == "EXIT") {
                    int kitchenId = kitchen->getKitchenId();
                    Logger::getInstance().logKitchenStatus(kitchenId,
                        "Kitchen sent shutdown message");

                    {
                        std::lock_guard<std::mutex> loadLock(_loadsMutex);
                        _kitchenLoads.erase(kitchenId);
                    }

                    if (kitchenProcess) {
                        kitchenProcess->terminate(1000);
                    }

                    it = _kitchens.erase(it);
                } else if (message.find("PIZZA_COOKED:") == 0) {
                    int kitchenId = kitchen->getKitchenId();
                    processPizzaCookedMessage(message, kitchenId);
                    ++it;
                } else {
                    ++it;
                }
            } else {
                ++it;
            }
        } catch (const std::exception& e) {
            int kitchenId = kitchen->getKitchenId();
            Logger::getInstance().logKitchenStatus(kitchenId,
                "Exception in checkKitchenMessages: " + std::string(e.what()));

            {
                std::lock_guard<std::mutex> loadLock(_loadsMutex);
                _kitchenLoads.erase(kitchenId);
            }

            it = _kitchens.erase(it);
        }
    }

    checkCompletedOrders();
}

/**
 * @brief Parse and validate pizza orders from a command string
 *
 * @param command The command string to parse
 * @param hasValidOrders Output parameter indicating if any valid orders were found
 * @param hasInvalidOrders Output parameter indicating if any invalid orders were found
 * @return A pair containing the order batch and total pizza count
 */
std::pair<Pizza::OrderBatch, int> Reception::validateAndParseOrders(
    const std::string& command, bool& hasValidOrders, bool& hasInvalidOrders)
{
    std::vector<std::string> orderItems = splitOrderString(command);
    Pizza::OrderBatch batch;
    int totalPizzaCount = 0;

    hasValidOrders = false;
    hasInvalidOrders = false;

    for (const auto& item : orderItems) {
        Pizza::PizzaOrder order = parsePizzaOrder(item);
        batch.orders.push_back(order);

        if (order.isValid) {
            hasValidOrders = true;
            totalPizzaCount += order.quantity;
        } else {
            hasInvalidOrders = true;
            std::cout << ColorUtils::RED << "Invalid order: " << item << " - "
                      << order.errorMessage << ColorUtils::RESET << std::endl;
            Logger::getInstance().log(Logger::LogLevel::WARNING,
                "Invalid order: " + item + " - " + order.errorMessage);
        }
    }

    return {batch, totalPizzaCount};
}

/**
 * @brief Clean up invalid kitchens and report status
 */
void Reception::cleanupInvalidKitchens()
{
    std::unique_lock<std::mutex> lock(_kitchensMutex);

    for (auto it = _kitchens.begin(); it != _kitchens.end();) {
        bool shouldRemove = false;
        int kitchenId = (*it)->getKitchenId();

        std::shared_ptr<KitchenProcess> kitchenProcess = nullptr;
        for (auto processIt = _kitchenProcesses.begin();
        processIt != _kitchenProcesses.end(); ++processIt) {
            if ((*processIt)->getKitchenId() == kitchenId) {
                kitchenProcess = *processIt;
                break;
            }
        }

        if (!(*it)->isValid()) {
            Logger::getInstance().logKitchenStatus(kitchenId,
                "Kitchen marked as invalid and will be cleaned up");
            shouldRemove = true;
        } else if (kitchenProcess && !kitchenProcess->isAlive()) {
            Logger::getInstance().logKitchenStatus(kitchenId,
                "Kitchen process is no longer alive - cleaning up");
            shouldRemove = true;
        }

        if (shouldRemove) {
            if ((*it)->getIpcChannel()) {
                try {
                    (*it)->getIpcChannel()->close();
                } catch (const std::exception& e) {
                    std::cerr << "Error closing channel for Kitchen #"
                            << kitchenId << ": " << e.what() << std::endl;
                    Logger::getInstance().logKitchenStatus(kitchenId,
                        "Error closing IPC channel: " + std::string(e.what()));
                }
            }

            if (kitchenProcess) {
                if (kitchenProcess->isAlive()) {
                    Logger::getInstance().logKitchenStatus(kitchenId,
                        "Terminating kitchen process");

                    if (!kitchenProcess->terminate(2000)) {
                        Logger::getInstance().logKitchenStatus(kitchenId,
                            "Failed to terminate gracefully, killing process");
                        kitchenProcess->kill();
                    }
                }

                for (auto processIt = _kitchenProcesses.begin();
                processIt != _kitchenProcesses.end(); ++processIt) {
                    if ((*processIt)->getKitchenId() == kitchenId) {
                        _kitchenProcesses.erase(processIt);
                        break;
                    }
                }
            }

            std::string parentToChildPath = "/tmp/reception_to_kitchen_"
                                        + std::to_string(kitchenId) + ".fifo";
            std::string childToParentPath = "/tmp/kitchen_to_reception_"
                                        + std::to_string(kitchenId) + ".fifo";
            unlink(parentToChildPath.c_str());
            unlink(childToParentPath.c_str());

            {
                std::lock_guard<std::mutex> loadLock(_loadsMutex);
                _kitchenLoads.erase(kitchenId);
            }

            it = _kitchens.erase(it);
            Logger::getInstance().logKitchenStatus(kitchenId,
                "Kitchen removed from active kitchens list");
        } else {
            ++it;
        }
    }
}

/**
 * @brief Attempt to assign a pizza to a specific kitchen
 *
 * @param order The pizza order to assign
 * @param kitchen The kitchen to assign the order to
 * @return true if assignment was successful, false otherwise
 */
bool Reception::assignPizzaToSpecificKitchen(const Pizza::PizzaOrder& order,
    std::shared_ptr<Kitchen>& kitchen)
{
    if (!kitchen || !kitchen->isValid())
        return false;

    auto ipcChannel = kitchen->getIpcChannel();
    if (!ipcChannel || !ipcChannel->isValid())
        return false;

    int kitchenId = kitchen->getKitchenId();
    int currentEstimatedLoad = getEstimatedKitchenLoad(kitchenId);
    int maxCapacity = kitchen->getMaxCapacity();

    if (currentEstimatedLoad >= maxCapacity)
        return false;

    try {
        Pizza::PizzaOrder singleOrder = order;
        singleOrder.quantity = 1;

        Pizza::Pizza pizza = singleOrder.createPizza();
        std::string message = "ORDER:" + std::to_string(singleOrder.orderId) +
            ":" + pizza.pack();

        for (int attempts = 0; attempts < 3; attempts++) {
            if (ipcChannel->send(message)) {
                increaseKitchenLoad(kitchenId);
                int updatedLoad = getEstimatedKitchenLoad(kitchenId);

                Logger::getInstance().logOrder(singleOrder,
                    Logger::OrderStatus::ASSIGNED, kitchenId);
                Logger::getInstance().logKitchenStatus(kitchenId,
                    "Updated load: " + std::to_string(updatedLoad) + "/"
                    + std::to_string(maxCapacity));

                return true;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        Logger::getInstance().log(Logger::LogLevel::ERROR,
            "Failed to send order to kitchen #" + std::to_string(kitchenId) +
            " after 3 attempts");
    } catch (const std::exception& e) {
        std::cerr << ColorUtils::RED << "Error sending to kitchen #"
                << kitchenId << ": " << e.what()
                << ColorUtils::RESET << std::endl;

        Logger::getInstance().log(Logger::LogLevel::ERROR,
            "Exception while sending to kitchen #" + std::to_string(kitchenId) +
            ": " + e.what());
    }

    return false;
}

/**
 * @brief Attempt to assign a pizza to the least loaded kitchen
 *
 * @param order The pizza order to assign
 * @return true if assignment was successful, false otherwise
 */
bool Reception::assignPizzaToKitchen(const Pizza::PizzaOrder& order)
{
    auto leastLoadedKitchen = findLeastLoadedKitchen();

    if (leastLoadedKitchen && leastLoadedKitchen->isValid())
        return assignPizzaToSpecificKitchen(order, leastLoadedKitchen);
    return false;
}

/**
 * @brief Create a new kitchen and assign a pizza to it if possible
 *
 * @param order The pizza order to assign
 * @return true if a kitchen was created and the order was assigned, false otherwise
 */
bool Reception::createKitchenAndAssignPizza(const Pizza::PizzaOrder& order)
{
    std::cout << ColorUtils::CYAN << "Creating a new kitchen for order..."
            << ColorUtils::RESET << std::endl;
    Logger::getInstance().log(Logger::LogLevel::INFO,
        "Creating a new kitchen for order: " + order.getDescription());

    createNewKitchen();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    std::unique_lock<std::mutex> lock(_kitchensMutex);
    if (!_kitchens.empty()) {
        auto kitchen = _kitchens.back();
        lock.unlock();

        if (kitchen && kitchen->isValid()) {
            bool result = assignPizzaToSpecificKitchen(order, kitchen);
            if (!result) {
                Logger::getInstance().log(Logger::LogLevel::ERROR,
                    "Failed to assign order to newly created kitchen #" +
                    std::to_string(kitchen->getKitchenId()));
            }
            return result;
        } else {
            Logger::getInstance().log(Logger::LogLevel::ERROR,
                "Newly created kitchen is not valid");
        }
    } else {
        Logger::getInstance().log(Logger::LogLevel::ERROR,
            "Kitchen creation failed");
    }

    return false;
}

/**
 * @brief Check all kitchen connections to identify any that have closed
 *
 * This method is used before displaying kitchen status to ensure we
 * immediately detect kitchens that have shutdown but haven't been removed yet
 */
void Reception::checkKitchenConnections() const
{
    std::unique_lock<std::mutex> lock(_kitchensMutex);

    for (const auto& kitchen : _kitchens) {
        kitchen->isValid();
    }
}

/**
 * @brief Monitor kitchen processes for state changes
 *
 * This method checks the state of all kitchen processes and removes
 * any that have died or failed. It provides proactive process monitoring.
 */
void Reception::monitorKitchenProcesses()
{
    std::unique_lock<std::mutex> lock(_kitchensMutex);

    for (auto processIt = _kitchenProcesses.begin(); processIt != _kitchenProcesses.end();) {
        auto& process = *processIt;
        int kitchenId = process->getKitchenId();

        if (!process->isAlive()) {
            Process::ProcessState state = process->getState();

            if (state == Process::ProcessState::TERMINATED) {
                Logger::getInstance().logKitchenStatus(kitchenId,
                    "Kitchen process terminated normally (exit code: " +
                    std::to_string(process->getExitStatus()) + ")");
            } else if (state == Process::ProcessState::KILLED) {
                Logger::getInstance().logKitchenStatus(kitchenId,
                    "Kitchen process was killed");
            } else if (state == Process::ProcessState::FAILED) {
                Logger::getInstance().logKitchenStatus(kitchenId,
                    "Kitchen process failed");
            }

            for (auto kitchenIt = _kitchens.begin();
            kitchenIt != _kitchens.end(); ++kitchenIt) {
                if ((*kitchenIt)->getKitchenId() == kitchenId) {
                    _kitchens.erase(kitchenIt);
                    break;
                }
            }

            {
                std::lock_guard<std::mutex> loadLock(_loadsMutex);
                _kitchenLoads.erase(kitchenId);
            }

            processIt = _kitchenProcesses.erase(processIt);
        } else {
            ++processIt;
        }
    }
}

/**
 * @brief Create a new order tracker for a batch of pizza orders
 *
 * @param orders The pizza orders to track
 * @return The order ID assigned to this batch
 */
int Reception::createNewOrder(const std::vector<Pizza::PizzaOrder>& orders)
{
    std::lock_guard<std::mutex> lock(_ordersMutex);
    int orderId = _nextOrderId++;

    OrderTracker tracker;
    tracker.orderId = orderId;
    tracker.orders = orders;
    tracker.timestamp = std::time(nullptr);

    int totalPizzas = 0;
    for (const auto& order : orders) {
        if (order.isValid) {
            totalPizzas += order.quantity;
        }
    }

    tracker.totalPizzas = totalPizzas;
    tracker.completedPizzas = 0;
    _orderTrackers[orderId] = tracker;

    Logger::getInstance().log(Logger::LogLevel::INFO,
        "Created new order #" + std::to_string(orderId) +
        " with " + std::to_string(totalPizzas) + " pizzas");

    return orderId;
}

/**
 * @brief Handle notification that a pizza has been cooked
 *
 * @param orderId The order ID the pizza belongs to
 * @param pizza The pizza that was cooked
 * @param kitchenId The ID of the kitchen that cooked the pizza
 */
void Reception::handlePizzaCooked(int orderId, const Pizza::PizzaOrder& pizza, int kitchenId)
{
    std::lock_guard<std::mutex> lock(_ordersMutex);

    if (_orderTrackers.find(orderId) == _orderTrackers.end()) {
        Logger::getInstance().log(Logger::LogLevel::WARNING,
            "Received cooked pizza notification for unknown order #" +
            std::to_string(orderId));
        return;
    }

    auto& tracker = _orderTrackers[orderId];
    tracker.completedPizzas++;

    Logger::getInstance().log(Logger::LogLevel::INFO,
        "Pizza " + pizza.getDescription() + " from order #" + std::to_string(orderId) +
        " cooked by Kitchen #" + std::to_string(kitchenId) +
        " (" + std::to_string(tracker.completedPizzas) + "/" +
        std::to_string(tracker.totalPizzas) + " completed)");

    decreaseKitchenLoad(kitchenId);

    if (tracker.isComplete()) {
        std::string orderDesc = tracker.getDescription();

        std::cout << std::endl << ColorUtils::BOLD << ColorUtils::GREEN
                  << "ORDER COMPLETE: " << ColorUtils::CYAN
                  << orderDesc << ColorUtils::MAGENTA
                  << " in : " << tracker.getElapsedTime() << " seconds"
                  << ColorUtils::RESET << std::endl;
        std::cout << ColorUtils::GREEN << "Plazza> "
                  << ColorUtils::RESET;
        std::cout.flush();

        Logger::getInstance().log(Logger::LogLevel::INFO,
            "Order #" + std::to_string(orderId) + " is now complete");

        _orderTrackers.erase(orderId);
    }
}

/**
 * @brief Check for any completed orders and remove them from tracking
 */
void Reception::checkCompletedOrders()
{
    std::lock_guard<std::mutex> lock(_ordersMutex);

    for (auto it = _orderTrackers.begin(); it != _orderTrackers.end();) {
        if (it->second.isComplete()) {
            int orderId = it->first;
            std::string orderDesc = it->second.getDescription();

            std::cout << std::endl << ColorUtils::BOLD << ColorUtils::GREEN
                  << "ORDER COMPLETE: " << ColorUtils::CYAN
                  << orderDesc << ColorUtils::MAGENTA
                  << " in : " << it->second.getElapsedTime() << " seconds"
                  << ColorUtils::RESET << std::endl;

            std::cout << ColorUtils::GREEN << "Plazza> "
                  << ColorUtils::RESET;
            std::cout.flush();

            Logger::getInstance().log(Logger::LogLevel::INFO,
                "Order #" + std::to_string(orderId) + " is now complete");

            it = _orderTrackers.erase(it);
        } else {
            ++it;
        }
    }
}

/**
 * @brief Process a pizza cooked message from a kitchen
 *
 * @param message The message from the kitchen
 * @param kitchenId The ID of the kitchen that sent the message
 */
void Reception::processPizzaCookedMessage(const std::string& message, int kitchenId)
{
    if (message.find("PIZZA_COOKED:") != 0)
        return;

    std::string data = message.substr(13);
    std::vector<std::string> parts;
    std::stringstream ss(data);
    std::string part;

    while (std::getline(ss, part, ':')) {
        parts.push_back(part);
    }

    if (parts.size() < 2) {
        Logger::getInstance().log(Logger::LogLevel::WARNING,
            "Invalid PIZZA_COOKED message format: " + message);
        return;
    }

    try {
        int orderId = std::stoi(parts[0]);
        std::string packedPizzaData = data.find_first_of(':') != std::string::npos
            ? data.substr(data.find_first_of(':') + 1)
            : parts[1];
        Pizza::Pizza pizza = Pizza::Pizza::unpack(packedPizzaData);
        Pizza::PizzaOrder order;
        order.isValid = true;
        order.pizzaId = pizza.getPizzaId();
        order.size = pizza.getSize();
        order.orderId = orderId;
        order.quantity = 1;

        handlePizzaCooked(orderId, order, kitchenId);
    } catch (const std::exception& e) {
        Logger::getInstance().log(Logger::LogLevel::ERROR,
            "Error processing PIZZA_COOKED message: " + std::string(e.what()));
    }
}

/**
 * @brief Run the reception process
 */
void Reception::run()
{
    _running = true;
    displayWelcomeMessage();
    Logger::getInstance().log(Logger::LogLevel::INFO, "Plazza application started");

    startListenerThread();
    std::string command;

    while (_running) {
        std::cout << ColorUtils::BOLD << ColorUtils::GREEN << "Plazza> "
                  << ColorUtils::RESET;

        if (std::getline(std::cin, command)) {
            processCommand(command);
            if (!_running) {
                break;
            }
        } else {
            Logger::getInstance().log(Logger::LogLevel::INFO,
                "End of input, stopping reception");
            stop();
            break;
        }
    }

    stopListenerThread();
    Logger::getInstance().log(Logger::LogLevel::INFO, "Plazza application closing");
}

/**
 * @brief Calculate the number of kitchens required to handle a certain number of pizzas
 *
 * Each kitchen can handle 2 * number of cooks pizzas at most
 *
 * @param totalPizzaCount Total number of pizzas to be cooked
 * @return The number of kitchens required to handle the order
 */
int Reception::calculateRequiredKitchens(int totalPizzaCount) const
{
    if (totalPizzaCount <= 0)
        return 0;

    int maxPizzasPerKitchen = 2 * _config.getCooksPerKitchen();
    if (maxPizzasPerKitchen <= 0)
        return 1;

    return std::max(1, (totalPizzaCount + maxPizzasPerKitchen - 1) / maxPizzasPerKitchen);
}

/**
 * @brief Create the necessary number of kitchens if we don't have enough already
 *
 * @param requiredCount The number of kitchens required
 */
void Reception::createNecessaryKitchens(int requiredCount)
{
    std::unique_lock<std::mutex> lock(_kitchensMutex);
    int validKitchenCount = 0;

    for (const auto& kitchen : _kitchens) {
        if (kitchen->isValid()) {
            validKitchenCount++;
        }
    }

    int kitchensToCreate = requiredCount - validKitchenCount;
    if (kitchensToCreate > 0) {
        std::cout << ColorUtils::CYAN << "Creating " << kitchensToCreate
                  << " new kitchen(s)..." << ColorUtils::RESET << std::endl;
        Logger::getInstance().log(Logger::LogLevel::INFO,
            "Creating " + std::to_string(kitchensToCreate) + " new kitchen(s)");

        lock.unlock();
        for (int i = 0; i < kitchensToCreate; i++) {
            createNewKitchen();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

/**
 * @brief Get the estimated load for a specific kitchen
 *
 * @param kitchenId The ID of the kitchen to check
 * @return The current estimated load
 */
int Reception::getEstimatedKitchenLoad(int kitchenId) const
{
    std::lock_guard<std::mutex> lock(_loadsMutex);
    if (_kitchenLoads.count(kitchenId) > 0) {
        return _kitchenLoads.at(kitchenId);
    }
    return 0;
}


/**
 * @brief Increase the tracked load of a specific kitchen
 *
 * @param kitchenId The ID of the kitchen to update
 */
void Reception::increaseKitchenLoad(int kitchenId)
{
    std::lock_guard<std::mutex> lock(_loadsMutex);
    _kitchenLoads[kitchenId]++;
}

/**
 * @brief Decrease the tracked load of a specific kitchen
 *
 * @param kitchenId The ID of the kitchen to update
 */
void Reception::decreaseKitchenLoad(int kitchenId)
{
    std::lock_guard<std::mutex> lock(_loadsMutex);
    if (_kitchenLoads.count(kitchenId) > 0 && _kitchenLoads[kitchenId] > 0) {
        _kitchenLoads[kitchenId]--;
    }
}


/**
 * @brief Find the kitchen with the lowest current workload
 *
 * @return A shared pointer to the least loaded kitchen, or nullptr if none found
 */
std::shared_ptr<Kitchen> Reception::findLeastLoadedKitchen()
{
    std::lock_guard<std::mutex> lock(_kitchensMutex);

    std::shared_ptr<Kitchen> leastLoadedKitchen = nullptr;
    int lowestLoad = std::numeric_limits<int>::max();
    float lowestLoadPercentage = 1.0f;

    for (const auto& kitchen : _kitchens) {
        if (!kitchen->isValid())
            continue;

        int kitchenId = kitchen->getKitchenId();
        int actualLoad = kitchen->getCurrentLoad();
        int estimatedLoad = getEstimatedKitchenLoad(kitchenId);
        int effectiveLoad = std::max(actualLoad, estimatedLoad);
        int maxCapacity = kitchen->getMaxCapacity();

        if (effectiveLoad >= maxCapacity)
            continue;

        float loadPercentage = (maxCapacity > 0) ?
            static_cast<float>(effectiveLoad) / static_cast<float>(maxCapacity) : 1.0f;

        if (loadPercentage < lowestLoadPercentage ||
            (loadPercentage == lowestLoadPercentage && effectiveLoad < lowestLoad)) {
            lowestLoad = effectiveLoad;
            lowestLoadPercentage = loadPercentage;
            leastLoadedKitchen = kitchen;
        }
    }

    return leastLoadedKitchen;
}

/**
 * @brief Démarre le thread d'écoute pour les messages des cuisines
 */
void Reception::startListenerThread()
{
    _listenerRunning = true;
    _listenerThread = std::thread(&Reception::listenerThreadFunction, this);
    Logger::getInstance().log(Logger::LogLevel::INFO, "Listener thread started");
}

/**
 * @brief Arrête le thread d'écoute
 */
void Reception::stopListenerThread()
{
    if (!_listenerRunning)
        return;

    {
        std::unique_lock<std::mutex> lock(_listenerMutex);
        _listenerRunning = false;
    }
    _listenerCondVar.notify_all();

    if (_listenerThread.joinable()) {
        _listenerThread.join();
    }
    Logger::getInstance().log(Logger::LogLevel::INFO, "Listener thread stopped");
}

/**
 * @brief Fonction exécutée par le thread d'écoute
 *
 * Cette fonction vérifie en continu les messages des cuisines et met à jour
 * le suivi des commandes en conséquence.
 */
void Reception::listenerThreadFunction()
{
    while (_listenerRunning) {
        checkKitchenMessages();
        monitorKitchenProcesses();

        std::unique_lock<std::mutex> lock(_listenerMutex);
        _listenerCondVar.wait_for(lock, std::chrono::milliseconds(100), [this] {
            return !_listenerRunning;
        });
    }
}
