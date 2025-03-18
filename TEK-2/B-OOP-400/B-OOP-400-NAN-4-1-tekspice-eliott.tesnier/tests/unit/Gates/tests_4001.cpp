/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** tests_4001
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>

#include "AComponent.hpp"
#include "4001.hpp"
#include "Input.hpp"
#include "Error.hpp"

// Constructor
Test(C4001, constructor)
{
    C4001 C4001;
}

// Destructor
Test(C4001, destructor)
{
    C4001 C4001;
}

// IsValidPin
Test(C4001, isValidPin)
{
    C4001 C4001;
    // Valid pins : 1 - 14 (Except 7, 14)

    cr_assert_throw(C4001.compute(0), nts::InvalidArgument)
    cr_assert_no_throw(C4001.compute(1))
    cr_assert_no_throw(C4001.compute(2))
    cr_assert_no_throw(C4001.compute(3))
    cr_assert_no_throw(C4001.compute(4))
    cr_assert_no_throw(C4001.compute(5))
    cr_assert_no_throw(C4001.compute(6))
    cr_assert_throw(C4001.compute(7), nts::InvalidArgument)
    cr_assert_no_throw(C4001.compute(8))
    cr_assert_no_throw(C4001.compute(9))
    cr_assert_no_throw(C4001.compute(10))
    cr_assert_no_throw(C4001.compute(11))
    cr_assert_no_throw(C4001.compute(12))
    cr_assert_no_throw(C4001.compute(13))
    cr_assert_throw(C4001.compute(14), nts::InvalidArgument)
    cr_assert_throw(C4001.compute(15), nts::InvalidArgument)
}

// ComputeOutput
Test(C4001, computeOutputNoLinks)
{
    C4001 C4001;

    cr_assert_eq(C4001.compute(3), nts::Tristate::Undefined);
    cr_assert_eq(C4001.compute(4), nts::Tristate::Undefined);
    cr_assert_eq(C4001.compute(10), nts::Tristate::Undefined);
    cr_assert_eq(C4001.compute(11), nts::Tristate::Undefined);
}

Test(C4001, TrueTrue)
{
    C4001 C4001;

    Input input1;
    Input input2;

    C4001.setLink(1, input1, 1);
    C4001.setLink(2, input2, 1);
    C4001.setLink(5, input1, 1);
    C4001.setLink(6, input2, 1);
    C4001.setLink(8, input1, 1);
    C4001.setLink(9, input2, 1);
    C4001.setLink(12, input1, 1);
    C4001.setLink(13, input2, 1);

    input1.setState(nts::Tristate::True);
    input2.setState(nts::Tristate::True);
    input1.simulate(1);
    input2.simulate(1);

    cr_assert_eq(C4001.compute(3), nts::Tristate::False);
    cr_assert_eq(C4001.compute(4), nts::Tristate::False);
    cr_assert_eq(C4001.compute(10), nts::Tristate::False);
    cr_assert_eq(C4001.compute(11), nts::Tristate::False);
}

Test(C4001, FalseFalse)
{
    C4001 C4001;

    Input input1;
    Input input2;

    C4001.setLink(1, input1, 1);
    C4001.setLink(2, input2, 1);
    C4001.setLink(5, input1, 1);
    C4001.setLink(6, input2, 1);
    C4001.setLink(8, input1, 1);
    C4001.setLink(9, input2, 1);
    C4001.setLink(12, input1, 1);
    C4001.setLink(13, input2, 1);

    input1.setState(nts::Tristate::False);
    input2.setState(nts::Tristate::False);
    input1.simulate(1);
    input2.simulate(1);

    cr_assert_eq(C4001.compute(3), nts::Tristate::True);
    cr_assert_eq(C4001.compute(4), nts::Tristate::True);
    cr_assert_eq(C4001.compute(10), nts::Tristate::True);
    cr_assert_eq(C4001.compute(11), nts::Tristate::True);
}

Test(C4001, TrueFalse)
{
    C4001 C4001;

    Input input1;
    Input input2;

    C4001.setLink(1, input1, 1);
    C4001.setLink(2, input2, 1);
    C4001.setLink(5, input1, 1);
    C4001.setLink(6, input2, 1);
    C4001.setLink(8, input1, 1);
    C4001.setLink(9, input2, 1);
    C4001.setLink(12, input1, 1);
    C4001.setLink(13, input2, 1);

    input1.setState(nts::Tristate::True);
    input2.setState(nts::Tristate::False);
    input1.simulate(1);
    input2.simulate(1);

    cr_assert_eq(C4001.compute(3), nts::Tristate::False);
    cr_assert_eq(C4001.compute(4), nts::Tristate::False);
    cr_assert_eq(C4001.compute(10), nts::Tristate::False);
    cr_assert_eq(C4001.compute(11), nts::Tristate::False);
}

Test(C4001, UndefinedUndefined)
{
    C4001 C4001;

    Input input1;
    Input input2;

    C4001.setLink(1, input1, 1);
    C4001.setLink(2, input2, 1);
    C4001.setLink(5, input1, 1);
    C4001.setLink(6, input2, 1);
    C4001.setLink(8, input1, 1);
    C4001.setLink(9, input2, 1);
    C4001.setLink(12, input1, 1);
    C4001.setLink(13, input2, 1);

    input1.setState(nts::Tristate::Undefined);
    input2.setState(nts::Tristate::Undefined);
    input1.simulate(1);
    input2.simulate(1);

    cr_assert_eq(C4001.compute(3), nts::Tristate::Undefined);
    cr_assert_eq(C4001.compute(4), nts::Tristate::Undefined);
    cr_assert_eq(C4001.compute(10), nts::Tristate::Undefined);
    cr_assert_eq(C4001.compute(11), nts::Tristate::Undefined);
}

Test(C4001, UndefinedFalse)
{
    C4001 C4001;

    Input input1;
    Input input2;

    C4001.setLink(1, input1, 1);
    C4001.setLink(2, input2, 1);
    C4001.setLink(5, input1, 1);
    C4001.setLink(6, input2, 1);
    C4001.setLink(8, input1, 1);
    C4001.setLink(9, input2, 1);
    C4001.setLink(12, input1, 1);
    C4001.setLink(13, input2, 1);

    input1.setState(nts::Tristate::Undefined);
    input2.setState(nts::Tristate::False);
    input1.simulate(1);
    input2.simulate(1);

    cr_assert_eq(C4001.compute(3), nts::Tristate::Undefined);
    cr_assert_eq(C4001.compute(4), nts::Tristate::Undefined);
    cr_assert_eq(C4001.compute(10), nts::Tristate::Undefined);
    cr_assert_eq(C4001.compute(11), nts::Tristate::Undefined);
}

Test(C4001, UndefinedTrue)
{
    C4001 C4001;

    Input input1;
    Input input2;

    C4001.setLink(1, input1, 1);
    C4001.setLink(2, input2, 1);
    C4001.setLink(5, input1, 1);
    C4001.setLink(6, input2, 1);
    C4001.setLink(8, input1, 1);
    C4001.setLink(9, input2, 1);
    C4001.setLink(12, input1, 1);
    C4001.setLink(13, input2, 1);

    input1.setState(nts::Tristate::Undefined);
    input2.setState(nts::Tristate::True);
    input1.simulate(1);
    input2.simulate(1);

    cr_assert_eq(C4001.compute(3), nts::Tristate::False);
    cr_assert_eq(C4001.compute(4), nts::Tristate::False);
    cr_assert_eq(C4001.compute(10), nts::Tristate::False);
    cr_assert_eq(C4001.compute(11), nts::Tristate::False);
}
