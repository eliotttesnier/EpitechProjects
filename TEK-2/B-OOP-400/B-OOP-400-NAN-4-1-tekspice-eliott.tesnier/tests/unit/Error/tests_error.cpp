/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** tests_error
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>

#include "Error.hpp"

// Invalid File
Test(Error, InvalidFile, .init = cr_redirect_stdout)
{
    try {
        throw nts::InvalidFile("Invalid file");
    } catch (const nts::InvalidFile &error) {
        cr_assert_str_eq(error.what(), "Invalid file");
    }
}

// Invalid Input
Test(Error, InvalidInput, .init = cr_redirect_stdout)
{
    try {
        throw nts::InvalidInput("Invalid input");
    } catch (const nts::InvalidInput &error) {
        cr_assert_str_eq(error.what(), "Invalid input");
    }
}

// Invalid Argument
Test(Error, InvalidArgument, .init = cr_redirect_stdout)
{
    try {
        throw nts::InvalidArgument("Invalid argument");
    } catch (const nts::InvalidArgument &error) {
        cr_assert_str_eq(error.what(), "Invalid argument");
    }
}
