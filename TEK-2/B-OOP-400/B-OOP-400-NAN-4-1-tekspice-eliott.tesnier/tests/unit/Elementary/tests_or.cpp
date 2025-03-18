/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-tekspice-eliott.tesnier
** File description:
** tests_or
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>

#include "Input.hpp"
#include "Or.hpp"
#include "Error.hpp"

// Constructeur
Test(Or, createOr)
{
    Or orGate;
    cr_assert_eq(orGate.compute(3), nts::Tristate::Undefined);
}

// Compute - U U
Test(Or, computeUndefinedUndefined)
{
    Input input1;
    Input input2;
    Or orGate;

    input1.setState(nts::Tristate::Undefined);
    input2.setState(nts::Tristate::Undefined);
    input1.simulate(1);
    input2.simulate(1);

    orGate.setLink(1, input1, 1);
    orGate.setLink(2, input2, 1);
    cr_assert_eq(orGate.compute(3), nts::Tristate::Undefined);
}

// Compute - U 0
Test(Or, computeUndefinedFalse)
{
    Input input1;
    Input input2;
    Or orGate;

    input1.setState(nts::Tristate::Undefined);
    input2.setState(nts::Tristate::False);
    input1.simulate(1);
    input2.simulate(1);

    orGate.setLink(1, input1, 1);
    orGate.setLink(2, input2, 1);
    cr_assert_eq(orGate.compute(3), nts::Tristate::Undefined);
}

// Compute - U 1
Test(Or, computeUndefinedTrue)
{
    Input input1;
    Input input2;
    Or orGate;

    input1.setState(nts::Tristate::Undefined);
    input2.setState(nts::Tristate::True);
    input1.simulate(1);
    input2.simulate(1);

    orGate.setLink(1, input1, 1);
    orGate.setLink(2, input2, 1);
    cr_assert_eq(orGate.compute(3), nts::Tristate::True);
}

// Compute - 0 0
Test(Or, computeFalseFalse)
{
    Input input1;
    Input input2;
    Or orGate;

    input1.setState(nts::Tristate::False);
    input2.setState(nts::Tristate::False);
    input1.simulate(1);
    input2.simulate(1);

    orGate.setLink(1, input1, 1);
    orGate.setLink(2, input2, 1);
    cr_assert_eq(orGate.compute(3), nts::Tristate::False);
}

// Compute - 1 0
Test(Or, computeTrueFalse)
{
    Input input1;
    Input input2;
    Or orGate;

    input1.setState(nts::Tristate::True);
    input2.setState(nts::Tristate::False);
    input1.simulate(1);
    input2.simulate(1);

    orGate.setLink(1, input1, 1);
    orGate.setLink(2, input2, 1);
    cr_assert_eq(orGate.compute(3), nts::Tristate::True);
}

// Compute - 1 1
Test(Or, computeTrueTrue)
{
    Input input1;
    Input input2;
    Or orGate;

    input1.setState(nts::Tristate::True);
    input2.setState(nts::Tristate::True);
    input1.simulate(1);
    input2.simulate(1);

    orGate.setLink(1, input1, 1);
    orGate.setLink(2, input2, 1);
    cr_assert_eq(orGate.compute(3), nts::Tristate::True);
}

// Compute self link
Test(Or, computeSelfLink)
{
    Or orGate;

    orGate.setLink(1, orGate, 3);
    cr_assert_eq(orGate.compute(3), nts::Tristate::Undefined);
}

// Compute invalid pin Throw
Test(Or, computeInvalidPinThrow, .init = cr_redirect_stderr)
{
    Or orGate;

    cr_assert_throw(orGate.compute(4), nts::InvalidArgument);
    cr_assert_throw(orGate.compute(0), nts::InvalidArgument);
}

// Comoute Invalid pin
Test(Or, computeInvalidPin, .init = cr_redirect_stderr)
{
    Or orGate;

    cr_assert_eq(orGate.compute(1), nts::Tristate::Undefined);
    cr_assert_eq(orGate.compute(2), nts::Tristate::Undefined);
}

// Compute self link error
Test(Or, computeSelfLinkError)
{
    Or orGate;

    orGate.setLink(2, orGate, 3);
    cr_assert_eq(orGate.compute(3), nts::Tristate::Undefined);
}

// Compute circular link
Test(Or, computeCircularLink)
{
    Or orGate;
    Or orGate2;

    orGate.setLink(1, orGate2, 3);
    orGate2.setLink(1, orGate, 3);
    cr_assert_eq(orGate.compute(3), nts::Tristate::Undefined);
}
