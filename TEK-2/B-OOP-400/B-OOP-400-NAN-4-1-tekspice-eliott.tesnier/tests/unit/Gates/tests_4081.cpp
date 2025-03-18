/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** tests_4081
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>

#include "AComponent.hpp"
#include "4081.hpp"
#include "Input.hpp"
#include "Error.hpp"

// Constructor
Test(C4081, constructor)
{
    C4081 c4081;
}

// Destructor
Test(C4081, destructor)
{
    C4081 c4081;
}

// IsValidPin
Test(C4081, isValidPin)
{
    C4081 c4081;
    // Valid pins : 1 - 14 (Except 7, 14)

    cr_assert_throw(c4081.compute(0), nts::InvalidArgument)
    cr_assert_no_throw(c4081.compute(1))
    cr_assert_no_throw(c4081.compute(2))
    cr_assert_no_throw(c4081.compute(3))
    cr_assert_no_throw(c4081.compute(4))
    cr_assert_no_throw(c4081.compute(5))
    cr_assert_no_throw(c4081.compute(6))
    cr_assert_throw(c4081.compute(7), nts::InvalidArgument)
    cr_assert_no_throw(c4081.compute(8))
    cr_assert_no_throw(c4081.compute(9))
    cr_assert_no_throw(c4081.compute(10))
    cr_assert_no_throw(c4081.compute(11))
    cr_assert_no_throw(c4081.compute(12))
    cr_assert_no_throw(c4081.compute(13))
    cr_assert_throw(c4081.compute(14), nts::InvalidArgument)
    cr_assert_throw(c4081.compute(15), nts::InvalidArgument)
}

// ComputeOutput
Test(C4081, computeOutputNoLinks)
{
    C4081 c4081;

    cr_assert_eq(c4081.compute(3), nts::Tristate::Undefined);
    cr_assert_eq(c4081.compute(4), nts::Tristate::Undefined);
    cr_assert_eq(c4081.compute(10), nts::Tristate::Undefined);
    cr_assert_eq(c4081.compute(11), nts::Tristate::Undefined);
}

Test(C4081, TrueTrue)
{
    C4081 c4081;

    Input input1;
    Input input2;

    c4081.setLink(1, input1, 1);
    c4081.setLink(2, input2, 1);
    c4081.setLink(5, input1, 1);
    c4081.setLink(6, input2, 1);
    c4081.setLink(8, input1, 1);
    c4081.setLink(9, input2, 1);
    c4081.setLink(12, input1, 1);
    c4081.setLink(13, input2, 1);

    input1.setState(nts::Tristate::True);
    input2.setState(nts::Tristate::True);
    input1.simulate(1);
    input2.simulate(1);

    cr_assert_eq(c4081.compute(3), nts::Tristate::True);
    cr_assert_eq(c4081.compute(4), nts::Tristate::True);
    cr_assert_eq(c4081.compute(10), nts::Tristate::True);
    cr_assert_eq(c4081.compute(11), nts::Tristate::True);
}

Test(C4081, FalseFalse)
{
    C4081 c4081;

    Input input1;
    Input input2;

    c4081.setLink(1, input1, 1);
    c4081.setLink(2, input2, 1);
    c4081.setLink(5, input1, 1);
    c4081.setLink(6, input2, 1);
    c4081.setLink(8, input1, 1);
    c4081.setLink(9, input2, 1);
    c4081.setLink(12, input1, 1);
    c4081.setLink(13, input2, 1);

    input1.setState(nts::Tristate::False);
    input2.setState(nts::Tristate::False);
    input1.simulate(1);
    input2.simulate(1);

    cr_assert_eq(c4081.compute(3), nts::Tristate::False);
    cr_assert_eq(c4081.compute(4), nts::Tristate::False);
    cr_assert_eq(c4081.compute(10), nts::Tristate::False);
    cr_assert_eq(c4081.compute(11), nts::Tristate::False);
}

Test(C4081, TrueFalse)
{
    C4081 c4081;

    Input input1;
    Input input2;

    c4081.setLink(1, input1, 1);
    c4081.setLink(2, input2, 1);
    c4081.setLink(5, input1, 1);
    c4081.setLink(6, input2, 1);
    c4081.setLink(8, input1, 1);
    c4081.setLink(9, input2, 1);
    c4081.setLink(12, input1, 1);
    c4081.setLink(13, input2, 1);

    input1.setState(nts::Tristate::True);
    input2.setState(nts::Tristate::False);
    input1.simulate(1);
    input2.simulate(1);

    cr_assert_eq(c4081.compute(3), nts::Tristate::False);
    cr_assert_eq(c4081.compute(4), nts::Tristate::False);
    cr_assert_eq(c4081.compute(10), nts::Tristate::False);
    cr_assert_eq(c4081.compute(11), nts::Tristate::False);
}

Test(C4081, UndefinedUndefined)
{
    C4081 c4081;

    Input input1;
    Input input2;

    c4081.setLink(1, input1, 1);
    c4081.setLink(2, input2, 1);
    c4081.setLink(5, input1, 1);
    c4081.setLink(6, input2, 1);
    c4081.setLink(8, input1, 1);
    c4081.setLink(9, input2, 1);
    c4081.setLink(12, input1, 1);
    c4081.setLink(13, input2, 1);

    input1.setState(nts::Tristate::Undefined);
    input2.setState(nts::Tristate::Undefined);
    input1.simulate(1);
    input2.simulate(1);

    cr_assert_eq(c4081.compute(3), nts::Tristate::Undefined);
    cr_assert_eq(c4081.compute(4), nts::Tristate::Undefined);
    cr_assert_eq(c4081.compute(10), nts::Tristate::Undefined);
    cr_assert_eq(c4081.compute(11), nts::Tristate::Undefined);
}

Test(C4081, UndefinedFalse)
{
    C4081 c4081;

    Input input1;
    Input input2;

    c4081.setLink(1, input1, 1);
    c4081.setLink(2, input2, 1);
    c4081.setLink(5, input1, 1);
    c4081.setLink(6, input2, 1);
    c4081.setLink(8, input1, 1);
    c4081.setLink(9, input2, 1);
    c4081.setLink(12, input1, 1);
    c4081.setLink(13, input2, 1);

    input1.setState(nts::Tristate::Undefined);
    input2.setState(nts::Tristate::False);
    input1.simulate(1);
    input2.simulate(1);

    cr_assert_eq(c4081.compute(3), nts::Tristate::False);
    cr_assert_eq(c4081.compute(4), nts::Tristate::False);
    cr_assert_eq(c4081.compute(10), nts::Tristate::False);
    cr_assert_eq(c4081.compute(11), nts::Tristate::False);
}

Test(C4081, UndefinedTrue)
{
    C4081 c4081;

    Input input1;
    Input input2;

    c4081.setLink(1, input1, 1);
    c4081.setLink(2, input2, 1);
    c4081.setLink(5, input1, 1);
    c4081.setLink(6, input2, 1);
    c4081.setLink(8, input1, 1);
    c4081.setLink(9, input2, 1);
    c4081.setLink(12, input1, 1);
    c4081.setLink(13, input2, 1);

    input1.setState(nts::Tristate::Undefined);
    input2.setState(nts::Tristate::True);
    input1.simulate(1);
    input2.simulate(1);

    cr_assert_eq(c4081.compute(3), nts::Tristate::Undefined);
    cr_assert_eq(c4081.compute(4), nts::Tristate::Undefined);
    cr_assert_eq(c4081.compute(10), nts::Tristate::Undefined);
    cr_assert_eq(c4081.compute(11), nts::Tristate::Undefined);
}
