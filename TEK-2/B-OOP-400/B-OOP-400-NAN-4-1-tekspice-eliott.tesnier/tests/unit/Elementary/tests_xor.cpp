/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-tekspice-eliott.tesnier
** File description:
** tests_xor
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>

#include "Input.hpp"
#include "Xor.hpp"
#include "Error.hpp"

// Compute U - U
Test(Xor, computeUndefinedUndefined)
{
    Input input1;
    Input input2;
    Xor xorGate;

    input1.setState(nts::Tristate::Undefined);
    input2.setState(nts::Tristate::Undefined);
    input1.simulate(1);
    input2.simulate(1);

    xorGate.setLink(1, input1, 1);
    xorGate.setLink(2, input2, 1);
    input1.setLink(1, xorGate, 1);
    input2.setLink(1, xorGate, 2);

    cr_assert_eq(xorGate.compute(3), nts::Tristate::Undefined);
}

// Compute T - U
Test(Xor, computeTrueUndefined)
{
    Input input1;
    Input input2;
    Xor xorGate;

    input1.setState(nts::Tristate::True);
    input2.setState(nts::Tristate::Undefined);
    input1.simulate(1);
    input2.simulate(1);

    xorGate.setLink(1, input1, 1);
    xorGate.setLink(2, input2, 1);
    input1.setLink(1, xorGate, 1);
    input2.setLink(1, xorGate, 2);

    cr_assert_eq(xorGate.compute(3), nts::Tristate::Undefined);
}

// Compute F - U
Test(Xor, computeFalseUndefined)
{
    Input input1;
    Input input2;
    Xor xorGate;

    input1.setState(nts::Tristate::False);
    input2.setState(nts::Tristate::Undefined);
    input1.simulate(1);
    input2.simulate(1);

    xorGate.setLink(1, input1, 1);
    xorGate.setLink(2, input2, 1);
    input1.setLink(1, xorGate, 1);
    input2.setLink(1, xorGate, 2);

    cr_assert_eq(xorGate.compute(3), nts::Tristate::Undefined);
}

// Compute T - T
Test(Xor, computeTrueTrue)
{
    Input input1;
    Input input2;
    Xor xorGate;

    input1.setState(nts::Tristate::True);
    input2.setState(nts::Tristate::True);
    input1.simulate(1);
    input2.simulate(1);

    xorGate.setLink(1, input1, 1);
    xorGate.setLink(2, input2, 1);
    input1.setLink(1, xorGate, 1);
    input2.setLink(1, xorGate, 2);

    cr_assert_eq(xorGate.compute(3), nts::Tristate::False);
}

// Compute T - F
Test(Xor, computeTrueFalse)
{
    Input input1;
    Input input2;
    Xor xorGate;

    input1.setState(nts::Tristate::True);
    input2.setState(nts::Tristate::False);
    input1.simulate(1);
    input2.simulate(1);

    xorGate.setLink(1, input1, 1);
    xorGate.setLink(2, input2, 1);
    input1.setLink(1, xorGate, 1);
    input2.setLink(1, xorGate, 2);

    cr_assert_eq(xorGate.compute(3), nts::Tristate::True);
}

// Compute F - T
Test(Xor, computeFalseTrue)
{
    Input input1;
    Input input2;
    Xor xorGate;

    input1.setState(nts::Tristate::False);
    input2.setState(nts::Tristate::True);
    input1.simulate(1);
    input2.simulate(1);

    xorGate.setLink(1, input1, 1);
    xorGate.setLink(2, input2, 1);
    input1.setLink(1, xorGate, 1);
    input2.setLink(1, xorGate, 2);

    cr_assert_eq(xorGate.compute(3), nts::Tristate::True);
}

// Compute F - F
Test(Xor, computeFalseFalse)
{
    Input input1;
    Input input2;
    Xor xorGate;

    input1.setState(nts::Tristate::False);
    input2.setState(nts::Tristate::False);
    input1.simulate(1);
    input2.simulate(1);

    xorGate.setLink(1, input1, 1);
    xorGate.setLink(2, input2, 1);
    input1.setLink(1, xorGate, 1);
    input2.setLink(1, xorGate, 2);

    cr_assert_eq(xorGate.compute(3), nts::Tristate::False);
}

// Compute self link 1
Test(Xor, computeSelfLink1)
{
    Xor xorGate;

    xorGate.setLink(1, xorGate, 3);
    cr_assert_eq(xorGate.compute(3), nts::Tristate::Undefined);
}

// Compute self link 2
Test(Xor, computeSelfLink2)
{
    Xor xorGate;

    xorGate.setLink(2, xorGate, 3);
    cr_assert_eq(xorGate.compute(3), nts::Tristate::Undefined);
}

// Compute circular link
Test(Xor, computeCircularLink)
{
    Xor xorGate;
    Xor xorGate2;

    xorGate.setLink(1, xorGate2, 3);
    xorGate2.setLink(1, xorGate, 3);
    cr_assert_eq(xorGate.compute(3), nts::Tristate::Undefined);
}

// Compute invalid pin
Test(Xor, computeInvalidPin, .init = cr_redirect_stderr)
{
    Xor xorGate;

    cr_assert_eq(xorGate.compute(2), nts::Tristate::Undefined);
    cr_assert_eq(xorGate.compute(1), nts::Tristate::Undefined);
}
