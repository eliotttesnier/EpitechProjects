/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** tests_4801
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>

#include "AComponent.hpp"
#include "4801.hpp"
#include "Input.hpp"
#include "Error.hpp"

// Constructor
Test(C4801, constructor)
{
    C4801 c4801;
}

// Destructor
Test(C4801, destructor)
{
    C4801 c4801;
}

// IsValidPin
Test(C4801, isValidPin)
{
    C4801 c4801;
    // Valid pins : 1 - 24

    cr_assert_throw(c4801.compute(0), nts::InvalidArgument)
    cr_assert_no_throw(c4801.compute(1))
    cr_assert_no_throw(c4801.compute(2))
    cr_assert_no_throw(c4801.compute(3))
    cr_assert_no_throw(c4801.compute(4))
    cr_assert_no_throw(c4801.compute(5))
    cr_assert_no_throw(c4801.compute(6))
    cr_assert_no_throw(c4801.compute(7))
    cr_assert_no_throw(c4801.compute(8))
    cr_assert_no_throw(c4801.compute(9))
    cr_assert_no_throw(c4801.compute(10))
    cr_assert_no_throw(c4801.compute(11))
    cr_assert_throw(c4801.compute(12), nts::InvalidArgument)
    cr_assert_no_throw(c4801.compute(13))
    cr_assert_no_throw(c4801.compute(14))
    cr_assert_no_throw(c4801.compute(15))
    cr_assert_no_throw(c4801.compute(16))
    cr_assert_no_throw(c4801.compute(17))
    cr_assert_no_throw(c4801.compute(18))
    cr_assert_no_throw(c4801.compute(19))
    cr_assert_no_throw(c4801.compute(20))
    cr_assert_no_throw(c4801.compute(21))
    cr_assert_no_throw(c4801.compute(22))
    cr_assert_no_throw(c4801.compute(23))
    cr_assert_throw(c4801.compute(24), nts::InvalidArgument)
    cr_assert_throw(c4801.compute(25), nts::InvalidArgument)
}
