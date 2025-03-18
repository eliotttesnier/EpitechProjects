/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-tekspice-eliott.tesnier
** File description:
** tests_false
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>

#include "False.hpp"
#include "Error.hpp"

// Constructor
Test(False, createFalse)
{
    False falseclass;

    cr_assert_eq(falseclass.compute(1), nts::Tristate::False);
}

// Invalid pin
Test(False, invalidPin, .init = cr_redirect_stderr)
{
    False falseclass;

    cr_assert_throw(falseclass.compute(2), nts::InvalidArgument);
    cr_assert_throw(falseclass.compute(0), nts::InvalidArgument);
}

// State transition
Test(False, stateTransition)
{
    False falseclass;

    falseclass.simulate(1);
    cr_assert_eq(falseclass.compute(1), nts::Tristate::False);

    falseclass.simulate(2);
    cr_assert_eq(falseclass.compute(1), nts::Tristate::False);

    falseclass.simulate(3);
    cr_assert_eq(falseclass.compute(1), nts::Tristate::False);
}
