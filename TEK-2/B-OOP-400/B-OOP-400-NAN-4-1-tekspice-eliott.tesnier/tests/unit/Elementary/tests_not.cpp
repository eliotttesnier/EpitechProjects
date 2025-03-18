/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-tekspice-eliott.tesnier
** File description:
** tests_not
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>

#include "Not.hpp"
#include "Input.hpp"
#include "Error.hpp"

// constructor
Test(Not, createNot)
{
    Not notGate;

    cr_assert_eq(notGate.compute(2), nts::Tristate::Undefined);
}

// Compute with true
Test(Not, computeWithTrue)
{
    Not notGate;
    Input input;

    input.setState(nts::Tristate::True);
    input.simulate(1);
    notGate.setLink(1, input, 1);

    cr_assert_eq(notGate.compute(2), nts::Tristate::False);
}

// Compute with false
Test(Not, computeWithFalse)
{
    Not notGate;
    Input input;

    input.setState(nts::Tristate::False);
    input.simulate(1);
    notGate.setLink(1, input, 1);

    cr_assert_eq(notGate.compute(2), nts::Tristate::True);
}

// Compute with undefined
Test(Not, computeWithUndefined)
{
    Not notGate;
    Input input;

    input.setState(nts::Tristate::Undefined);
    input.simulate(1);
    notGate.setLink(1, input, 1);

    cr_assert_eq(notGate.compute(2), nts::Tristate::Undefined);
}

// No connection
Test(Not, computeWithoutConnection)
{
    Not notGate;

    cr_assert_eq(notGate.compute(2), nts::Tristate::Undefined);
}

// Invalide pin
Test(Not, computeInvalidPin, .init = cr_redirect_stderr)
{
    Not notGate;

    cr_assert_throw(notGate.compute(3), nts::InvalidArgument);
}

// Invalid pin undefined
Test(Not, computeWithInvalidPin)
{
    Not notGate;

    cr_assert_eq(notGate.compute(1), nts::Tristate::Undefined);
}

// Links pointer undefined
Test(Not, computeWithSelfLink)
{
    Not notGate;

    notGate.setLink(1, notGate, 2);
    cr_assert_eq(notGate.compute(2), nts::Tristate::Undefined);
}

// Compute circular link
Test(AnNotd, computeCircularLink)
{
    Not notGate;
    Not notGate2;

    notGate.setLink(1, notGate2, 2);
    notGate2.setLink(1, notGate, 2);
    cr_assert_eq(notGate.compute(2), nts::Tristate::Undefined);
}
