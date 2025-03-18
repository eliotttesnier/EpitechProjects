/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** tests_4011
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>

#include "AComponent.hpp"
#include "4011.hpp"
#include "Input.hpp"
#include "Error.hpp"

// Constructor
Test(C4011, constructor)
{
    C4011 C4011;
}

// Destructor
Test(C4011, destructor)
{
    C4011 C4011;
}

// IsValidPin
Test(C4011, isValidPin)
{
    C4011 C4011;
    // Valid pins : 1 - 14 (Except 7, 14)

    cr_assert_throw(C4011.compute(0), nts::InvalidArgument)
    cr_assert_no_throw(C4011.compute(1))
    cr_assert_no_throw(C4011.compute(2))
    cr_assert_no_throw(C4011.compute(3))
    cr_assert_no_throw(C4011.compute(4))
    cr_assert_no_throw(C4011.compute(5))
    cr_assert_no_throw(C4011.compute(6))
    cr_assert_throw(C4011.compute(7), nts::InvalidArgument)
    cr_assert_no_throw(C4011.compute(8))
    cr_assert_no_throw(C4011.compute(9))
    cr_assert_no_throw(C4011.compute(10))
    cr_assert_no_throw(C4011.compute(11))
    cr_assert_no_throw(C4011.compute(12))
    cr_assert_no_throw(C4011.compute(13))
    cr_assert_throw(C4011.compute(14), nts::InvalidArgument)
    cr_assert_throw(C4011.compute(15), nts::InvalidArgument)
}

// ComputeOutput
Test(C4011, computeOutputNoLinks)
{
    C4011 C4011;

    cr_assert_eq(C4011.compute(3), nts::Tristate::Undefined);
    cr_assert_eq(C4011.compute(4), nts::Tristate::Undefined);
    cr_assert_eq(C4011.compute(10), nts::Tristate::Undefined);
    cr_assert_eq(C4011.compute(11), nts::Tristate::Undefined);
}

Test(C4011, TrueTrue)
{
    C4011 C4011;

    Input input1;
    Input input2;

    C4011.setLink(1, input1, 1);
    C4011.setLink(2, input2, 1);
    C4011.setLink(5, input1, 1);
    C4011.setLink(6, input2, 1);
    C4011.setLink(8, input1, 1);
    C4011.setLink(9, input2, 1);
    C4011.setLink(12, input1, 1);
    C4011.setLink(13, input2, 1);

    input1.setState(nts::Tristate::True);
    input2.setState(nts::Tristate::True);
    input1.simulate(1);
    input2.simulate(1);

    cr_assert_eq(C4011.compute(3), nts::Tristate::False);
    cr_assert_eq(C4011.compute(4), nts::Tristate::False);
    cr_assert_eq(C4011.compute(10), nts::Tristate::False);
    cr_assert_eq(C4011.compute(11), nts::Tristate::False);
}

Test(C4011, FalseFalse)
{
    C4011 C4011;

    Input input1;
    Input input2;

    C4011.setLink(1, input1, 1);
    C4011.setLink(2, input2, 1);
    C4011.setLink(5, input1, 1);
    C4011.setLink(6, input2, 1);
    C4011.setLink(8, input1, 1);
    C4011.setLink(9, input2, 1);
    C4011.setLink(12, input1, 1);
    C4011.setLink(13, input2, 1);

    input1.setState(nts::Tristate::False);
    input2.setState(nts::Tristate::False);
    input1.simulate(1);
    input2.simulate(1);

    cr_assert_eq(C4011.compute(3), nts::Tristate::True);
    cr_assert_eq(C4011.compute(4), nts::Tristate::True);
    cr_assert_eq(C4011.compute(10), nts::Tristate::True);
    cr_assert_eq(C4011.compute(11), nts::Tristate::True);
}

Test(C4011, TrueFalse)
{
    C4011 C4011;

    Input input1;
    Input input2;

    C4011.setLink(1, input1, 1);
    C4011.setLink(2, input2, 1);
    C4011.setLink(5, input1, 1);
    C4011.setLink(6, input2, 1);
    C4011.setLink(8, input1, 1);
    C4011.setLink(9, input2, 1);
    C4011.setLink(12, input1, 1);
    C4011.setLink(13, input2, 1);

    input1.setState(nts::Tristate::True);
    input2.setState(nts::Tristate::False);
    input1.simulate(1);
    input2.simulate(1);

    cr_assert_eq(C4011.compute(3), nts::Tristate::True);
    cr_assert_eq(C4011.compute(4), nts::Tristate::True);
    cr_assert_eq(C4011.compute(10), nts::Tristate::True);
    cr_assert_eq(C4011.compute(11), nts::Tristate::True);
}

Test(C4011, UndefinedUndefined)
{
    C4011 C4011;

    Input input1;
    Input input2;

    C4011.setLink(1, input1, 1);
    C4011.setLink(2, input2, 1);
    C4011.setLink(5, input1, 1);
    C4011.setLink(6, input2, 1);
    C4011.setLink(8, input1, 1);
    C4011.setLink(9, input2, 1);
    C4011.setLink(12, input1, 1);
    C4011.setLink(13, input2, 1);

    input1.setState(nts::Tristate::Undefined);
    input2.setState(nts::Tristate::Undefined);
    input1.simulate(1);
    input2.simulate(1);

    cr_assert_eq(C4011.compute(3), nts::Tristate::Undefined);
    cr_assert_eq(C4011.compute(4), nts::Tristate::Undefined);
    cr_assert_eq(C4011.compute(10), nts::Tristate::Undefined);
    cr_assert_eq(C4011.compute(11), nts::Tristate::Undefined);
}

Test(C4011, UndefinedFalse)
{
    C4011 C4011;

    Input input1;
    Input input2;

    C4011.setLink(1, input1, 1);
    C4011.setLink(2, input2, 1);
    C4011.setLink(5, input1, 1);
    C4011.setLink(6, input2, 1);
    C4011.setLink(8, input1, 1);
    C4011.setLink(9, input2, 1);
    C4011.setLink(12, input1, 1);
    C4011.setLink(13, input2, 1);

    input1.setState(nts::Tristate::Undefined);
    input2.setState(nts::Tristate::False);
    input1.simulate(1);
    input2.simulate(1);

    cr_assert_eq(C4011.compute(3), nts::Tristate::True);
    cr_assert_eq(C4011.compute(4), nts::Tristate::True);
    cr_assert_eq(C4011.compute(10), nts::Tristate::True);
    cr_assert_eq(C4011.compute(11), nts::Tristate::True);
}

Test(C4011, UndefinedTrue)
{
    C4011 C4011;

    Input input1;
    Input input2;

    C4011.setLink(1, input1, 1);
    C4011.setLink(2, input2, 1);
    C4011.setLink(5, input1, 1);
    C4011.setLink(6, input2, 1);
    C4011.setLink(8, input1, 1);
    C4011.setLink(9, input2, 1);
    C4011.setLink(12, input1, 1);
    C4011.setLink(13, input2, 1);

    input1.setState(nts::Tristate::Undefined);
    input2.setState(nts::Tristate::True);
    input1.simulate(1);
    input2.simulate(1);

    cr_assert_eq(C4011.compute(3), nts::Tristate::Undefined);
    cr_assert_eq(C4011.compute(4), nts::Tristate::Undefined);
    cr_assert_eq(C4011.compute(10), nts::Tristate::Undefined);
    cr_assert_eq(C4011.compute(11), nts::Tristate::Undefined);
}
