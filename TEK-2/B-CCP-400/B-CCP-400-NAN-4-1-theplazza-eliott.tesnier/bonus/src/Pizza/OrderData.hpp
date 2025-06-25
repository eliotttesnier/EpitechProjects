/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** OrderData - Pizza order data structures for IPC and order processing
*/

#pragma once

#include <string>
#include <sstream>
#include <vector>
#include "Pizza.hpp"
#include "PizzaConfig.hpp"

namespace Pizza {

/**
 * @brief Structure representing a parsed pizza order with validation status
 */
struct PizzaOrder {
    std::string pizzaId;
    PizzaSize size;
    int quantity;
    int orderId;

    bool isValid;
    std::string errorMessage;

    PizzaOrder() :
        pizzaId(""),
        size(static_cast<PizzaSize>(0)),
        quantity(0),
        orderId(0),
        isValid(false),
        errorMessage("") {}

    /**
     * @brief Constructor with all fields
     * @param id Pizza ID
     * @param s Pizza size
     * @param q Quantity
     * @param orderNum Order ID
     * @param valid Validity flag
     * @param error Error message if invalid
     */
    PizzaOrder(const std::string& id, PizzaSize s, int q, int orderNum = 0, bool valid = true,
                const std::string& error = "")
        : pizzaId(id), size(s), quantity(q), orderId(orderNum), isValid(valid), errorMessage(error) {}

    /**
     * @brief Legacy constructor for backward compatibility
     * @param pizzaName Pizza name
     * @param s Pizza size
     * @param q Quantity
     * @param orderNum Order ID
     * @param valid Validity flag
     * @param error Error message if invalid
     */
    PizzaOrder(const std::string& pizzaName, const std::string& sizeStr, int q, int orderNum = 0, bool valid = true,
                const std::string& error = "")
        : quantity(q), orderId(orderNum), isValid(valid), errorMessage(error) {
        auto& config = PizzaConfig::getInstance();
        pizzaId = config.findPizzaIdByName(pizzaName);
        size = PizzaConfig::stringToSize(sizeStr);

        if (pizzaId.empty()) {
            isValid = false;
            errorMessage = "Unknown pizza: " + pizzaName;
        }
    }

    /**
     * @brief Serialize the order to a string for IPC
     * @return Serialized string representation
     */
    std::string serialize() const {
        std::stringstream ss;
        ss << pizzaId << ";"
           << static_cast<int>(size) << ";"
           << quantity << ";"
           << orderId << ";"
           << (isValid ? "1" : "0") << ";"
           << errorMessage;
        return ss.str();
    }

    /**
     * @brief Deserialize from a string
     * @param data Serialized string data
     * @return Deserialized PizzaOrder object
     */
    static PizzaOrder deserialize(const std::string& data) {
        PizzaOrder order;
        std::stringstream ss(data);
        std::string token;

        if (std::getline(ss, token, ';'))
            order.pizzaId = token;

        if (std::getline(ss, token, ';'))
            order.size = static_cast<PizzaSize>(std::stoi(token));

        if (std::getline(ss, token, ';'))
            order.quantity = std::stoi(token);

        if (std::getline(ss, token, ';'))
            order.orderId = std::stoi(token);

        if (std::getline(ss, token, ';'))
            order.isValid = (token == "1");

        std::getline(ss, order.errorMessage);
        return order;
    }

    /**
     * @brief Get a human-readable description of the order
     * @return Formatted string representation
     */
    std::string getDescription() const {
        if (!isValid)
            return "Invalid order: " + errorMessage;

        try {
            auto& config = PizzaConfig::getInstance();
            const auto& pizzaDef = config.getPizzaDefinition(pizzaId);
            std::string sizeName = PizzaConfig::sizeToString(size);
            return pizzaDef.name + " " + sizeName + " x" + std::to_string(quantity);
        } catch (const std::exception& e) {
            return "Invalid pizza configuration";
        }
    }

    /**
     * @brief Validate the current order data
     * @return True if the order is valid, false otherwise
     */
    bool validate() {
        auto& config = PizzaConfig::getInstance();

        if (pizzaId.empty() || !config.pizzaExists(pizzaId)) {
            isValid = false;
            errorMessage = "Unknown pizza ID: " + pizzaId;
            return false;
        }

        if (size == static_cast<PizzaSize>(0)) {
            isValid = false;
            errorMessage = "Invalid size";
            return false;
        }

        if (quantity <= 0) {
            isValid = false;
            errorMessage = "Invalid quantity: must be positive";
            return false;
        }

        isValid = true;
        errorMessage = "";
        return true;
    }

    /**
     * @brief Create a Pizza object from this order
     * @return A new Pizza object
     */
    Pizza createPizza() const {
        return Pizza(pizzaId, size, orderId);
    }
};

/**
 * @brief Structure representing a batch of pizza orders
 */
struct OrderBatch {
    std::vector<PizzaOrder> orders;

    /**
     * @brief Serialize the batch to a string for IPC
     * @return Serialized string representation
     */
    std::string serialize() const {
        std::stringstream ss;
        ss << orders.size();

        for (const auto& order : orders) {
            ss << "|" << order.serialize();
        }

        return ss.str();
    }

    /**
     * @brief Deserialize from a string
     * @param data Serialized string data
     * @return Deserialized OrderBatch object
     */
    static OrderBatch deserialize(const std::string& data) {
        OrderBatch batch;
        std::stringstream ss(data);
        std::string countStr;
        std::getline(ss, countStr, '|');

        int count = std::stoi(countStr);
        std::string orderData;

        for (int i = 0; i < count && std::getline(ss, orderData, '|'); i++) {
            batch.orders.push_back(PizzaOrder::deserialize(orderData));
        }

        return batch;
    }

    /**
     * @brief Count valid orders in the batch
     * @return Number of valid orders
     */
    size_t validCount() const {
        size_t count = 0;
        for (const auto& order : orders) {
            if (order.isValid) {
                count++;
            }
        }
        return count;
    }
};

} // namespace Pizza
