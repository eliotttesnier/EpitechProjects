/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** tests_4094
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>

#include "AComponent.hpp"
#include "4094.hpp"
#include "Input.hpp"
#include "Clock.hpp"
#include "True.hpp"
#include "Error.hpp"

// Constructor
Test(C4094, constructor)
{
    C4094 c4094;
}

// Destructor
Test(C4094, destructor)
{
    C4094 c4094;
}

// IsValidPin
Test(C4094, isValidPin)
{
    C4094 c4094;
    // Valid pins : 1 - 16 (8, 16 are power)

    cr_assert_throw(c4094.compute(0), nts::InvalidArgument)
    cr_assert_no_throw(c4094.compute(1))
    cr_assert_no_throw(c4094.compute(2))
    cr_assert_no_throw(c4094.compute(3))
    cr_assert_no_throw(c4094.compute(4))
    cr_assert_no_throw(c4094.compute(5))
    cr_assert_no_throw(c4094.compute(6))
    cr_assert_no_throw(c4094.compute(7))
    cr_assert_throw(c4094.compute(8), nts::InvalidArgument)
    cr_assert_no_throw(c4094.compute(9))
    cr_assert_no_throw(c4094.compute(10))
    cr_assert_no_throw(c4094.compute(11))
    cr_assert_no_throw(c4094.compute(12))
    cr_assert_no_throw(c4094.compute(13))
    cr_assert_no_throw(c4094.compute(14))
    cr_assert_no_throw(c4094.compute(15))
    cr_assert_throw(c4094.compute(16), nts::InvalidArgument)
    cr_assert_throw(c4094.compute(17), nts::InvalidArgument)
}

// ComputeOutput
Test(C4094, computeOutputs)
{
    C4094 c4094;
    Clock clock;
    Input data;
    True strobe;
    True enable;

    c4094.setLink(3, clock, 1);
    clock.setLink(1, c4094, 3);

    c4094.setLink(2, data, 1);
    data.setLink(1, c4094, 2);

    c4094.setLink(1, strobe, 1);
    strobe.setLink(1, c4094, 1);

    c4094.setLink(15, enable, 1);
    enable.setLink(1, c4094, 15);

    clock.setState(nts::Tristate::True);
    clock.simulate(1);
    data.setState(nts::Tristate::True);
    data.simulate(1);

    cr_assert_eq(c4094.compute(4), nts::Tristate::Undefined);
    cr_assert_eq(c4094.compute(5), nts::Tristate::Undefined);
    cr_assert_eq(c4094.compute(6), nts::Tristate::Undefined);
    cr_assert_eq(c4094.compute(7), nts::Tristate::Undefined);
    cr_assert_eq(c4094.compute(14), nts::Tristate::Undefined);
    cr_assert_eq(c4094.compute(13), nts::Tristate::Undefined);
    cr_assert_eq(c4094.compute(12), nts::Tristate::Undefined);
    cr_assert_eq(c4094.compute(11), nts::Tristate::Undefined);
    cr_assert_eq(c4094.compute(9), nts::Tristate::Undefined);
    cr_assert_eq(c4094.compute(10), nts::Tristate::Undefined);
}

// Simulate
Test(C4094, simulateUndefined)
{
    C4094 c4094;
    Clock clock;
    Input data;
    True strobe;
    True enable;

    c4094.setLink(3, clock, 1);
    clock.setLink(1, c4094, 3);

    c4094.setLink(2, data, 1);
    data.setLink(1, c4094, 2);

    c4094.setLink(1, strobe, 1);
    strobe.setLink(1, c4094, 1);

    c4094.setLink(15, enable, 1);
    enable.setLink(1, c4094, 15);

    cr_assert_no_throw(c4094.simulate(1));
}

Test(C4094, simulateSameTick)
{
    C4094 c4094;
    Clock clock;
    Input data;
    True strobe;
    True enable;

    c4094.setLink(3, clock, 1);
    clock.setLink(1, c4094, 3);

    c4094.setLink(2, data, 1);
    data.setLink(1, c4094, 2);

    c4094.setLink(1, strobe, 1);
    strobe.setLink(1, c4094, 1);

    c4094.setLink(15, enable, 1);
    enable.setLink(1, c4094, 15);

    cr_assert_no_throw(c4094.simulate(1));
    cr_assert_no_throw(c4094.simulate(1));
}

Test(C4094, simulateRisingEdge)
{
    C4094 c4094;
    Clock clock;
    Input data;
    True strobe;
    True enable;

    c4094.setLink(3, clock, 1);
    clock.setLink(1, c4094, 3);

    c4094.setLink(2, data, 1);
    data.setLink(1, c4094, 2);

    c4094.setLink(1, strobe, 1);
    strobe.setLink(1, c4094, 1);

    c4094.setLink(15, enable, 1);
    enable.setLink(1, c4094, 15);

    clock.setState(nts::Tristate::False);
    clock.simulate(1);
    data.setState(nts::Tristate::False);
    data.simulate(1);

    cr_assert_no_throw(c4094.simulate(1));
    cr_assert_no_throw(c4094.simulate(2));
}

Test(C4094, simulateDataTrue)
{
    C4094 c4094;
    Clock clock;
    Input data;
    True strobe;
    True enable;

    c4094.setLink(3, clock, 1);
    clock.setLink(1, c4094, 3);

    c4094.setLink(2, data, 1);
    data.setLink(1, c4094, 2);

    c4094.setLink(1, strobe, 1);
    strobe.setLink(1, c4094, 1);

    c4094.setLink(15, enable, 1);
    enable.setLink(1, c4094, 15);

    clock.setState(nts::Tristate::False);
    clock.simulate(1);
    data.setState(nts::Tristate::True);
    data.simulate(1);

    cr_assert_no_throw(c4094.simulate(1));
}
