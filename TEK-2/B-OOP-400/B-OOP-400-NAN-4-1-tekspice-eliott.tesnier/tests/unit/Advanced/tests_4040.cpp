/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** tests_4040
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>

#include "AComponent.hpp"
#include "4040.hpp"
#include "Input.hpp"
#include "Clock.hpp"
#include "Error.hpp"

// Constructor
Test(C4040, constructor)
{
    C4040 c4040;
}

// Destructor
Test(C4040, destructor)
{
    C4040 c4040;
}

// IsValidPin
Test(C4040, isValidPin)
{
    C4040 c4040;
    // Valid pins : 1 - 16 (8, 16 are power)

    cr_assert_throw(c4040.compute(0), nts::InvalidArgument)
    cr_assert_no_throw(c4040.compute(1))
    cr_assert_no_throw(c4040.compute(2))
    cr_assert_no_throw(c4040.compute(3))
    cr_assert_no_throw(c4040.compute(4))
    cr_assert_no_throw(c4040.compute(5))
    cr_assert_no_throw(c4040.compute(6))
    cr_assert_no_throw(c4040.compute(7))
    cr_assert_throw(c4040.compute(8), nts::InvalidArgument)
    cr_assert_no_throw(c4040.compute(9))
    cr_assert_no_throw(c4040.compute(10))
    cr_assert_no_throw(c4040.compute(11))
    cr_assert_no_throw(c4040.compute(12))
    cr_assert_no_throw(c4040.compute(13))
    cr_assert_no_throw(c4040.compute(14))
    cr_assert_no_throw(c4040.compute(15))
    cr_assert_throw(c4040.compute(16), nts::InvalidArgument)
    cr_assert_throw(c4040.compute(17), nts::InvalidArgument)
}

// ComputeOutput
Test(C4040, computeResetTrue)
{
    C4040 c4040;
    Clock clock;
    Input reset;

    c4040.setLink(10, clock, 1);
    clock.setLink(1, c4040, 10);

    c4040.setLink(11, reset, 1);
    reset.setLink(1, c4040, 11);

    reset.setState(nts::Tristate::True);
    reset.simulate(1);

    cr_assert_eq(c4040.compute(1), nts::Tristate::False);
}

Test(C4040, computeEveryOutput)
{
    C4040 c4040;
    Clock clock;
    Input reset;

    c4040.setLink(10, clock, 1);
    clock.setLink(1, c4040, 10);

    c4040.setLink(11, reset, 1);
    reset.setLink(1, c4040, 11);

    reset.setState(nts::Tristate::False);
    reset.simulate(1);
    clock.setState(nts::Tristate::False);
    clock.simulate(1);

    cr_assert_eq(c4040.compute(9), nts::Tristate::False);
    cr_assert_eq(c4040.compute(7), nts::Tristate::False);
    cr_assert_eq(c4040.compute(6), nts::Tristate::False);
    cr_assert_eq(c4040.compute(5), nts::Tristate::False);
    cr_assert_eq(c4040.compute(3), nts::Tristate::False);
    cr_assert_eq(c4040.compute(2), nts::Tristate::False);
    cr_assert_eq(c4040.compute(4), nts::Tristate::False);
    cr_assert_eq(c4040.compute(13), nts::Tristate::False);
    cr_assert_eq(c4040.compute(12), nts::Tristate::False);
    cr_assert_eq(c4040.compute(14), nts::Tristate::False);
    cr_assert_eq(c4040.compute(15), nts::Tristate::False);
    cr_assert_eq(c4040.compute(1), nts::Tristate::False);
}

Test(C4040, simulateResetTrue)
{
    C4040 c4040;
    Clock clock;
    Input reset;

    c4040.setLink(10, clock, 1);
    clock.setLink(1, c4040, 10);

    c4040.setLink(11, reset, 1);
    reset.setLink(1, c4040, 11);

    reset.setState(nts::Tristate::True);
    reset.simulate(1);
    clock.setState(nts::Tristate::False);
    clock.simulate(1);

    cr_assert_no_throw(c4040.simulate(1));
}

Test(C4040, simulateSameTick)
{
    C4040 c4040;
    Clock clock;
    Input reset;

    c4040.setLink(10, clock, 1);
    clock.setLink(1, c4040, 10);

    c4040.setLink(11, reset, 1);
    reset.setLink(1, c4040, 11);

    reset.setState(nts::Tristate::True);
    reset.simulate(1);
    clock.setState(nts::Tristate::False);
    clock.simulate(1);

    cr_assert_no_throw(c4040.simulate(1));
    cr_assert_no_throw(c4040.simulate(1));
}

Test(C4040, simulateRisingEdge)
{
    C4040 c4040;
    Clock clock;
    Input reset;

    c4040.setLink(10, clock, 1);
    clock.setLink(1, c4040, 10);

    c4040.setLink(11, reset, 1);
    reset.setLink(1, c4040, 11);

    reset.setState(nts::Tristate::False);
    reset.simulate(1);
    clock.setState(nts::Tristate::True);
    clock.simulate(1);

    c4040.simulate(1);
    cr_assert_no_throw(c4040.simulate(2));
}

Test(C4040, simulateFallingEdge)
{
    C4040 c4040;
    Clock clock;
    Input reset;

    c4040.setLink(10, clock, 1);
    clock.setLink(1, c4040, 10);

    c4040.setLink(11, reset, 1);
    reset.setLink(1, c4040, 11);

    reset.setState(nts::Tristate::False);
    reset.simulate(1);
    clock.setState(nts::Tristate::False);
    clock.simulate(1);

    c4040.simulate(1);
    cr_assert_no_throw(c4040.simulate(2));
}
