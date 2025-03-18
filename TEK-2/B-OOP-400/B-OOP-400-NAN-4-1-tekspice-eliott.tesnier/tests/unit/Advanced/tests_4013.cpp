/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** tests_4013
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>

#include "AComponent.hpp"
#include "4013.hpp"
#include "Input.hpp"
#include "Clock.hpp"
#include "Error.hpp"

// Constructor
Test(C4013, constructor)
{
    C4013 c4013;
}

// Destructor
Test(C4013, destructor)
{
    C4013 c4013;
}

// IsValidPin
Test(C4013, isValidPin)
{
    C4013 c4013;
    // Valid pins : 1 - 14 (7, 14 are power)

    cr_assert_throw(c4013.compute(0), nts::InvalidArgument)
    cr_assert_no_throw(c4013.compute(1))
    cr_assert_no_throw(c4013.compute(2))
    cr_assert_no_throw(c4013.compute(3))
    cr_assert_no_throw(c4013.compute(4))
    cr_assert_no_throw(c4013.compute(5))
    cr_assert_no_throw(c4013.compute(6))
    cr_assert_throw(c4013.compute(7), nts::InvalidArgument)
    cr_assert_no_throw(c4013.compute(8))
    cr_assert_no_throw(c4013.compute(9))
    cr_assert_no_throw(c4013.compute(10))
    cr_assert_no_throw(c4013.compute(11))
    cr_assert_no_throw(c4013.compute(12))
    cr_assert_no_throw(c4013.compute(13))
    cr_assert_throw(c4013.compute(14), nts::InvalidArgument)
    cr_assert_throw(c4013.compute(15), nts::InvalidArgument)
}

// ComputeOutput
Test(C4013, computeQPins)
{
    C4013 c4013;

    cr_assert_eq(c4013.compute(1), nts::Tristate::Undefined);
    cr_assert_eq(c4013.compute(13), nts::Tristate::Undefined);
}

Test(C4013, computeSetTrue)
{
    C4013 c4013;
    Clock clock;
    Input in_data;
    Input in_set;
    Input in_reset;

    c4013.setLink(3, clock, 1);
    clock.setLink(1, c4013, 3);
    c4013.setLink(11, clock, 1);
    clock.setLink(1, c4013, 11);

    c4013.setLink(5, in_data, 1);
    in_data.setLink(1, c4013, 5);
    c4013.setLink(9, in_data, 1);
    in_data.setLink(1, c4013, 9);

    c4013.setLink(6, in_set, 1);
    in_set.setLink(1, c4013, 6);
    c4013.setLink(8, in_set, 1);
    in_set.setLink(1, c4013, 8);

    c4013.setLink(4, in_reset, 1);
    in_reset.setLink(1, c4013, 4);
    c4013.setLink(10, in_reset, 1);
    in_reset.setLink(1, c4013, 10);

    in_set.setState(nts::Tristate::True);
    in_set.simulate(1);

    c4013.simulate(1);
    cr_assert_eq(c4013.compute(1), nts::Tristate::True);
    cr_assert_eq(c4013.compute(2), nts::Tristate::False);
    cr_assert_eq(c4013.compute(13), nts::Tristate::True);
    cr_assert_eq(c4013.compute(12), nts::Tristate::False);
}

Test(C4013, computeResetTrue)
{
    C4013 c4013;
    Clock clock;
    Input in_data;
    Input in_set;
    Input in_reset;

    c4013.setLink(3, clock, 1);
    clock.setLink(1, c4013, 3);
    c4013.setLink(11, clock, 1);
    clock.setLink(1, c4013, 11);

    c4013.setLink(5, in_data, 1);
    in_data.setLink(1, c4013, 5);
    c4013.setLink(9, in_data, 1);
    in_data.setLink(1, c4013, 9);

    c4013.setLink(6, in_set, 1);
    in_set.setLink(1, c4013, 6);
    c4013.setLink(8, in_set, 1);
    in_set.setLink(1, c4013, 8);

    c4013.setLink(4, in_reset, 1);
    in_reset.setLink(1, c4013, 4);
    c4013.setLink(10, in_reset, 1);
    in_reset.setLink(1, c4013, 10);

    in_reset.setState(nts::Tristate::True);
    in_reset.simulate(1);

    c4013.simulate(1);
    cr_assert_eq(c4013.compute(1), nts::Tristate::False);
    cr_assert_eq(c4013.compute(2), nts::Tristate::True);
    cr_assert_eq(c4013.compute(13), nts::Tristate::False);
    cr_assert_eq(c4013.compute(12), nts::Tristate::True);
}

Test(C4013, computeSetAndResetTrue)
{
    C4013 c4013;
    Clock clock;
    Input in_data;
    Input in_set;
    Input in_reset;

    c4013.setLink(3, clock, 1);
    clock.setLink(1, c4013, 3);
    c4013.setLink(11, clock, 1);
    clock.setLink(1, c4013, 11);

    c4013.setLink(5, in_data, 1);
    in_data.setLink(1, c4013, 5);
    c4013.setLink(9, in_data, 1);
    in_data.setLink(1, c4013, 9);

    c4013.setLink(6, in_set, 1);
    in_set.setLink(1, c4013, 6);
    c4013.setLink(8, in_set, 1);
    in_set.setLink(1, c4013, 8);

    c4013.setLink(4, in_reset, 1);
    in_reset.setLink(1, c4013, 4);
    c4013.setLink(10, in_reset, 1);
    in_reset.setLink(1, c4013, 10);

    in_set.setState(nts::Tristate::True);
    in_set.simulate(1);
    in_reset.setState(nts::Tristate::True);
    in_reset.simulate(1);

    c4013.simulate(1);
    cr_assert_eq(c4013.compute(1), nts::Tristate::True);
    cr_assert_eq(c4013.compute(2), nts::Tristate::True);
    cr_assert_eq(c4013.compute(13), nts::Tristate::True);
    cr_assert_eq(c4013.compute(12), nts::Tristate::True);
}

Test(C4013, computeRisingEdge)
{
    C4013 c4013;
    Clock clock;
    Input in_data;
    Input in_set;
    Input in_reset;

    c4013.setLink(3, clock, 1);
    clock.setLink(1, c4013, 3);
    c4013.setLink(11, clock, 1);
    clock.setLink(1, c4013, 11);

    c4013.setLink(5, in_data, 1);
    in_data.setLink(1, c4013, 5);
    c4013.setLink(9, in_data, 1);
    in_data.setLink(1, c4013, 9);

    c4013.setLink(6, in_set, 1);
    in_set.setLink(1, c4013, 6);
    c4013.setLink(8, in_set, 1);
    in_set.setLink(1, c4013, 8);

    c4013.setLink(4, in_reset, 1);
    in_reset.setLink(1, c4013, 4);
    c4013.setLink(10, in_reset, 1);
    in_reset.setLink(1, c4013, 10);

    clock.setState(nts::Tristate::False);
    clock.simulate(1);
    in_data.setState(nts::Tristate::True);
    in_data.simulate(1);
    in_set.setState(nts::Tristate::False);
    in_set.simulate(1);
    in_reset.setState(nts::Tristate::False);
    in_reset.simulate(1);

    c4013.simulate(1);
    c4013.simulate(2);
    cr_assert_eq(c4013.compute(1), nts::Tristate::True);
    cr_assert_eq(c4013.compute(2), nts::Tristate::False);
    cr_assert_eq(c4013.compute(13), nts::Tristate::True);
    cr_assert_eq(c4013.compute(12), nts::Tristate::False);
}

Test(C4013, computeFallingEdge)
{
    C4013 c4013;
    Clock clock;
    Input in_data;
    Input in_set;
    Input in_reset;

    c4013.setLink(3, clock, 1);
    clock.setLink(1, c4013, 3);
    c4013.setLink(11, clock, 1);
    clock.setLink(1, c4013, 11);

    c4013.setLink(5, in_data, 1);
    in_data.setLink(1, c4013, 5);
    c4013.setLink(9, in_data, 1);
    in_data.setLink(1, c4013, 9);

    c4013.setLink(6, in_set, 1);
    in_set.setLink(1, c4013, 6);
    c4013.setLink(8, in_set, 1);
    in_set.setLink(1, c4013, 8);

    c4013.setLink(4, in_reset, 1);
    in_reset.setLink(1, c4013, 4);
    c4013.setLink(10, in_reset, 1);
    in_reset.setLink(1, c4013, 10);

    clock.setState(nts::Tristate::True);
    clock.simulate(1);
    in_data.setState(nts::Tristate::True);
    in_data.simulate(1);
    in_set.setState(nts::Tristate::False);
    in_set.simulate(1);
    in_reset.setState(nts::Tristate::False);
    in_reset.simulate(1);

    c4013.simulate(1);
    c4013.simulate(2);
    cr_assert_eq(c4013.compute(1), nts::Tristate::True);
    cr_assert_eq(c4013.compute(2), nts::Tristate::False);
    cr_assert_eq(c4013.compute(13), nts::Tristate::True);
    cr_assert_eq(c4013.compute(12), nts::Tristate::False);
}

Test(c4013, computeDataUndefined)
{
    C4013 c4013;
    Clock clock;
    Input in_data;
    Input in_set;
    Input in_reset;

    c4013.setLink(3, clock, 1);
    clock.setLink(1, c4013, 3);
    c4013.setLink(11, clock, 1);
    clock.setLink(1, c4013, 11);

    c4013.setLink(5, in_data, 1);
    in_data.setLink(1, c4013, 5);
    c4013.setLink(9, in_data, 1);
    in_data.setLink(1, c4013, 9);

    c4013.setLink(6, in_set, 1);
    in_set.setLink(1, c4013, 6);
    c4013.setLink(8, in_set, 1);
    in_set.setLink(1, c4013, 8);

    c4013.setLink(4, in_reset, 1);
    in_reset.setLink(1, c4013, 4);
    c4013.setLink(10, in_reset, 1);
    in_reset.setLink(1, c4013, 10);

    clock.setState(nts::Tristate::True);
    clock.simulate(1);
    in_data.setState(nts::Tristate::Undefined);
    in_data.simulate(1);
    in_set.setState(nts::Tristate::False);
    in_set.simulate(1);
    in_reset.setState(nts::Tristate::False);
    in_reset.simulate(1);

    c4013.simulate(1);
    c4013.simulate(2);
    cr_assert_eq(c4013.compute(1), nts::Tristate::Undefined);
    cr_assert_eq(c4013.compute(2), nts::Tristate::Undefined);
    cr_assert_eq(c4013.compute(13), nts::Tristate::Undefined);
    cr_assert_eq(c4013.compute(12), nts::Tristate::Undefined);
}

Test(C4013, simulateSameTick)
{
    C4013 c4013;
    Clock clock;
    Input in_data;
    Input in_set;
    Input in_reset;

    c4013.setLink(3, clock, 1);
    clock.setLink(1, c4013, 3);
    c4013.setLink(11, clock, 1);
    clock.setLink(1, c4013, 11);

    c4013.setLink(5, in_data, 1);
    in_data.setLink(1, c4013, 5);
    c4013.setLink(9, in_data, 1);
    in_data.setLink(1, c4013, 9);

    c4013.setLink(6, in_set, 1);
    in_set.setLink(1, c4013, 6);
    c4013.setLink(8, in_set, 1);
    in_set.setLink(1, c4013, 8);

    c4013.setLink(4, in_reset, 1);
    in_reset.setLink(1, c4013, 4);
    c4013.setLink(10, in_reset, 1);
    in_reset.setLink(1, c4013, 10);

    clock.setState(nts::Tristate::True);
    clock.simulate(1);
    in_data.setState(nts::Tristate::True);
    in_data.simulate(1);
    in_set.setState(nts::Tristate::False);
    in_set.simulate(1);
    in_reset.setState(nts::Tristate::False);
    in_reset.simulate(1);

    c4013.simulate(1);
    cr_assert_no_throw(c4013.simulate(1));
}

