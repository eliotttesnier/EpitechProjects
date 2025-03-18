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
#include "4008.hpp"
#include "Input.hpp"
#include "Error.hpp"

// Constructor
Test(C4008, constructor)
{
    C4008 c4008;
}

// Destructor
Test(C4008, destructor)
{
    C4008 c4008;
}

// IsValidPin
Test(C4008, isValidPin)
{
    C4008 c4008;
    // Valid pins : 1 - 16

    cr_assert_throw(c4008.compute(0), nts::InvalidArgument)
    cr_assert_no_throw(c4008.compute(1))
    cr_assert_no_throw(c4008.compute(2))
    cr_assert_no_throw(c4008.compute(3))
    cr_assert_no_throw(c4008.compute(4))
    cr_assert_no_throw(c4008.compute(5))
    cr_assert_no_throw(c4008.compute(6))
    cr_assert_no_throw(c4008.compute(7))
    cr_assert_no_throw(c4008.compute(8))
    cr_assert_no_throw(c4008.compute(9))
    cr_assert_no_throw(c4008.compute(10))
    cr_assert_no_throw(c4008.compute(11))
    cr_assert_no_throw(c4008.compute(12))
    cr_assert_no_throw(c4008.compute(13))
    cr_assert_no_throw(c4008.compute(14))
    cr_assert_no_throw(c4008.compute(15))
    cr_assert_no_throw(c4008.compute(16))
    cr_assert_throw(c4008.compute(17), nts::InvalidArgument)
}

// ComputeOutput
Test(C4008, computeInputs)
{
    C4008 c4008;
    Input in_a1;
    Input in_b1;
    Input in_a2;
    Input in_b2;
    Input in_a3;
    Input in_b3;
    Input in_a4;
    Input in_b4;
    Input in_c;

    c4008.setLink(7, in_a1, 1);
    in_a1.setLink(1, c4008, 7);

    c4008.setLink(6, in_b1, 1);
    in_b1.setLink(1, c4008, 6);

    c4008.setLink(5, in_a2, 1);
    in_a2.setLink(1, c4008, 5);

    c4008.setLink(4, in_b2, 1);
    in_b2.setLink(1, c4008, 4);

    c4008.setLink(3, in_a3, 1);
    in_a3.setLink(1, c4008, 3);

    c4008.setLink(2, in_b3, 1);
    in_b3.setLink(1, c4008, 2);

    c4008.setLink(1, in_a4, 1);
    in_a4.setLink(1, c4008, 1);

    c4008.setLink(15, in_b4, 1);
    in_b4.setLink(1, c4008, 15);

    c4008.setLink(9, in_c, 1);
    in_c.setLink(1, c4008, 9);

    in_a1.setState(nts::Tristate::True);
    in_a1.simulate(1);
    in_b1.setState(nts::Tristate::True);
    in_b1.simulate(1);
    in_a2.setState(nts::Tristate::True);
    in_a2.simulate(1);
    in_b2.setState(nts::Tristate::True);
    in_b2.simulate(1);
    in_a3.setState(nts::Tristate::True);
    in_a3.simulate(1);
    in_b3.setState(nts::Tristate::True);
    in_b3.simulate(1);
    in_a4.setState(nts::Tristate::True);
    in_a4.simulate(1);
    in_b4.setState(nts::Tristate::True);
    in_b4.simulate(1);
    in_c.setState(nts::Tristate::True);
    in_c.simulate(1);

    cr_assert_eq(c4008.compute(7), nts::Tristate::True);
    cr_assert_eq(c4008.compute(6), nts::Tristate::True);
    cr_assert_eq(c4008.compute(5), nts::Tristate::True);
    cr_assert_eq(c4008.compute(4), nts::Tristate::True);
    cr_assert_eq(c4008.compute(3), nts::Tristate::True);
    cr_assert_eq(c4008.compute(2), nts::Tristate::True);
    cr_assert_eq(c4008.compute(1), nts::Tristate::True);
    cr_assert_eq(c4008.compute(15), nts::Tristate::True);
    cr_assert_eq(c4008.compute(9), nts::Tristate::True);
}
