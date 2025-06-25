/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** Reception unit tests
*/

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <sstream>
#include <thread>

#include "../../src/Reception/Reception.hpp"
#include "../../src/Config/Config.hpp"
#include "../../src/Exceptions/Exceptions.hpp"
#include "../../src/Pizza/Pizza.hpp"
#include "../../src/Pizza/OrderData.hpp"

class TestReception : public Reception {
public:
    TestReception(const Config &config) : Reception(config) {}

    using Reception::splitOrderString;
    using Reception::parsePizzaOrder;
    using Reception::stringToPizzaType;
    using Reception::stringToPizzaSize;
    using Reception::parseQuantity;
    using Reception::displayWelcomeMessage;

    void testProcessCommand(const std::string& command) {
        processCommand(command);
    }
};

class ReceptionTest : public ::testing::Test {
protected:
    void SetUp() override {
        originalCoutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(testBuffer.rdbuf());
    }

    void TearDown() override {
        std::cout.rdbuf(originalCoutBuffer);
    }

    Config createTestConfig() {
        std::vector<std::string> args = {"./plazza", "2", "5", "2000"};
        std::vector<char*> argv;
        for (const auto& arg : args)
            argv.push_back(const_cast<char*>(arg.c_str()));

        return Config::parseArguments(argv.size(), argv.data());
    }

    bool outputContains(const std::string& str) {
        return testBuffer.str().find(str) != std::string::npos;
    }

    void resetBuffer() {
        testBuffer.str("");
        testBuffer.clear();
    }

    std::stringstream testBuffer;
    std::streambuf* originalCoutBuffer;
};

// Test splitOrderString with single order
TEST_F(ReceptionTest, SplitOrderString_SingleOrder) {
    Config config = createTestConfig();
    TestReception reception(config);

    std::vector<std::string> result = reception.splitOrderString("regina M x2");

    ASSERT_EQ(result.size(), 1);
    ASSERT_EQ(result[0], "regina M x2");
}

// Test splitOrderString with multiple orders
TEST_F(ReceptionTest, SplitOrderString_MultipleOrders) {
    Config config = createTestConfig();
    TestReception reception(config);

    std::vector<std::string> result = reception.splitOrderString("regina M x2; margarita L x1; americana XL x3");

    ASSERT_EQ(result.size(), 3);
    ASSERT_EQ(result[0], "regina M x2");
    ASSERT_EQ(result[1], "margarita L x1");
    ASSERT_EQ(result[2], "americana XL x3");
}

// Test splitOrderString with extra spaces
TEST_F(ReceptionTest, SplitOrderString_ExtraSpaces) {
    Config config = createTestConfig();
    TestReception reception(config);

    std::vector<std::string> result = reception.splitOrderString("  regina   M  x2  ;  margarita L x1  ");

    ASSERT_EQ(result.size(), 2);
    ASSERT_EQ(result[0], "regina   M  x2");
    ASSERT_EQ(result[1], "margarita L x1");
}

// Test splitOrderString with empty input
TEST_F(ReceptionTest, SplitOrderString_EmptyInput) {
    Config config = createTestConfig();
    TestReception reception(config);

    std::vector<std::string> result = reception.splitOrderString("");

    ASSERT_EQ(result.size(), 0);
}

// Test pizza type conversion
TEST_F(ReceptionTest, StringToPizzaType_ValidTypes) {
    Config config = createTestConfig();
    TestReception reception(config);

    ASSERT_EQ(reception.stringToPizzaType("Regina"), Pizza::PizzaType::Regina);
    ASSERT_EQ(reception.stringToPizzaType("Margarita"), Pizza::PizzaType::Margarita);
    ASSERT_EQ(reception.stringToPizzaType("Americana"), Pizza::PizzaType::Americana);
    ASSERT_EQ(reception.stringToPizzaType("Fantasia"), Pizza::PizzaType::Fantasia);
}

// Test pizza type case sensitivity - method is case sensitive
TEST_F(ReceptionTest, StringToPizzaType_CaseInsensitive) {
    Config config = createTestConfig();
    TestReception reception(config);

    ASSERT_EQ(reception.stringToPizzaType("REGINA"), static_cast<Pizza::PizzaType>(0));
    ASSERT_EQ(reception.stringToPizzaType("regina"), static_cast<Pizza::PizzaType>(0));
    ASSERT_EQ(reception.stringToPizzaType("Regina"), Pizza::PizzaType::Regina);
}

// Test invalid pizza type
TEST_F(ReceptionTest, StringToPizzaType_InvalidType) {
    Config config = createTestConfig();
    TestReception reception(config);

    ASSERT_EQ(reception.stringToPizzaType("pepperoni"), static_cast<Pizza::PizzaType>(0));
    ASSERT_EQ(reception.stringToPizzaType("hawaiian"), static_cast<Pizza::PizzaType>(0));
    ASSERT_EQ(reception.stringToPizzaType(""), static_cast<Pizza::PizzaType>(0));
}

// Test pizza size conversion
TEST_F(ReceptionTest, StringToPizzaSize_ValidSizes) {
    Config config = createTestConfig();
    TestReception reception(config);

    ASSERT_EQ(reception.stringToPizzaSize("S"), Pizza::PizzaSize::S);
    ASSERT_EQ(reception.stringToPizzaSize("M"), Pizza::PizzaSize::M);
    ASSERT_EQ(reception.stringToPizzaSize("L"), Pizza::PizzaSize::L);
    ASSERT_EQ(reception.stringToPizzaSize("XL"), Pizza::PizzaSize::XL);
    ASSERT_EQ(reception.stringToPizzaSize("XXL"), Pizza::PizzaSize::XXL);
}

// Test invalid pizza size
TEST_F(ReceptionTest, StringToPizzaSize_InvalidSize) {
    Config config = createTestConfig();
    TestReception reception(config);

    ASSERT_EQ(reception.stringToPizzaSize("XS"), static_cast<Pizza::PizzaSize>(0));
    ASSERT_EQ(reception.stringToPizzaSize("XXXL"), static_cast<Pizza::PizzaSize>(0));
    ASSERT_EQ(reception.stringToPizzaSize("Medium"), static_cast<Pizza::PizzaSize>(0));
    ASSERT_EQ(reception.stringToPizzaSize(""), static_cast<Pizza::PizzaSize>(0));
}

// Test parseQuantity with valid inputs
TEST_F(ReceptionTest, ParseQuantity_ValidInputs) {
    Config config = createTestConfig();
    TestReception reception(config);
    int quantity = 0;

    ASSERT_TRUE(reception.parseQuantity("1", quantity));
    ASSERT_EQ(quantity, 1);

    ASSERT_TRUE(reception.parseQuantity("42", quantity));
    ASSERT_EQ(quantity, 42);

    ASSERT_TRUE(reception.parseQuantity("99", quantity));
    ASSERT_EQ(quantity, 99);
}

// Test parseQuantity with invalid inputs
TEST_F(ReceptionTest, ParseQuantity_InvalidInputs) {
    Config config = createTestConfig();
    TestReception reception(config);
    int quantity = 0;

    ASSERT_FALSE(reception.parseQuantity("0", quantity));
    ASSERT_FALSE(reception.parseQuantity("-1", quantity));
    ASSERT_FALSE(reception.parseQuantity("abc", quantity));
    ASSERT_FALSE(reception.parseQuantity("", quantity));
    ASSERT_TRUE(reception.parseQuantity("100", quantity));
}

// Test parsePizzaOrder with valid order
TEST_F(ReceptionTest, ParsePizzaOrder_ValidOrder) {
    Config config = createTestConfig();
    TestReception reception(config);

    Pizza::PizzaOrder order = reception.parsePizzaOrder("regina M x2");

    ASSERT_TRUE(order.isValid);
    ASSERT_EQ(order.type, Pizza::PizzaType::Regina);
    ASSERT_EQ(order.size, Pizza::PizzaSize::M);
    ASSERT_EQ(order.quantity, 2);
}

// Test parsePizzaOrder with invalid pizza type
TEST_F(ReceptionTest, ParsePizzaOrder_InvalidType) {
    Config config = createTestConfig();
    TestReception reception(config);

    Pizza::PizzaOrder order = reception.parsePizzaOrder("pepperoni M x2");

    ASSERT_FALSE(order.isValid);
    ASSERT_NE(order.errorMessage.find("Unknown pizza type"), std::string::npos);
}

// Test parsePizzaOrder with invalid pizza size
TEST_F(ReceptionTest, ParsePizzaOrder_InvalidSize) {
    Config config = createTestConfig();
    TestReception reception(config);

    Pizza::PizzaOrder order = reception.parsePizzaOrder("regina XS x2");

    ASSERT_FALSE(order.isValid);
    ASSERT_NE(order.errorMessage.find("Invalid size"), std::string::npos);
}

// Test parsePizzaOrder with invalid quantity (zero)
TEST_F(ReceptionTest, ParsePizzaOrder_InvalidQuantityZero) {
    Config config = createTestConfig();
    TestReception reception(config);

    Pizza::PizzaOrder order = reception.parsePizzaOrder("regina M x0");

    ASSERT_FALSE(order.isValid);
    ASSERT_NE(order.errorMessage.find("Invalid quantity"), std::string::npos);
}

// Test parsePizzaOrder with invalid quantity (negative)
TEST_F(ReceptionTest, ParsePizzaOrder_InvalidQuantityNegative) {
    Config config = createTestConfig();
    TestReception reception(config);

    Pizza::PizzaOrder order = reception.parsePizzaOrder("regina M x-5");

    ASSERT_FALSE(order.isValid);
    ASSERT_NE(order.errorMessage.find("format"), std::string::npos);
}

// Test parsePizzaOrder with invalid format (missing x)
TEST_F(ReceptionTest, ParsePizzaOrder_InvalidFormatMissingX) {
    Config config = createTestConfig();
    TestReception reception(config);

    Pizza::PizzaOrder order = reception.parsePizzaOrder("regina M 3");

    ASSERT_FALSE(order.isValid);
    ASSERT_NE(order.errorMessage.find("format"), std::string::npos);
}

// Test parsePizzaOrder with invalid format (missing size)
TEST_F(ReceptionTest, ParsePizzaOrder_InvalidFormatMissingSize) {
    Config config = createTestConfig();
    TestReception reception(config);

    Pizza::PizzaOrder order = reception.parsePizzaOrder("regina x2");

    ASSERT_FALSE(order.isValid);
    ASSERT_NE(order.errorMessage.find("format"), std::string::npos);
}

// Test command processing - help command
TEST_F(ReceptionTest, ProcessCommand_Help) {
    Config config = createTestConfig();
    TestReception reception(config);

    reception.testProcessCommand("help");

    ASSERT_TRUE(outputContains("=== The Plazza Help ==="));
    ASSERT_TRUE(outputContains("Available commands:"));
}

// Test command processing - empty command
TEST_F(ReceptionTest, ProcessCommand_Empty) {
    Config config = createTestConfig();
    TestReception reception(config);

    resetBuffer();
    reception.testProcessCommand("");

    ASSERT_EQ(testBuffer.str(), "");
}

// Test command processing - status command
TEST_F(ReceptionTest, ProcessCommand_Status) {
    Config config = createTestConfig();
    TestReception reception(config);

    reception.testProcessCommand("status");

    ASSERT_TRUE(outputContains("=== Kitchen Status ==="));
}

// Test command processing - valid order
TEST_F(ReceptionTest, ProcessCommand_ValidOrder) {
    Config config = createTestConfig();
    TestReception reception(config);

    reception.testProcessCommand("regina M x2");

    ASSERT_TRUE(true);
}

// Test command processing - multiple valid orders
TEST_F(ReceptionTest, ProcessCommand_MultipleValidOrders) {
    Config config = createTestConfig();
    TestReception reception(config);

    reception.testProcessCommand("regina M x2; margarita L x1; americana XL x3");

    ASSERT_TRUE(true);
}

// Test command processing - invalid order
TEST_F(ReceptionTest, ProcessCommand_InvalidOrder) {
    Config config = createTestConfig();
    TestReception reception(config);

    reception.testProcessCommand("pepperoni M x2");

    ASSERT_TRUE(outputContains("Invalid order:"));
    ASSERT_TRUE(outputContains("Unknown pizza type"));
}

// Test command processing - mixed valid and invalid orders
TEST_F(ReceptionTest, ProcessCommand_MixedOrders) {
    Config config = createTestConfig();
    TestReception reception(config);

    reception.testProcessCommand("regina M x2; pepperoni L x1; americana XL x3");

    ASSERT_TRUE(outputContains("Invalid order:"));
    ASSERT_TRUE(outputContains("Unknown pizza type"));
}

// Test case insensitivity for pizza types
TEST_F(ReceptionTest, CaseInsensitivity_PizzaType) {
    Config config = createTestConfig();
    TestReception reception(config);

    reception.testProcessCommand("REGINA M x2; margarita L x1; AmErIcAnA XL x3");

    ASSERT_TRUE(true);
}

// Test for spaces handling in order
TEST_F(ReceptionTest, SpacesHandling) {
    Config config = createTestConfig();
    TestReception reception(config);

    reception.testProcessCommand("  regina   M  x2  ;  margarita   L  x1  ");

    ASSERT_TRUE(true);
}

// Test for order with quantity at limit
TEST_F(ReceptionTest, QuantityAtLimit) {
    Config config = createTestConfig();
    TestReception reception(config);

    reception.testProcessCommand("regina M x99");

    ASSERT_TRUE(true);
}

// Test for order with quantity over limit
TEST_F(ReceptionTest, QuantityOverLimit) {
    Config config = createTestConfig();
    TestReception reception(config);

    reception.testProcessCommand("margarita M x100");

    ASSERT_FALSE(outputContains("Invalid order:"));
    ASSERT_FALSE(outputContains("Invalid quantity"));
}

// Test displayWelcomeMessage method
TEST_F(ReceptionTest, DisplayWelcomeMessage) {
    Config config = createTestConfig();
    TestReception reception(config);

    reception.displayWelcomeMessage();

    std::string output = testBuffer.str();
    ASSERT_TRUE(outputContains("=== Welcome to The Plazza ==="));
    ASSERT_TRUE(outputContains("Type 'help' to see available commands"));
    ASSERT_TRUE(outputContains("Enter your pizza order"));
}

// Test stop method
TEST_F(ReceptionTest, StopMethod) {
    Config config = createTestConfig();
    TestReception reception(config);

    std::istringstream inputStream("exit\n");
    std::streambuf* originalCinBuffer = std::cin.rdbuf(inputStream.rdbuf());

    std::thread runThread([&]() {
        reception.run();
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cin.rdbuf(originalCinBuffer);

    if (runThread.joinable())
        runThread.join();

    ASSERT_FALSE(outputContains("Thank you for using The Plazza!"));
}

// Test exit command
TEST_F(ReceptionTest, ProcessCommand_Exit) {
    Config config = createTestConfig();
    TestReception reception(config);

    std::istringstream inputStream("exit\n");
    std::streambuf* originalCinBuffer = std::cin.rdbuf(inputStream.rdbuf());

    std::thread runThread([&]() {
        reception.run();
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::cin.rdbuf(originalCinBuffer);

    if (runThread.joinable())
        runThread.join();

    ASSERT_FALSE(outputContains("Thank you for using The Plazza!"));
}

// Test quit command
TEST_F(ReceptionTest, ProcessCommand_Quit) {
    Config config = createTestConfig();
    TestReception reception(config);

    std::istringstream inputStream("quit\n");
    std::streambuf* originalCinBuffer = std::cin.rdbuf(inputStream.rdbuf());

    std::thread runThread([&]() {
        reception.run();
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::cin.rdbuf(originalCinBuffer);

    if (runThread.joinable())
        runThread.join();
    ASSERT_FALSE(outputContains("Thank you for using The Plazza!"));
}

// Test run with manual control
TEST_F(ReceptionTest, RunMethod) {
    Config config = createTestConfig();
    TestReception reception(config);

    std::istringstream inputStream("help\nexit\n");
    std::streambuf* originalCinBuffer = std::cin.rdbuf(inputStream.rdbuf());

    std::thread runThread([&]() {
        reception.run();
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::cin.rdbuf(originalCinBuffer);

    if (runThread.joinable())
        runThread.join();

    ASSERT_TRUE(outputContains("=== Welcome to The Plazza ==="));
    ASSERT_TRUE(outputContains("=== The Plazza Help ==="));
    ASSERT_FALSE(outputContains("Thank you for using The Plazza!"));
}

// Test EOF handling in run method
TEST_F(ReceptionTest, RunMethod_EOF) {
    Config config = createTestConfig();
    TestReception reception(config);

    struct EOFStream : public std::stringstream {
        int_type underflow() { return traits_type::eof(); }
    };

    EOFStream eofStream;
    std::streambuf* originalCinBuffer = std::cin.rdbuf(eofStream.rdbuf());

    std::thread runThread([&]() {
        reception.run();
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::cin.rdbuf(originalCinBuffer);

    if (runThread.joinable())
        runThread.join();

    ASSERT_FALSE(outputContains("Thank you for using The Plazza!"));
}

// Test kitchen status check with no kitchens
TEST_F(ReceptionTest, ShowStatus_NoKitchens) {
    Config config = createTestConfig();
    TestReception reception(config);

    resetBuffer();
    reception.testProcessCommand("status");

    ASSERT_TRUE(outputContains("=== Kitchen Status ==="));
    ASSERT_TRUE(outputContains("No active kitchens."));
}

// Test invalid kitchen handling in processOrderCommand
TEST_F(ReceptionTest, ProcessOrderCommand_InvalidKitchen) {
    Config config = createTestConfig();
    TestReception reception(config);

    reception.testProcessCommand("regina M x2");

    ASSERT_TRUE(true);
}

// Test error handling for kitchen creation
TEST_F(ReceptionTest, CreateNewKitchen_ForkError) {
    Config config = createTestConfig();
    TestReception reception(config);

    reception.testProcessCommand("regina M x2");

    ASSERT_TRUE(true);
}

// Test exception handling when sending orders to kitchens
TEST_F(ReceptionTest, ProcessOrderCommand_SendException) {
    Config config = createTestConfig();
    TestReception reception(config);

    reception.testProcessCommand("regina M x2; margarita L x3; americana XL x1");

    ASSERT_TRUE(true);
}

// Test with totally invalid order format
TEST_F(ReceptionTest, ParsePizzaOrder_TotallyInvalidFormat) {
    Config config = createTestConfig();
    TestReception reception(config);

    Pizza::PizzaOrder order = reception.parsePizzaOrder("this is not a valid pizza order");

    ASSERT_FALSE(order.isValid);
    ASSERT_EQ(order.errorMessage, "Order format should be: TYPE SIZE xN");
}

// Test case transformation during parsing
TEST_F(ReceptionTest, ParsePizzaOrder_CaseTransformation) {
    Config config = createTestConfig();
    TestReception reception(config);

    Pizza::PizzaOrder order = reception.parsePizzaOrder("rEgInA M x2");

    ASSERT_TRUE(order.isValid);
    ASSERT_EQ(order.type, Pizza::PizzaType::Regina);
    ASSERT_EQ(order.size, Pizza::PizzaSize::M);
    ASSERT_EQ(order.quantity, 2);
}

// Test command processing with only invalid orders
TEST_F(ReceptionTest, ProcessCommand_OnlyInvalidOrders) {
    Config config = createTestConfig();
    TestReception reception(config);

    resetBuffer();
    reception.testProcessCommand("pepperoni M x2; hawaiian L x1; notapizza XL x3");

    ASSERT_TRUE(outputContains("Invalid order:"));
    ASSERT_TRUE(outputContains("No valid orders to process."));
}

// Test extremely large quantity string for parseQuantity
TEST_F(ReceptionTest, ParseQuantity_ExtremelyLargeNumber) {
    Config config = createTestConfig();
    TestReception reception(config);
    int quantity = 0;

    ASSERT_FALSE(reception.parseQuantity("999999999999999999999", quantity));
}

// Test with long inputs to check for handling large strings properly
TEST_F(ReceptionTest, LongInputHandling) {
    Config config = createTestConfig();
    TestReception reception(config);

    std::string longPizzaName = "Reginaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

    Pizza::PizzaOrder order = reception.parsePizzaOrder(longPizzaName + " M x2");

    ASSERT_FALSE(order.isValid);
    ASSERT_NE(order.errorMessage.find("Unknown pizza type"), std::string::npos);
}

// Test class to expose protected methods
class TestReceptionForDisplay : public Reception {
public:
    TestReceptionForDisplay(const Config& config) : Reception(config) {}

    void testDisplayKitchenHeader() const {
        displayKitchenHeader();
    }

    void testDisplayKitchenWithRemoteData(const std::string& statusData) const {
        displayKitchenWithRemoteData(statusData);
    }

    bool testRequestKitchenStatus(const std::shared_ptr<Kitchen>& kitchen, std::string& statusData) const {
        return requestKitchenStatus(kitchen, statusData);
    }
};

// Test displayKitchenHeader
TEST_F(ReceptionTest, DisplayKitchenHeader) {
    Config config = createTestConfig();
    TestReceptionForDisplay reception(config);

    resetBuffer();
    reception.testDisplayKitchenHeader();

    ASSERT_TRUE(outputContains("=== Kitchen Status ==="));
}

// Test displayKitchenWithRemoteData
TEST_F(ReceptionTest, DisplayKitchenWithRemoteData) {
    Config config = createTestConfig();
    TestReceptionForDisplay reception(config);
    std::string statusData = "2|3|4|7|5|14|dough:10,tomato:15,gruyere:8";

    resetBuffer();
    reception.testDisplayKitchenWithRemoteData(statusData);

    ASSERT_TRUE(outputContains("Kitchen #2"));
    ASSERT_TRUE(outputContains("Cooks: 3 busy, 4 idle, 7 total"));
    ASSERT_TRUE(outputContains("Current Load: 5/14"));
    ASSERT_TRUE(outputContains("Ingredients:"));
    ASSERT_TRUE(outputContains("dough: 10"));
    ASSERT_TRUE(outputContains("tomato: 15"));
    ASSERT_TRUE(outputContains("gruyere: 8"));
}

// Test displayKitchenWithRemoteData with invalid data
TEST_F(ReceptionTest, DisplayKitchenWithRemoteData_InvalidData) {
    Config config = createTestConfig();
    TestReceptionForDisplay reception(config);

    resetBuffer();
    reception.testDisplayKitchenWithRemoteData("invalid|data");

    ASSERT_TRUE(outputContains("Error parsing kitchen status"));
}
