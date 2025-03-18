/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-tekspice-eliott.tesnier
** File description:
** tests_output
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>

#include "Output.hpp"
#include "Input.hpp"
#include "False.hpp"
#include "Error.hpp"

// Constructor
Test(Output, computeWithInitialUndefined)
{
    Output output;
    Input input;

    output.setLink(1, input, 1);
    cr_assert_eq(output.compute(1), nts::Tristate::Undefined);
}


// Compute output without connection
Test(Output, computeWithoutConnection, .init = cr_redirect_stderr)
{
    Output output;

    cr_assert_throw(output.compute(1), nts::InvalidArgument);
}

// Compute output with a valid connection (Input)
Test(Output, computeWithInput)
{
    Output output;
    Input input;

    input.setState(nts::Tristate::True);
    input.simulate(1);

    output.setLink(1, input, 1);

    cr_assert_eq(output.compute(1), nts::Tristate::True);
}

// Compute output with a False component
Test(Output, computeWithFalse)
{
    Output output;
    False falseComponent;

    output.setLink(1, falseComponent, 1);

    cr_assert_eq(output.compute(1), nts::Tristate::False);
}

// Compute output with an updated Input
Test(Output, computeWithUpdatedInput)
{
    Output output;
    Input input;

    input.setState(nts::Tristate::False);
    input.simulate(1);
    output.setLink(1, input, 1);

    cr_assert_eq(output.compute(1), nts::Tristate::False);

    input.setState(nts::Tristate::Undefined);
    input.simulate(2);

    cr_assert_eq(output.compute(1), nts::Tristate::Undefined);
}

// Compute with an invalid pin
Test(Output, computeInvalidPin, .init = cr_redirect_stderr)
{
    Output output;

    cr_assert_throw(output.compute(2), nts::InvalidArgument);
}
