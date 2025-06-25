/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** OrderData unit tests
*/

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <sstream>

#include "../../src/Pizza/OrderData.hpp"
#include "../../src/Pizza/Pizza.hpp"

class OrderDataTest : public ::testing::Test {
protected:
    Pizza::PizzaOrder createValidOrder() {
        return Pizza::PizzaOrder(Pizza::Regina, Pizza::M, 2);
    }
};

// Test PizzaOrder default constructor
TEST_F(OrderDataTest, PizzaOrder_DefaultConstructor) {
    Pizza::PizzaOrder order;

    ASSERT_EQ(order.type, static_cast<Pizza::PizzaType>(0));
    ASSERT_EQ(order.size, static_cast<Pizza::PizzaSize>(0));
    ASSERT_EQ(order.quantity, 0);
    ASSERT_FALSE(order.isValid);
    ASSERT_EQ(order.errorMessage, "");
}

// Test PizzaOrder explicit constructor
TEST_F(OrderDataTest, PizzaOrder_ExplicitConstructor) {
    Pizza::PizzaOrder order(Pizza::Regina, Pizza::M, 2);

    ASSERT_EQ(order.type, Pizza::Regina);
    ASSERT_EQ(order.size, Pizza::M);
    ASSERT_EQ(order.quantity, 2);
    ASSERT_TRUE(order.isValid);
    ASSERT_EQ(order.errorMessage, "");
}

// Test PizzaOrder serialization
TEST_F(OrderDataTest, PizzaOrder_Serialization) {
    Pizza::PizzaOrder order(Pizza::Regina, Pizza::M, 2);
    order.isValid = true;
    order.errorMessage = "No error";

    std::string serialized = order.serialize();

    // Format: type;size;quantity;isValid;errorMessage
    ASSERT_EQ(serialized, "1;2;2;0;1;No error");
}

// Test PizzaOrder deserialization
TEST_F(OrderDataTest, PizzaOrder_Deserialization) {
    std::string serialized = "1;2;2;0;1;No error";

    Pizza::PizzaOrder order = Pizza::PizzaOrder::deserialize(serialized);

    ASSERT_EQ(order.type, Pizza::Regina);
    ASSERT_EQ(order.size, Pizza::M);
    ASSERT_EQ(order.quantity, 2);
    ASSERT_TRUE(order.isValid);
    ASSERT_EQ(order.errorMessage, "No error");
}

// Test PizzaOrder getDescription for valid order
TEST_F(OrderDataTest, PizzaOrder_GetDescription_Valid) {
    Pizza::PizzaOrder order(Pizza::Regina, Pizza::M, 2);

    std::string description = order.getDescription();

    ASSERT_EQ(description, "Regina M x2");
}

// Test PizzaOrder getDescription for invalid order
TEST_F(OrderDataTest, PizzaOrder_GetDescription_Invalid) {
    Pizza::PizzaOrder order;
    order.errorMessage = "Test error";

    std::string description = order.getDescription();

    ASSERT_EQ(description, "Invalid order: Test error");
}

// Test PizzaOrder getDescription with invalid pizza configuration
TEST_F(OrderDataTest, PizzaOrder_GetDescription_InvalidPizzaConfig) {
    Pizza::PizzaOrder order;

    order.type = static_cast<Pizza::PizzaType>(1000);
    order.size = Pizza::M;
    order.quantity = 2;
    order.isValid = true;

    std::string description = order.getDescription();

    ASSERT_EQ(description, "Invalid pizza configuration");
}

// Test PizzaOrder validate with valid data
TEST_F(OrderDataTest, PizzaOrder_Validate_Valid) {
    Pizza::PizzaOrder order(Pizza::Regina, Pizza::M, 2);

    bool result = order.validate();

    ASSERT_TRUE(result);
    ASSERT_TRUE(order.isValid);
    ASSERT_EQ(order.errorMessage, "");
}

// Test PizzaOrder validate with invalid type
TEST_F(OrderDataTest, PizzaOrder_Validate_InvalidType) {
    Pizza::PizzaOrder order(static_cast<Pizza::PizzaType>(0), Pizza::M, 2);

    bool result = order.validate();

    ASSERT_FALSE(result);
    ASSERT_FALSE(order.isValid);
    ASSERT_NE(order.errorMessage.find("Unknown pizza type"), std::string::npos);
}

// Test PizzaOrder validate with invalid size
TEST_F(OrderDataTest, PizzaOrder_Validate_InvalidSize) {
    Pizza::PizzaOrder order(Pizza::Regina, static_cast<Pizza::PizzaSize>(0), 2);

    bool result = order.validate();

    ASSERT_FALSE(result);
    ASSERT_FALSE(order.isValid);
    ASSERT_NE(order.errorMessage.find("Invalid size"), std::string::npos);
}

// Test PizzaOrder validate with zero quantity
TEST_F(OrderDataTest, PizzaOrder_Validate_ZeroQuantity) {
    Pizza::PizzaOrder order(Pizza::Regina, Pizza::M, 0);

    bool result = order.validate();

    ASSERT_FALSE(result);
    ASSERT_FALSE(order.isValid);
    ASSERT_NE(order.errorMessage.find("Invalid quantity"), std::string::npos);
}

// Test PizzaOrder validate with excessive quantity
TEST_F(OrderDataTest, PizzaOrder_Validate_ExcessiveQuantity) {
    Pizza::PizzaOrder order(Pizza::Regina, Pizza::M, 100);

    bool result = order.validate();

    ASSERT_TRUE(result);
    ASSERT_TRUE(order.isValid);
    ASSERT_EQ(order.errorMessage.find("Invalid quantity"), std::string::npos);
}

// Test PizzaOrder createPizza
TEST_F(OrderDataTest, PizzaOrder_CreatePizza) {
    Pizza::PizzaOrder order(Pizza::Regina, Pizza::M, 2);

    Pizza::Pizza pizza = order.createPizza();

    ASSERT_EQ(pizza.getType(), Pizza::Regina);
    ASSERT_EQ(pizza.getSize(), Pizza::M);
}

// Test OrderBatch serialization
TEST_F(OrderDataTest, OrderBatch_Serialization) {
    Pizza::OrderBatch batch;
    batch.orders.push_back(Pizza::PizzaOrder(Pizza::Regina, Pizza::M, 2));
    batch.orders.push_back(Pizza::PizzaOrder(Pizza::Margarita, Pizza::L, 1));

    std::string serialized = batch.serialize();

    // Format: count|order1|order2...
    std::string expected = "2|1;2;2;0;1;|2;4;1;0;1;";
    ASSERT_EQ(serialized, expected);
}

// Test OrderBatch deserialization
TEST_F(OrderDataTest, OrderBatch_Deserialization) {
    std::string serialized = "2|1;2;2;1;|2;4;1;1;";

    Pizza::OrderBatch batch = Pizza::OrderBatch::deserialize(serialized);

    ASSERT_EQ(batch.orders.size(), 2);
    ASSERT_EQ(batch.orders[0].type, Pizza::Regina);
    ASSERT_EQ(batch.orders[0].size, Pizza::M);
    ASSERT_EQ(batch.orders[0].quantity, 2);
    ASSERT_EQ(batch.orders[1].type, Pizza::Margarita);
    ASSERT_EQ(batch.orders[1].size, Pizza::L);
    ASSERT_EQ(batch.orders[1].quantity, 1);
}

// Test OrderBatch validCount
TEST_F(OrderDataTest, OrderBatch_ValidCount) {
    Pizza::OrderBatch batch;
    batch.orders.push_back(Pizza::PizzaOrder(Pizza::Regina, Pizza::M, 2));

    Pizza::PizzaOrder invalidOrder;
    invalidOrder.isValid = false;
    batch.orders.push_back(invalidOrder);

    batch.orders.push_back(Pizza::PizzaOrder(Pizza::Margarita, Pizza::L, 1));

    size_t count = batch.validCount();

    ASSERT_EQ(count, 2);
}

// Test Pizza pack method with valid pizza
TEST_F(OrderDataTest, Pizza_Pack_Valid) {
    Pizza::Pizza pizza(Pizza::Regina, Pizza::M, 0);

    std::string serialized = pizza.pack();

    ASSERT_EQ(serialized, "Regina:M:0");
}

// Test Pizza pack method with different pizza type and size
TEST_F(OrderDataTest, Pizza_Pack_DifferentTypes) {
    Pizza::Pizza pizza1(Pizza::Margarita, Pizza::S, 0);
    Pizza::Pizza pizza2(Pizza::Americana, Pizza::XL, 0);
    Pizza::Pizza pizza3(Pizza::Fantasia, Pizza::XXL, 0);

    ASSERT_EQ(pizza1.pack(), "Margarita:S:0");
    ASSERT_EQ(pizza2.pack(), "Americana:XL:0");
    ASSERT_EQ(pizza3.pack(), "Fantasia:XXL:0");
}

// Test Pizza unpack method with valid data
TEST_F(OrderDataTest, Pizza_Unpack_Valid) {
    std::string data = "Regina:M:0";

    Pizza::Pizza pizza = Pizza::Pizza::unpack(data);

    ASSERT_EQ(pizza.getType(), Pizza::Regina);
    ASSERT_EQ(pizza.getSize(), Pizza::M);
    ASSERT_EQ(pizza.pack(), data);
}

// Test Pizza unpack method with all valid types
TEST_F(OrderDataTest, Pizza_Unpack_AllTypes) {
    std::string data1 = "Regina:S";
    std::string data2 = "Margarita:M";
    std::string data3 = "Americana:L";
    std::string data4 = "Fantasia:XL";

    Pizza::Pizza pizza1 = Pizza::Pizza::unpack(data1);
    Pizza::Pizza pizza2 = Pizza::Pizza::unpack(data2);
    Pizza::Pizza pizza3 = Pizza::Pizza::unpack(data3);
    Pizza::Pizza pizza4 = Pizza::Pizza::unpack(data4);

    ASSERT_EQ(pizza1.getType(), Pizza::Regina);
    ASSERT_EQ(pizza1.getSize(), Pizza::S);

    ASSERT_EQ(pizza2.getType(), Pizza::Margarita);
    ASSERT_EQ(pizza2.getSize(), Pizza::M);

    ASSERT_EQ(pizza3.getType(), Pizza::Americana);
    ASSERT_EQ(pizza3.getSize(), Pizza::L);

    ASSERT_EQ(pizza4.getType(), Pizza::Fantasia);
    ASSERT_EQ(pizza4.getSize(), Pizza::XL);
}

// Test Pizza unpack method with invalid data
TEST_F(OrderDataTest, Pizza_Unpack_Invalid) {
    std::string emptyData = "";
    std::string invalidData = "Invalid";
    std::string badFormatData = "Regina-M"; // Wrong delimiter
    std::string unknownTypeData = "Pepperoni:M"; // Unknown type
    std::string unknownSizeData = "Regina:XS"; // Unknown size

    Pizza::Pizza emptyPizza = Pizza::Pizza::unpack(emptyData);
    Pizza::Pizza invalidPizza = Pizza::Pizza::unpack(invalidData);
    Pizza::Pizza badFormatPizza = Pizza::Pizza::unpack(badFormatData);
    Pizza::Pizza unknownTypePizza = Pizza::Pizza::unpack(unknownTypeData);
    Pizza::Pizza unknownSizePizza = Pizza::Pizza::unpack(unknownSizeData);

    // Default pizza should be Margarita S
    ASSERT_EQ(emptyPizza.getType(), Pizza::Margarita);
    ASSERT_EQ(emptyPizza.getSize(), Pizza::S);

    ASSERT_EQ(invalidPizza.getType(), Pizza::Margarita);
    ASSERT_EQ(invalidPizza.getSize(), Pizza::S);

    ASSERT_EQ(badFormatPizza.getType(), Pizza::Margarita);
    ASSERT_EQ(badFormatPizza.getSize(), Pizza::S);

    ASSERT_EQ(unknownTypePizza.getType(), Pizza::Margarita);
    ASSERT_EQ(unknownTypePizza.getSize(), Pizza::M);

    ASSERT_EQ(unknownSizePizza.getType(), Pizza::Regina);
    ASSERT_EQ(unknownSizePizza.getSize(), Pizza::S);
}
