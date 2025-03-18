/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** tests_circuit
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>

#include "Circuit.hpp"
#include "Factory.hpp"
#include "Error.hpp"

// Constructor
Test(Circuit, constructor)
{
    Circuit circuit;
}

// Destructor
Test(Circuit, destructor)
{
    Circuit circuit;
}

// AddComponent
Test(Circuit, addComponent)
{
    Circuit circuit;
    Factory factory;

    cr_assert_eq(circuit.hasComponent("input"), false);
    circuit.addComponent("input", "input", factory);
    cr_assert_eq(circuit.hasComponent("input"), true);
}

// HasComponent
Test(Circuit, hasComponent)
{
    Circuit circuit;
    Factory factory;

    cr_assert_eq(circuit.hasComponent("input"), false);
    circuit.addComponent("input", "input", factory);
    cr_assert_eq(circuit.hasComponent("input"), true);
}


// LinkComponents
Test(Circuit, linkComponents)
{
    Circuit circuit;
    Factory factory;

    circuit.addComponent("input1", "input", factory);
    circuit.addComponent("input2", "input", factory);
    circuit.linkComponents("input1", 1, "input2", 1);
    cr_assert_eq(circuit.hasComponent("input1"), true);
    cr_assert_eq(circuit.hasComponent("input2"), true);
}

// SetInput
Test(Circuit, setInputInput)
{
    Circuit circuit;
    Factory factory;

    circuit.addComponent("input", "input", factory);
    circuit.setInput("input", nts::Tristate::True);
    cr_assert_eq(circuit.hasComponent("input"), true);
}

Test(Circuit, setInputClock)
{
    Circuit circuit;
    Factory factory;

    circuit.addComponent("clock", "clock", factory);
    circuit.setInput("clock", nts::Tristate::True);
    cr_assert_eq(circuit.hasComponent("clock"), true);
}

Test(Circuit, setInputInvalidName)
{
    Circuit circuit;
    Factory factory;

    cr_assert_throw(circuit.setInput("input", nts::Tristate::True), nts::InvalidInput);
}

Test(Circuit, setInputInvalidType)
{
    Circuit circuit;
    Factory factory;

    circuit.addComponent("output", "output", factory);
    cr_assert_throw(circuit.setInput("output", nts::Tristate::True), nts::InvalidInput);
}

// Simulate
Test(Circuit, simulate)
{
    Circuit circuit;
    Factory factory;

    circuit.addComponent("input", "input", factory);
    circuit.setInput("input", nts::Tristate::True);
    circuit.simulate();
    cr_assert_eq(circuit.hasComponent("input"), true);
}

// Display
Test(Circuit, display, .init = cr_redirect_stdout)
{
    Circuit circuit;

    circuit.display();
}

// DisplayInputs
Test(Circuit, displayInputs, .init = cr_redirect_stdout)
{
    Circuit circuit;
    Factory factory;

    circuit.addComponent("input", "input", factory);
    circuit.setInput("input", nts::Tristate::True);
    circuit.display();
}

// DisplayOutputs
Test(Circuit, displayOutputs, .init = cr_redirect_stdout)
{
    Circuit circuit;
    Factory factory;

    circuit.addComponent("input", "input", factory);
    circuit.addComponent("output", "output", factory);
    circuit.linkComponents("input", 1, "output", 1);
    circuit.display();
}
