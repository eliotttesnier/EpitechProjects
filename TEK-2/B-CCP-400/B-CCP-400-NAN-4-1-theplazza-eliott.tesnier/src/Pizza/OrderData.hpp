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

namespace Pizza {

/**
 * @brief Structure representing a parsed pizza order with validation status
 */
struct PizzaOrder {
    PizzaType type;
    PizzaSize size;
    int quantity;
    int orderId;

    bool isValid;
    std::string errorMessage;

    PizzaOrder() :
        type(static_cast<PizzaType>(0)),
        size(static_cast<PizzaSize>(0)),
        quantity(0),
        orderId(0),
        isValid(false),
        errorMessage("") {}

    /**
     * @brief Constructor with all fields
     * @param t Pizza type
     * @param s Pizza size
     * @param q Quantity
     * @param id Order ID
     * @param valid Validity flag
     * @param error Error message if invalid
     */
    PizzaOrder(PizzaType t, PizzaSize s, int q, int id = 0, bool valid = true,
                const std::string& error = "")
        : type(t), size(s), quantity(q), orderId(id), isValid(valid), errorMessage(error) {}

    /**
     * @brief Serialize the order to a string for IPC
     * @return Serialized string representation
     */
    std::string serialize() const {
        std::stringstream ss;
        ss << static_cast<int>(type) << ";"
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
            order.type = static_cast<PizzaType>(std::stoi(token));

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
            return TYPE_NAMES.at(type) + " " + SIZE_NAMES.at(size) + " x" + std::to_string(quantity);
        } catch (const std::out_of_range& e) {
            return "Invalid pizza configuration";
        }
    }

    /**
     * @brief Validate the current order data
     * @return True if the order is valid, false otherwise
     */
    bool validate() {
        if (type == static_cast<PizzaType>(0) || TYPE_NAMES.find(type) == TYPE_NAMES.end()) {
            isValid = false;
            errorMessage = "Unknown pizza type";
            return false;
        }

        if (size == static_cast<PizzaSize>(0) || SIZE_NAMES.find(size) == SIZE_NAMES.end()) {
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
        return Pizza(type, size, orderId);
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
