/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-tekspice-eliott.tesnier
** File description:
** test_clock
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>

#include "Clock.hpp"
#include "Error.hpp"

// Constructor
Test(Clock, createClock)
{
    Clock clock;

    cr_assert_eq(clock.compute(1), nts::Tristate::Undefined);
}

// setState
Test(Clock, setState)
{
    Clock clock;

    clock.setState(nts::Tristate::True);
    cr_assert_eq(clock.compute(1), nts::Tristate::Undefined);

    clock.simulate(1);
    cr_assert_eq(clock.compute(1), nts::Tristate::True);

    clock.setState(nts::Tristate::False);
    cr_assert_eq(clock.compute(1), nts::Tristate::True);

    clock.simulate(2);
    cr_assert_eq(clock.compute(1), nts::Tristate::False);
}

// Simulation
Test(Clock, simulate)
{
    Clock clock;

    clock.setState(nts::Tristate::True);
    clock.simulate(1);
    cr_assert_eq(clock.compute(1), nts::Tristate::True);

    clock.simulate(2);
    cr_assert_eq(clock.compute(1), nts::Tristate::False);

    clock.simulate(3);
    cr_assert_eq(clock.compute(1), nts::Tristate::True);
}

Test(Clock, simulate_same_tick)
{
    Clock clock;

    clock.setState(nts::Tristate::True);
    clock.simulate(1);
    cr_assert_eq(clock.compute(1), nts::Tristate::True);

    clock.simulate(1);
    cr_assert_eq(clock.compute(1), nts::Tristate::True);

    clock.simulate(2);
    cr_assert_eq(clock.compute(1), nts::Tristate::False);
}

// Invalid pin
Test(Clock, invalidPin, .init = cr_redirect_stderr)
{
    Clock clock;

    cr_assert_throw(clock.compute(2), nts::InvalidArgument);
    cr_assert_throw(clock.compute(0), nts::InvalidArgument);
}

// State transition
Test(Clock, stateTransition)
{
    Clock clock;

    clock.setState(nts::Tristate::True);
    clock.simulate(1);
    cr_assert_eq(clock.compute(1), nts::Tristate::True);

    clock.simulate(2);
    cr_assert_eq(clock.compute(1), nts::Tristate::False);

    clock.simulate(3);
    cr_assert_eq(clock.compute(1), nts::Tristate::True);
}
