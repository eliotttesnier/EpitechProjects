/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-tekspice-eliott.tesnier
** File description:
** tests_4017
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>

#include "AComponent.hpp"
#include "4017.hpp"
#include "Input.hpp"
#include "Clock.hpp"
#include "Error.hpp"

// Constructor
Test(C4017, constructor)
{
    C4017 c4017;
}

// Destructor
Test(C4017, destructor)
{
    C4017 c4017;
}

// IsValidPin
Test(C4017, isValidPin)
{
    C4017 c4017;
    // Valid pins : 1 - 15 (8 is power)

    cr_assert_throw(c4017.compute(0), nts::InvalidArgument)
    cr_assert_no_throw(c4017.compute(1))
    cr_assert_no_throw(c4017.compute(2))
    cr_assert_no_throw(c4017.compute(3))
    cr_assert_no_throw(c4017.compute(4))
    cr_assert_no_throw(c4017.compute(5))
    cr_assert_no_throw(c4017.compute(6))
    cr_assert_no_throw(c4017.compute(7))
    cr_assert_throw(c4017.compute(8), nts::InvalidArgument)
    cr_assert_no_throw(c4017.compute(9))
    cr_assert_no_throw(c4017.compute(10))
    cr_assert_no_throw(c4017.compute(11))
    cr_assert_no_throw(c4017.compute(12))
    cr_assert_no_throw(c4017.compute(13))
    cr_assert_no_throw(c4017.compute(14))
    cr_assert_no_throw(c4017.compute(15))
    cr_assert_throw(c4017.compute(16), nts::InvalidArgument)
}

// Define the pin numbers correctly based on your component implementation
const std::size_t CP0_PIN = 14;
const std::size_t CP1_PIN = 13;
const std::size_t MR_PIN = 15;
const std::size_t Q0_PIN = 3;
const std::size_t Q1_PIN = 2;
const std::size_t Q2_PIN = 4;
const std::size_t Q3_PIN = 7;
const std::size_t Q4_PIN = 10;
const std::size_t Q5_PIN = 1;
const std::size_t Q6_PIN = 5;
const std::size_t Q7_PIN = 6;
const std::size_t Q8_PIN = 9;
const std::size_t Q9_PIN = 11;
const std::size_t Q59_PIN = 12;

// ComputeOutput initial state
Test(C4017, computeInitialState)
{
    C4017 c4017;
    Input cp0;
    Input cp1;
    Input mr;

    c4017.setLink(CP0_PIN, cp0, 1);
    cp0.setLink(1, c4017, CP0_PIN);
    c4017.setLink(CP1_PIN, cp1, 1);
    cp1.setLink(1, c4017, CP1_PIN);
    c4017.setLink(MR_PIN, mr, 1);
    mr.setLink(1, c4017, MR_PIN);

    cp0.setState(nts::Tristate::False);
    cp1.setState(nts::Tristate::True);
    mr.setState(nts::Tristate::False);

    cp0.simulate(1);
    cp1.simulate(1);
    mr.simulate(1);
    c4017.simulate(1);

    cr_assert_eq(c4017.compute(Q0_PIN), nts::Tristate::True);  // Q0 is true
    cr_assert_eq(c4017.compute(Q1_PIN), nts::Tristate::False); // Q1 is false
    cr_assert_eq(c4017.compute(Q2_PIN), nts::Tristate::False); // Q2 is false
    cr_assert_eq(c4017.compute(Q3_PIN), nts::Tristate::False); // Q3 is false
    cr_assert_eq(c4017.compute(Q4_PIN), nts::Tristate::False); // Q4 is false
    cr_assert_eq(c4017.compute(Q5_PIN), nts::Tristate::False); // Q5 is false
    cr_assert_eq(c4017.compute(Q6_PIN), nts::Tristate::False); // Q6 is false
    cr_assert_eq(c4017.compute(Q7_PIN), nts::Tristate::False); // Q7 is false
    cr_assert_eq(c4017.compute(Q8_PIN), nts::Tristate::False); // Q8 is false
    cr_assert_eq(c4017.compute(Q9_PIN), nts::Tristate::False); // Q9 is false
    cr_assert_eq(c4017.compute(Q59_PIN), nts::Tristate::True); // Q5-9 output is true (counter < 5)
}

// Setup helper function for the Johnson counter circuit
void setupC4017Circuit(C4017 &c4017, Input &clock0, Input &clock1, Input &reset)
{
    c4017.setLink(CP0_PIN, clock0, 1);
    clock0.setLink(1, c4017, CP0_PIN);

    c4017.setLink(CP1_PIN, clock1, 1);
    clock1.setLink(1, c4017, CP1_PIN);

    c4017.setLink(MR_PIN, reset, 1);
    reset.setLink(1, c4017, MR_PIN);

    clock0.setState(nts::Tristate::False);
    clock1.setState(nts::Tristate::True);
    reset.setState(nts::Tristate::False);

    clock0.simulate(1);
    clock1.simulate(1);
    reset.simulate(1);
    c4017.simulate(1);
}

// Test reset functionality
Test(C4017, resetFunctionality)
{
    C4017 c4017;
    Input clock0;
    Input clock1;
    Input reset;

    setupC4017Circuit(c4017, clock0, clock1, reset);

    clock0.setState(nts::Tristate::True);
    clock0.simulate(2);
    c4017.simulate(2);

    clock0.setState(nts::Tristate::False);
    clock0.simulate(3);
    c4017.simulate(3);

    cr_assert_eq(c4017.compute(Q1_PIN), nts::Tristate::True);

    reset.setState(nts::Tristate::True);
    reset.simulate(4);
    c4017.simulate(4);

    cr_assert_eq(c4017.compute(Q0_PIN), nts::Tristate::True);
    cr_assert_eq(c4017.compute(Q1_PIN), nts::Tristate::False);
    cr_assert_eq(c4017.compute(Q59_PIN), nts::Tristate::True);
}

// Test counter increment
Test(C4017, counterIncrement)
{
    C4017 c4017;
    Input clock0;
    Input clock1;
    Input reset;

    setupC4017Circuit(c4017, clock0, clock1, reset);

    cr_assert_eq(c4017.compute(Q0_PIN), nts::Tristate::True);
    cr_assert_eq(c4017.compute(Q1_PIN), nts::Tristate::False);

    clock0.setState(nts::Tristate::True);
    clock0.simulate(2);
    c4017.simulate(2);

    clock0.setState(nts::Tristate::False);
    clock0.simulate(3);
    c4017.simulate(3);

    cr_assert_eq(c4017.compute(Q0_PIN), nts::Tristate::False);
    cr_assert_eq(c4017.compute(Q1_PIN), nts::Tristate::True);
    cr_assert_eq(c4017.compute(Q59_PIN), nts::Tristate::True);

    clock0.setState(nts::Tristate::True);
    clock0.simulate(4);
    c4017.simulate(4);

    clock0.setState(nts::Tristate::False);
    clock0.simulate(5);
    c4017.simulate(5);

    cr_assert_eq(c4017.compute(Q1_PIN), nts::Tristate::False);
    cr_assert_eq(c4017.compute(Q2_PIN), nts::Tristate::True);
    cr_assert_eq(c4017.compute(Q59_PIN), nts::Tristate::True);
}

// Test full counter cycle
Test(C4017, fullCounterCycle)
{
    C4017 c4017;
    Input clock0;
    Input clock1;
    Input reset;

    setupC4017Circuit(c4017, clock0, clock1, reset);
    const std::size_t qPins[10] = {Q0_PIN, Q1_PIN, Q2_PIN, Q3_PIN, Q4_PIN, Q5_PIN, Q6_PIN, Q7_PIN, Q8_PIN, Q9_PIN};

    cr_assert_eq(c4017.compute(qPins[0]), nts::Tristate::True);

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (j == i) {
                cr_assert_eq(c4017.compute(qPins[j]), nts::Tristate::True, "Expected pin %zu to be True at counter position %d", qPins[j], i);
            } else {
                cr_assert_eq(c4017.compute(qPins[j]), nts::Tristate::False, "Expected pin %zu to be False at counter position %d", qPins[j], i);
            }
        }
        if (i >= 5 && i <= 9) {
            cr_assert_eq(c4017.compute(Q59_PIN), nts::Tristate::False, "Expected pin 12 to be False at counter position %d", i);
        } else {
            cr_assert_eq(c4017.compute(Q59_PIN), nts::Tristate::True, "Expected pin 12 to be True at counter position %d", i);
        }
        if (i < 9) {
            // Advance counter
            clock0.setState(nts::Tristate::True);
            clock0.simulate(i*2 + 2);
            c4017.simulate(i*2 + 2);
            clock0.setState(nts::Tristate::False);
            clock0.simulate(i*2 + 3);
            c4017.simulate(i*2 + 3);
        }
    }
}

// Test CP1 functionality - Counter should only increment when CP1 is high
Test(C4017, cp1Functionality)
{
    C4017 c4017;
    Input clock0;
    Input clock1;
    Input reset;

    c4017.setLink(CP0_PIN, clock0, 1);
    clock0.setLink(1, c4017, CP0_PIN);
    c4017.setLink(CP1_PIN, clock1, 1);
    clock1.setLink(1, c4017, CP1_PIN);
    c4017.setLink(MR_PIN, reset, 1);
    reset.setLink(1, c4017, MR_PIN);

    clock0.setState(nts::Tristate::False);
    clock1.setState(nts::Tristate::False); // CP1 is low
    reset.setState(nts::Tristate::False);

    clock0.simulate(1);
    clock1.simulate(1);
    reset.simulate(1);
    c4017.simulate(1);

    cr_assert_eq(c4017.compute(Q0_PIN), nts::Tristate::True);

    clock0.setState(nts::Tristate::True);
    clock0.simulate(2);
    c4017.simulate(2);

    cr_assert_eq(c4017.compute(Q0_PIN), nts::Tristate::True);

    clock1.setState(nts::Tristate::True);
    clock1.simulate(3);
    c4017.simulate(3);

    clock0.setState(nts::Tristate::False);
    clock0.simulate(4);
    c4017.simulate(4);

    clock0.setState(nts::Tristate::True);
    clock0.simulate(5);
    c4017.simulate(5);

    clock0.setState(nts::Tristate::False);
    clock0.simulate(6);
    c4017.simulate(6);

    cr_assert_eq(c4017.compute(Q0_PIN), nts::Tristate::False);
    cr_assert_eq(c4017.compute(Q1_PIN), nts::Tristate::False);
}

// Test undefined inputs
Test(C4017, undefinedInputs)
{
    C4017 c4017;
    Input clock0;
    Input clock1;
    Input reset;

    setupC4017Circuit(c4017, clock0, clock1, reset);

    clock0.setState(nts::Tristate::Undefined);
    clock0.simulate(2);
    c4017.simulate(2);

    cr_assert_eq(c4017.compute(Q0_PIN), nts::Tristate::Undefined);
    cr_assert_eq(c4017.compute(Q1_PIN), nts::Tristate::Undefined);
    cr_assert_eq(c4017.compute(Q59_PIN), nts::Tristate::Undefined);

    clock0.setState(nts::Tristate::False);
    clock0.simulate(3);
    c4017.simulate(3);

    clock1.setState(nts::Tristate::Undefined);
    clock1.simulate(4);
    c4017.simulate(4);

    cr_assert_eq(c4017.compute(Q0_PIN), nts::Tristate::Undefined);
    cr_assert_eq(c4017.compute(Q59_PIN), nts::Tristate::Undefined);

    clock1.setState(nts::Tristate::True);
    clock1.simulate(5);
    c4017.simulate(5);

    reset.setState(nts::Tristate::Undefined);
    reset.simulate(6);
    c4017.simulate(6);

    cr_assert_eq(c4017.compute(Q0_PIN), nts::Tristate::Undefined);
    cr_assert_eq(c4017.compute(Q59_PIN), nts::Tristate::Undefined);
}

// Test simulateSameTick
Test(C4017, simulateSameTick)
{
    C4017 c4017;
    Input clock0;
    Input clock1;
    Input reset;

    setupC4017Circuit(c4017, clock0, clock1, reset);

    c4017.simulate(1);
    cr_assert_no_throw(c4017.simulate(1));
}

// Test wrapping behavior after reaching the end of the cycle
Test(C4017, wrapBehavior)
{
    C4017 c4017;
    Input clock0;
    Input clock1;
    Input reset;

    setupC4017Circuit(c4017, clock0, clock1, reset);

    for (int i = 0; i < 10; i++) {
        // Advance counter
        clock0.setState(nts::Tristate::True);
        clock0.simulate(i*2 + 2);
        c4017.simulate(i*2 + 2);
        clock0.setState(nts::Tristate::False);
        clock0.simulate(i*2 + 3);
        c4017.simulate(i*2 + 3);
    }
    cr_assert_eq(c4017.compute(Q0_PIN), nts::Tristate::True);
    cr_assert_eq(c4017.compute(Q9_PIN), nts::Tristate::False);
}
