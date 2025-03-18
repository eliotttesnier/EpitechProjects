/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** tests_and
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>

#include "Input.hpp"
#include "And.hpp"
#include "Error.hpp"

// Constructor
Test(And, createAnd)
{
    And andGate;

    cr_assert_eq(andGate.compute(1), nts::Tristate::Undefined);
}

// Compute - U U
Test(And, compute)
{
    Input input1;
    Input input2;
    And andGate;

    input1.setState(nts::Tristate::Undefined);
    input2.setState(nts::Tristate::Undefined);
    input1.simulate(1);
    input2.simulate(1);

    andGate.setLink(1, input1, 1);
    andGate.setLink(2, input2, 1);
    input1.setLink(1, andGate, 1);
    input2.setLink(1, andGate, 2);
    cr_assert_eq(andGate.compute(3), nts::Tristate::Undefined);
}

// Compute - U 0
Test(And, compute1)
{
    Input input1;
    Input input2;
    And andGate;

    input1.setState(nts::Tristate::Undefined);
    input2.setState(nts::Tristate::False);
    input1.simulate(1);
    input2.simulate(1);

    andGate.setLink(1, input1, 1);
    andGate.setLink(2, input2, 1);
    input1.setLink(1, andGate, 1);
    input2.setLink(1, andGate, 2);
    cr_assert_eq(andGate.compute(3), nts::Tristate::False);
}

// Compute - U 1
Test(And, compute6)
{
    Input input1;
    Input input2;
    And andGate;

    input1.setState(nts::Tristate::Undefined);
    input2.setState(nts::Tristate::True);
    input1.simulate(1);
    input2.simulate(1);

    andGate.setLink(1, input1, 1);
    andGate.setLink(2, input2, 1);
    input1.setLink(1, andGate, 1);
    input2.setLink(1, andGate, 2);
    cr_assert_eq(andGate.compute(3), nts::Tristate::Undefined);
}

// Compute - 0 0
Test(And, compute2)
{
    Input input1;
    Input input2;
    And andGate;

    input1.setState(nts::Tristate::False);
    input2.setState(nts::Tristate::False);
    input1.simulate(1);
    input2.simulate(1);

    andGate.setLink(1, input1, 1);
    andGate.setLink(2, input2, 1);
    input1.setLink(1, andGate, 1);
    input2.setLink(1, andGate, 2);
    cr_assert_eq(andGate.compute(3), nts::Tristate::False);
}

// Compute - 1 0
Test(And, compute3)
{
    Input input1;
    Input input2;
    And andGate;

    input1.setState(nts::Tristate::True);
    input2.setState(nts::Tristate::False);
    input1.simulate(1);
    input2.simulate(1);

    andGate.setLink(1, input1, 1);
    andGate.setLink(2, input2, 1);
    input1.setLink(1, andGate, 1);
    input2.setLink(1, andGate, 2);
    cr_assert_eq(andGate.compute(3), nts::Tristate::False);
}

// Compute - 1 1
Test(And, compute5)
{
    Input input1;
    Input input2;
    And andGate;

    input1.setState(nts::Tristate::True);
    input2.setState(nts::Tristate::True);
    input1.simulate(1);
    input2.simulate(1);

    andGate.setLink(1, input1, 1);
    andGate.setLink(2, input2, 1);
    input1.setLink(1, andGate, 1);
    input2.setLink(1, andGate, 2);
    cr_assert_eq(andGate.compute(3), nts::Tristate::True);
}

// Compute self link
Test(And, computeSelfLink)
{
    And andGate;

    andGate.setLink(1, andGate, 3);
    cr_assert_eq(andGate.compute(3), nts::Tristate::Undefined);
}

// Compute self link 2
Test(And, computeSelfLink2)
{
    And andGate;

    andGate.setLink(2, andGate, 3);
    cr_assert_eq(andGate.compute(3), nts::Tristate::Undefined);
}

// Compute circular link
Test(And, computeCircularLink)
{
    And andGate;
    And andGate2;

    andGate.setLink(1, andGate2, 3);
    andGate2.setLink(1, andGate, 3);
    cr_assert_eq(andGate.compute(3), nts::Tristate::Undefined);
}

// Compute invalid pin
Test(And, computeInvalidPin, .init = cr_redirect_stderr)
{
    And andGate;

    cr_assert_throw(andGate.compute(4), nts::InvalidArgument);
    cr_assert_throw(andGate.compute(0), nts::InvalidArgument);
}
