/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** Config unit tests
*/

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <sstream>
#include "../../src/Config/Config.hpp"
#include "../../src/Exceptions/Exceptions.hpp"

class ConfigTest : public ::testing::Test {
    protected:
        void SetUp() override {
        }

        void TearDown() override {
        }

        std::vector<char*> createArgv(const std::vector<std::string>& args) {
            std::vector<char*> argv;
            for (const auto& arg : args) {
                argv.push_back(const_cast<char*>(arg.c_str()));
            }
            return argv;
        }
};

// Test with no arguments
TEST_F(ConfigTest, NotEnoughArguments_NoArgs) {
    std::vector<std::string> args = {"./plazza"};
    auto argv = createArgv(args);

    ASSERT_THROW({
        Config::parseArguments(argv.size(), argv.data());
    }, Exceptions::InvalidArgumentCountException);
}

// Test with one argument
TEST_F(ConfigTest, NotEnoughArguments_OneArg) {
    std::vector<std::string> args = {"./plazza", "2"};
    auto argv = createArgv(args);

    ASSERT_THROW({
        Config::parseArguments(argv.size(), argv.data());
    }, Exceptions::InvalidArgumentCountException);
}

// Test with two arguments
TEST_F(ConfigTest, NotEnoughArguments_TwoArgs) {
    std::vector<std::string> args = {"./plazza", "2", "5"};
    auto argv = createArgv(args);

    ASSERT_THROW({
        Config::parseArguments(argv.size(), argv.data());
    }, Exceptions::InvalidArgumentCountException);
}

// Test with too many arguments
TEST_F(ConfigTest, TooManyArguments) {
    std::vector<std::string> args = {"./plazza", "2", "5", "2000", "extra"};
    auto argv = createArgv(args);

    ASSERT_THROW({
        Config::parseArguments(argv.size(), argv.data());
    }, Exceptions::InvalidArgumentCountException);
}

// Test with invalid multiplier (not a number)
TEST_F(ConfigTest, InvalidMultiplier_NotANumber) {
    std::vector<std::string> args = {"./plazza", "abc", "5", "2000"};
    auto argv = createArgv(args);

    ASSERT_THROW({
        Config::parseArguments(argv.size(), argv.data());
    }, Exceptions::InvalidMultiplierException);
}

// Test with invalid multiplier (negative)
TEST_F(ConfigTest, InvalidMultiplier_Negative) {
    std::vector<std::string> args = {"./plazza", "-2", "5", "2000"};
    auto argv = createArgv(args);

    ASSERT_THROW({
        Config::parseArguments(argv.size(), argv.data());
    }, Exceptions::InvalidMultiplierException);
}

// Test with invalid cooks (not a number)
TEST_F(ConfigTest, InvalidCooks_NotANumber) {
    std::vector<std::string> args = {"./plazza", "2", "abc", "2000"};
    auto argv = createArgv(args);

    ASSERT_THROW({
        Config::parseArguments(argv.size(), argv.data());
    }, Exceptions::InvalidCooksException);
}

// Test with invalid cooks (negative)
TEST_F(ConfigTest, InvalidCooks_Negative) {
    std::vector<std::string> args = {"./plazza", "2", "-5", "2000"};
    auto argv = createArgv(args);

    ASSERT_THROW({
        Config::parseArguments(argv.size(), argv.data());
    }, Exceptions::InvalidCooksException);
}

// Test with invalid cooks (zero)
TEST_F(ConfigTest, InvalidCooks_Zero) {
    std::vector<std::string> args = {"./plazza", "2", "0", "2000"};
    auto argv = createArgv(args);

    ASSERT_THROW({
        Config::parseArguments(argv.size(), argv.data());
    }, Exceptions::InvalidCooksException);
}

// Test with invalid regeneration time (not a number)
TEST_F(ConfigTest, InvalidRegenerationTime_NotANumber) {
    std::vector<std::string> args = {"./plazza", "2", "5", "abc"};
    auto argv = createArgv(args);

    ASSERT_THROW({
        Config::parseArguments(argv.size(), argv.data());
    }, Exceptions::InvalidRegenerationTimeException);
}

// Test with invalid regeneration time (negative)
TEST_F(ConfigTest, InvalidRegenerationTime_Negative) {
    std::vector<std::string> args = {"./plazza", "2", "5", "-2000"};
    auto argv = createArgv(args);

    ASSERT_THROW({
        Config::parseArguments(argv.size(), argv.data());
    }, Exceptions::InvalidRegenerationTimeException);
}

// Test with invalid regeneration time (zero)
TEST_F(ConfigTest, InvalidRegenerationTime_Zero) {
    std::vector<std::string> args = {"./plazza", "2", "5", "0"};
    auto argv = createArgv(args);

    ASSERT_THROW({
        Config::parseArguments(argv.size(), argv.data());
    }, Exceptions::InvalidRegenerationTimeException);
}

// Test with valid arguments (integer multiplier)
TEST_F(ConfigTest, ValidArguments_IntegerMultiplier) {
    std::vector<std::string> args = {"./plazza", "2", "5", "2000"};
    auto argv = createArgv(args);

    Config config = Config::parseArguments(argv.size(), argv.data());

    ASSERT_FLOAT_EQ(config.getMultiplier(), 2.0);
    ASSERT_EQ(config.getCooksPerKitchen(), 5);
    ASSERT_EQ(config.getRegenerationTimeMs(), 2000);
}

// Test with valid arguments (decimal multiplier)
TEST_F(ConfigTest, ValidArguments_DecimalMultiplier) {
    std::vector<std::string> args = {"./plazza", "1.5", "5", "2000"};
    auto argv = createArgv(args);

    Config config = Config::parseArguments(argv.size(), argv.data());

    ASSERT_FLOAT_EQ(config.getMultiplier(), 1.5);
    ASSERT_EQ(config.getCooksPerKitchen(), 5);
    ASSERT_EQ(config.getRegenerationTimeMs(), 2000);
}

// Test with valid arguments (multiplier less than 1)
TEST_F(ConfigTest, ValidArguments_MultiplierLessThanOne) {
    std::vector<std::string> args = {"./plazza", "0.5", "5", "2000"};
    auto argv = createArgv(args);

    Config config = Config::parseArguments(argv.size(), argv.data());

    ASSERT_FLOAT_EQ(config.getMultiplier(), 0.5);
    ASSERT_EQ(config.getCooksPerKitchen(), 5);
    ASSERT_EQ(config.getRegenerationTimeMs(), 2000);
}

// Test with edge case (minimum values)
TEST_F(ConfigTest, EdgeCase_MinimumValues) {
    std::vector<std::string> args = {"./plazza", "0.01", "1", "1"};
    auto argv = createArgv(args);

    Config config = Config::parseArguments(argv.size(), argv.data());

    ASSERT_FLOAT_EQ(config.getMultiplier(), 0.01);
    ASSERT_EQ(config.getCooksPerKitchen(), 1);
    ASSERT_EQ(config.getRegenerationTimeMs(), 1);
}

// Test with edge case (zero multiplier)
TEST_F(ConfigTest, EdgeCase_ZeroMultiplier) {
    std::vector<std::string> args = {"./plazza", "0", "5", "2000"};
    auto argv = createArgv(args);

    Config config = Config::parseArguments(argv.size(), argv.data());

    ASSERT_FLOAT_EQ(config.getMultiplier(), 0.0);
    ASSERT_EQ(config.getCooksPerKitchen(), 5);
    ASSERT_EQ(config.getRegenerationTimeMs(), 2000);
}

// Test printUsage
TEST_F(ConfigTest, PrintUsage) {
    std::stringstream buffer;
    std::streambuf* old = std::cerr.rdbuf(buffer.rdbuf());

    Config::printUsage("./plazza");

    std::cerr.rdbuf(old);

    std::string output = buffer.str();

    ASSERT_TRUE(output.find("USAGE:") != std::string::npos);
    ASSERT_TRUE(output.find("./plazza") != std::string::npos);
    ASSERT_TRUE(output.find("multiplier") != std::string::npos);
    ASSERT_TRUE(output.find("cooks_per_kitchen") != std::string::npos);
    ASSERT_TRUE(output.find("regeneration_time_ms") != std::string::npos);
}
