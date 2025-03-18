/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** tests_2716
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>

#include "AComponent.hpp"
#include "2716.hpp"
#include "Input.hpp"
#include "Error.hpp"

// Constructor
Test(C2716, constructor)
{
    C2716 c2716;
}

// Destructor
Test(C2716, destructor)
{
    C2716 c2716;
}

// IsValidPin
Test(C2716, isValidPin)
{
    C2716 c2716;
    // Valid pins : 1 - 24

    cr_assert_throw(c2716.compute(0), nts::InvalidArgument)
    cr_assert_no_throw(c2716.compute(1))
    cr_assert_no_throw(c2716.compute(2))
    cr_assert_no_throw(c2716.compute(3))
    cr_assert_no_throw(c2716.compute(4))
    cr_assert_no_throw(c2716.compute(5))
    cr_assert_no_throw(c2716.compute(6))
    cr_assert_no_throw(c2716.compute(7))
    cr_assert_no_throw(c2716.compute(8))
    cr_assert_no_throw(c2716.compute(9))
    cr_assert_no_throw(c2716.compute(10))
    cr_assert_no_throw(c2716.compute(11))
    cr_assert_throw(c2716.compute(12), nts::InvalidArgument)
    cr_assert_no_throw(c2716.compute(13))
    cr_assert_no_throw(c2716.compute(14))
    cr_assert_no_throw(c2716.compute(15))
    cr_assert_no_throw(c2716.compute(16))
    cr_assert_no_throw(c2716.compute(17))
    cr_assert_no_throw(c2716.compute(18))
    cr_assert_no_throw(c2716.compute(19))
    cr_assert_no_throw(c2716.compute(20))
    cr_assert_no_throw(c2716.compute(21))
    cr_assert_no_throw(c2716.compute(22))
    cr_assert_no_throw(c2716.compute(23))
    cr_assert_throw(c2716.compute(24), nts::InvalidArgument)
    cr_assert_throw(c2716.compute(25), nts::InvalidArgument)
}

// Simulate
Test(C2716, simulate)
{
    C2716 c2716;
    cr_assert_no_throw(c2716.simulate(1))
    cr_assert_no_throw(c2716.simulate(1))
}
