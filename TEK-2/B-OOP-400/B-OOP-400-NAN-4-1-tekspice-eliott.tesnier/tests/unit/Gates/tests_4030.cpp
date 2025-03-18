/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** tests_4030
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>

#include "AComponent.hpp"
#include "4030.hpp"
#include "Input.hpp"
#include "Error.hpp"

// Constructor
Test(C4030, constructor)
{
    C4030 C4030;
}

// Destructor
Test(C4030, destructor)
{
    C4030 C4030;
}

// IsValidPin
Test(C4030, isValidPin)
{
    C4030 C4030;
    // Valid pins : 1 - 14 (Except 7, 14)

    cr_assert_throw(C4030.compute(0), nts::InvalidArgument)
    cr_assert_no_throw(C4030.compute(1))
    cr_assert_no_throw(C4030.compute(2))
    cr_assert_no_throw(C4030.compute(3))
    cr_assert_no_throw(C4030.compute(4))
    cr_assert_no_throw(C4030.compute(5))
    cr_assert_no_throw(C4030.compute(6))
    cr_assert_throw(C4030.compute(7), nts::InvalidArgument)
    cr_assert_no_throw(C4030.compute(8))
    cr_assert_no_throw(C4030.compute(9))
    cr_assert_no_throw(C4030.compute(10))
    cr_assert_no_throw(C4030.compute(11))
    cr_assert_no_throw(C4030.compute(12))
    cr_assert_no_throw(C4030.compute(13))
    cr_assert_throw(C4030.compute(14), nts::InvalidArgument)
    cr_assert_throw(C4030.compute(15), nts::InvalidArgument)
}

// ComputeOutput
Test(C4030, computeOutputNoLinks)
{
    C4030 C4030;

    cr_assert_eq(C4030.compute(3), nts::Tristate::Undefined);
    cr_assert_eq(C4030.compute(4), nts::Tristate::Undefined);
    cr_assert_eq(C4030.compute(10), nts::Tristate::Undefined);
    cr_assert_eq(C4030.compute(11), nts::Tristate::Undefined);
}

Test(C4030, TrueTrue)
{
    C4030 C4030;

    Input input1;
    Input input2;

    C4030.setLink(1, input1, 1);
    C4030.setLink(2, input2, 1);
    C4030.setLink(5, input1, 1);
    C4030.setLink(6, input2, 1);
    C4030.setLink(8, input1, 1);
    C4030.setLink(9, input2, 1);
    C4030.setLink(12, input1, 1);
    C4030.setLink(13, input2, 1);

    input1.setState(nts::Tristate::True);
    input2.setState(nts::Tristate::True);
    input1.simulate(1);
    input2.simulate(1);

    cr_assert_eq(C4030.compute(3), nts::Tristate::False);
    cr_assert_eq(C4030.compute(4), nts::Tristate::False);
    cr_assert_eq(C4030.compute(10), nts::Tristate::False);
    cr_assert_eq(C4030.compute(11), nts::Tristate::False);
}

Test(C4030, FalseFalse)
{
    C4030 C4030;

    Input input1;
    Input input2;

    C4030.setLink(1, input1, 1);
    C4030.setLink(2, input2, 1);
    C4030.setLink(5, input1, 1);
    C4030.setLink(6, input2, 1);
    C4030.setLink(8, input1, 1);
    C4030.setLink(9, input2, 1);
    C4030.setLink(12, input1, 1);
    C4030.setLink(13, input2, 1);

    input1.setState(nts::Tristate::False);
    input2.setState(nts::Tristate::False);
    input1.simulate(1);
    input2.simulate(1);

    cr_assert_eq(C4030.compute(3), nts::Tristate::False);
    cr_assert_eq(C4030.compute(4), nts::Tristate::False);
    cr_assert_eq(C4030.compute(10), nts::Tristate::False);
    cr_assert_eq(C4030.compute(11), nts::Tristate::False);
}

Test(C4030, TrueFalse)
{
    C4030 C4030;

    Input input1;
    Input input2;

    C4030.setLink(1, input1, 1);
    C4030.setLink(2, input2, 1);
    C4030.setLink(5, input1, 1);
    C4030.setLink(6, input2, 1);
    C4030.setLink(8, input1, 1);
    C4030.setLink(9, input2, 1);
    C4030.setLink(12, input1, 1);
    C4030.setLink(13, input2, 1);

    input1.setState(nts::Tristate::True);
    input2.setState(nts::Tristate::False);
    input1.simulate(1);
    input2.simulate(1);

    cr_assert_eq(C4030.compute(3), nts::Tristate::True);
    cr_assert_eq(C4030.compute(4), nts::Tristate::True);
    cr_assert_eq(C4030.compute(10), nts::Tristate::True);
    cr_assert_eq(C4030.compute(11), nts::Tristate::True);
}

Test(C4030, UndefinedUndefined)
{
    C4030 C4030;

    Input input1;
    Input input2;

    C4030.setLink(1, input1, 1);
    C4030.setLink(2, input2, 1);
    C4030.setLink(5, input1, 1);
    C4030.setLink(6, input2, 1);
    C4030.setLink(8, input1, 1);
    C4030.setLink(9, input2, 1);
    C4030.setLink(12, input1, 1);
    C4030.setLink(13, input2, 1);

    input1.setState(nts::Tristate::Undefined);
    input2.setState(nts::Tristate::Undefined);
    input1.simulate(1);
    input2.simulate(1);

    cr_assert_eq(C4030.compute(3), nts::Tristate::Undefined);
    cr_assert_eq(C4030.compute(4), nts::Tristate::Undefined);
    cr_assert_eq(C4030.compute(10), nts::Tristate::Undefined);
    cr_assert_eq(C4030.compute(11), nts::Tristate::Undefined);
}

Test(C4030, UndefinedFalse)
{
    C4030 C4030;

    Input input1;
    Input input2;

    C4030.setLink(1, input1, 1);
    C4030.setLink(2, input2, 1);
    C4030.setLink(5, input1, 1);
    C4030.setLink(6, input2, 1);
    C4030.setLink(8, input1, 1);
    C4030.setLink(9, input2, 1);
    C4030.setLink(12, input1, 1);
    C4030.setLink(13, input2, 1);

    input1.setState(nts::Tristate::Undefined);
    input2.setState(nts::Tristate::False);
    input1.simulate(1);
    input2.simulate(1);

    cr_assert_eq(C4030.compute(3), nts::Tristate::Undefined);
    cr_assert_eq(C4030.compute(4), nts::Tristate::Undefined);
    cr_assert_eq(C4030.compute(10), nts::Tristate::Undefined);
    cr_assert_eq(C4030.compute(11), nts::Tristate::Undefined);
}

Test(C4030, UndefinedTrue)
{
    C4030 C4030;

    Input input1;
    Input input2;

    C4030.setLink(1, input1, 1);
    C4030.setLink(2, input2, 1);
    C4030.setLink(5, input1, 1);
    C4030.setLink(6, input2, 1);
    C4030.setLink(8, input1, 1);
    C4030.setLink(9, input2, 1);
    C4030.setLink(12, input1, 1);
    C4030.setLink(13, input2, 1);

    input1.setState(nts::Tristate::Undefined);
    input2.setState(nts::Tristate::True);
    input1.simulate(1);
    input2.simulate(1);

    cr_assert_eq(C4030.compute(3), nts::Tristate::Undefined);
    cr_assert_eq(C4030.compute(4), nts::Tristate::Undefined);
    cr_assert_eq(C4030.compute(10), nts::Tristate::Undefined);
    cr_assert_eq(C4030.compute(11), nts::Tristate::Undefined);
}
