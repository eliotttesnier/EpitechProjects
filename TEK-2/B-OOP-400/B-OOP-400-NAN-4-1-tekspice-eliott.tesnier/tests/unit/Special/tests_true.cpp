/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-tekspice-eliott.tesnier
** File description:
** tests_true
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>

#include "True.hpp"
#include "Error.hpp"

// Constructor
Test(True, createTrue)
{
    True trueclass;

    cr_assert_eq(trueclass.compute(1), nts::Tristate::True);
}

// Invalid pin
Test(True, invalidPin, .init = cr_redirect_stderr)
{
    True trueclass;

    cr_assert_throw(trueclass.compute(2), nts::InvalidArgument);
    cr_assert_throw(trueclass.compute(0), nts::InvalidArgument);
}

// State transition
Test(True, stateTransition)
{
    True trueclass;

    trueclass.simulate(1);
    cr_assert_eq(trueclass.compute(1), nts::Tristate::True);

    trueclass.simulate(2);
    cr_assert_eq(trueclass.compute(1), nts::Tristate::True);

    trueclass.simulate(3);
    cr_assert_eq(trueclass.compute(1), nts::Tristate::True);
}
