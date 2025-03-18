/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-tekspice-eliott.tesnier
** File description:
** tests_input
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>

#include "Input.hpp"
#include "Error.hpp"

// Constructor
Test(Input, createInput)
{
    Input input;

    cr_assert_eq(input.compute(1), nts::Tristate::Undefined);
}

// Simulate without change
Test(Input, simulateWithoutChange)
{
    Input input;

    input.simulate(1);
    cr_assert_eq(input.compute(1), nts::Tristate::Undefined);
}

// Simulate same tick
Test(Input, simulateSameTick)
{
    Input input;

    input.simulate(1);
    cr_assert_eq(input.compute(1), nts::Tristate::Undefined);

    input.simulate(1);
    cr_assert_eq(input.compute(1), nts::Tristate::Undefined);
}

// Simulate with state change
Test(Input, simulateWithChange)
{
    Input input;

    input.setState(nts::Tristate::True);
    cr_assert_eq(input.compute(1), nts::Tristate::Undefined);

    input.simulate(2);
    cr_assert_eq(input.compute(1), nts::Tristate::True);
}

// State transition check
Test(Input, stateTransition)
{
    Input input;

    input.setState(nts::Tristate::True);
    input.simulate(1);
    cr_assert_eq(input.compute(1), nts::Tristate::True);

    input.setState(nts::Tristate::False);
    cr_assert_eq(input.compute(1), nts::Tristate::True);

    input.simulate(2);
    cr_assert_eq(input.compute(1), nts::Tristate::False);
}

// Check invalid pin
Test(Input, invalidPin, .init = cr_redirect_stderr)
{
    Input input;

    cr_assert_throw(input.compute(0), nts::InvalidArgument);
    cr_assert_throw(input.compute(2), nts::InvalidArgument);
}

// Check multiple state transitions
Test(Input, multipleStateChanges)
{
    Input input;

    input.setState(nts::Tristate::False);
    input.simulate(1);
    cr_assert_eq(input.compute(1), nts::Tristate::False);

    input.setState(nts::Tristate::True);
    cr_assert_eq(input.compute(1), nts::Tristate::False);

    input.simulate(2);
    cr_assert_eq(input.compute(1), nts::Tristate::True);

    input.setState(nts::Tristate::Undefined);
    cr_assert_eq(input.compute(1), nts::Tristate::True);

    input.simulate(3);
    cr_assert_eq(input.compute(1), nts::Tristate::Undefined);
}
