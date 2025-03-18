/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** tests_4069
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>

#include "AComponent.hpp"
#include "4069.hpp"
#include "Input.hpp"
#include "Error.hpp"

// Constructor
Test(C4069, constructor)
{
    C4069 C4069;
}

// Destructor
Test(C4069, destructor)
{
    C4069 C4069;
}

// IsValidPin
Test(C4069, isValidPin)
{
    C4069 C4069;
    // Valid pins : 1 - 14 (Except 7, 14)

    cr_assert_throw(C4069.compute(0), nts::InvalidArgument)
    cr_assert_no_throw(C4069.compute(1))
    cr_assert_no_throw(C4069.compute(2))
    cr_assert_no_throw(C4069.compute(3))
    cr_assert_no_throw(C4069.compute(4))
    cr_assert_no_throw(C4069.compute(5))
    cr_assert_no_throw(C4069.compute(6))
    cr_assert_throw(C4069.compute(7), nts::InvalidArgument)
    cr_assert_no_throw(C4069.compute(8))
    cr_assert_no_throw(C4069.compute(9))
    cr_assert_no_throw(C4069.compute(10))
    cr_assert_no_throw(C4069.compute(11))
    cr_assert_no_throw(C4069.compute(12))
    cr_assert_no_throw(C4069.compute(13))
    cr_assert_throw(C4069.compute(14), nts::InvalidArgument)
    cr_assert_throw(C4069.compute(15), nts::InvalidArgument)
}

// ComputeOutput
Test(C4069, computeOutputNoLinks)
{
    C4069 C4069;

    cr_assert_eq(C4069.compute(2), nts::Tristate::Undefined);
    cr_assert_eq(C4069.compute(4), nts::Tristate::Undefined);
    cr_assert_eq(C4069.compute(6), nts::Tristate::Undefined);
    cr_assert_eq(C4069.compute(8), nts::Tristate::Undefined);
    cr_assert_eq(C4069.compute(10), nts::Tristate::Undefined);
    cr_assert_eq(C4069.compute(12), nts::Tristate::Undefined);
}

Test(C4069, True)
{
    C4069 C4069;

    Input input1;

    C4069.setLink(1, input1, 1);
    C4069.setLink(3, input1, 1);
    C4069.setLink(5, input1, 1);
    C4069.setLink(9, input1, 1);
    C4069.setLink(11, input1, 1);
    C4069.setLink(13, input1, 1);

    input1.setState(nts::Tristate::True);
    input1.simulate(1);

    cr_assert_eq(C4069.compute(2), nts::Tristate::False);
    cr_assert_eq(C4069.compute(4), nts::Tristate::False);
    cr_assert_eq(C4069.compute(6), nts::Tristate::False);
    cr_assert_eq(C4069.compute(8), nts::Tristate::False);
    cr_assert_eq(C4069.compute(10), nts::Tristate::False);
    cr_assert_eq(C4069.compute(12), nts::Tristate::False);
}

Test(C4069, False)
{
    C4069 C4069;

    Input input1;

    C4069.setLink(1, input1, 1);
    C4069.setLink(3, input1, 1);
    C4069.setLink(5, input1, 1);
    C4069.setLink(9, input1, 1);
    C4069.setLink(11, input1, 1);
    C4069.setLink(13, input1, 1);

    input1.setState(nts::Tristate::False);
    input1.simulate(1);

    cr_assert_eq(C4069.compute(2), nts::Tristate::True);
    cr_assert_eq(C4069.compute(4), nts::Tristate::True);
    cr_assert_eq(C4069.compute(6), nts::Tristate::True);
    cr_assert_eq(C4069.compute(8), nts::Tristate::True);
    cr_assert_eq(C4069.compute(10), nts::Tristate::True);
    cr_assert_eq(C4069.compute(12), nts::Tristate::True);
}

Test(C4069, Undefined)
{
    C4069 C4069;

    Input input1;

    C4069.setLink(1, input1, 1);
    C4069.setLink(3, input1, 1);
    C4069.setLink(5, input1, 1);
    C4069.setLink(9, input1, 1);
    C4069.setLink(11, input1, 1);
    C4069.setLink(13, input1, 1);

    input1.setState(nts::Tristate::Undefined);
    input1.simulate(1);

    cr_assert_eq(C4069.compute(2), nts::Tristate::Undefined);
    cr_assert_eq(C4069.compute(4), nts::Tristate::Undefined);
    cr_assert_eq(C4069.compute(6), nts::Tristate::Undefined);
    cr_assert_eq(C4069.compute(8), nts::Tristate::Undefined);
    cr_assert_eq(C4069.compute(10), nts::Tristate::Undefined);
    cr_assert_eq(C4069.compute(12), nts::Tristate::Undefined);
}
