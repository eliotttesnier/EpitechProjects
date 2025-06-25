/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** Exception unit tests
*/

#include <gtest/gtest.h>
#include <string>
#include "../../src/Exceptions/Exceptions.hpp"

class ExceptionTest : public ::testing::Test {
    protected:
        void SetUp() override {
        }

        void TearDown() override {
        }
};

// Test the base CLIParsingException what() method
TEST_F(ExceptionTest, CLIParsingException_What) {
    Exceptions::CLIParsingException exception("Test error message");
    ASSERT_STREQ(exception.what(), "Test error message");
}

// Test the InvalidArgumentCountException what() method
TEST_F(ExceptionTest, InvalidArgumentCountException_What) {
    Exceptions::InvalidArgumentCountException exception;
    ASSERT_STREQ(exception.what(), "Invalid number of arguments");
}

// Test the InvalidMultiplierException what() method
TEST_F(ExceptionTest, InvalidMultiplierException_What) {
    Exceptions::InvalidMultiplierException exception("abc");
    std::string message = exception.what();
    ASSERT_TRUE(message.find("Invalid multiplier value: abc") != std::string::npos);
    ASSERT_TRUE(message.find("Must be a float >= 0.0") != std::string::npos);
}

// Test the InvalidCooksException what() method
TEST_F(ExceptionTest, InvalidCooksException_What) {
    Exceptions::InvalidCooksException exception("0");
    std::string message = exception.what();
    ASSERT_TRUE(message.find("Invalid cooks per kitchen value: 0") != std::string::npos);
    ASSERT_TRUE(message.find("Must be a positive integer (>= 1)") != std::string::npos);
}

// Test the InvalidRegenerationTimeException what() method
TEST_F(ExceptionTest, InvalidRegenerationTimeException_What) {
    Exceptions::InvalidRegenerationTimeException exception("-10");
    std::string message = exception.what();
    ASSERT_TRUE(message.find("Invalid regeneration time value: -10") != std::string::npos);
    ASSERT_TRUE(message.find("Must be a positive integer (>= 1)") != std::string::npos);
}