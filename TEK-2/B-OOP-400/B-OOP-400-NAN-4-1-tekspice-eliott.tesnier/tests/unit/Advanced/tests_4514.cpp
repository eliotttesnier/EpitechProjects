/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-tekspice-eliott.tesnier
** File description:
** tests_4514
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>

#include "AComponent.hpp"
#include "4514.hpp"
#include "Input.hpp"
#include "Error.hpp"

// Constructor
Test(C4514, constructor)
{
    C4514 c4514;
}

// Destructor
Test(C4514, destructor)
{
    C4514 c4514;
}

// IsValidPin
Test(C4514, isValidPin)
{
    C4514 c4514;
    // Valid pins : 1 - 24

    cr_assert_throw(c4514.compute(0), nts::InvalidArgument)
    cr_assert_no_throw(c4514.compute(1))
    cr_assert_no_throw(c4514.compute(2))
    cr_assert_no_throw(c4514.compute(3))
    cr_assert_no_throw(c4514.compute(4))
    cr_assert_no_throw(c4514.compute(5))
    cr_assert_no_throw(c4514.compute(6))
    cr_assert_no_throw(c4514.compute(7))
    cr_assert_no_throw(c4514.compute(8))
    cr_assert_no_throw(c4514.compute(9))
    cr_assert_no_throw(c4514.compute(10))
    cr_assert_no_throw(c4514.compute(11))
    cr_assert_no_throw(c4514.compute(12))
    cr_assert_no_throw(c4514.compute(13))
    cr_assert_no_throw(c4514.compute(14))
    cr_assert_no_throw(c4514.compute(15))
    cr_assert_no_throw(c4514.compute(16))
    cr_assert_no_throw(c4514.compute(17))
    cr_assert_no_throw(c4514.compute(18))
    cr_assert_no_throw(c4514.compute(19))
    cr_assert_no_throw(c4514.compute(20))
    cr_assert_no_throw(c4514.compute(21))
    cr_assert_no_throw(c4514.compute(22))
    cr_assert_no_throw(c4514.compute(23))
    cr_assert_no_throw(c4514.compute(24))
    cr_assert_throw(c4514.compute(25), nts::InvalidArgument)
}

// ComputeOutput
Test(C4514, computeInputs)
{
    C4514 c4514;
    Input in_0;
    Input in_1;
    Input in_2;
    Input in_3;
    Input inhibit;
    Input strobe;

    c4514.setLink(2, in_0, 1);
    in_0.setLink(1, c4514, 2);

    c4514.setLink(3, in_1, 1);
    in_1.setLink(1, c4514, 3);

    c4514.setLink(21, in_2, 1);
    in_2.setLink(1, c4514, 21);

    c4514.setLink(22, in_3, 1);
    in_3.setLink(1, c4514, 22);

    c4514.setLink(23, inhibit, 1);
    inhibit.setLink(1, c4514, 23);

    c4514.setLink(1, strobe, 1);
    strobe.setLink(1, c4514, 1);

    in_0.setState(nts::Tristate::True);
    in_1.setState(nts::Tristate::False);
    in_2.setState(nts::Tristate::True);
    in_3.setState(nts::Tristate::False);
    inhibit.setState(nts::Tristate::False);
    strobe.setState(nts::Tristate::True);

    in_0.simulate(1);
    in_1.simulate(1);
    in_2.simulate(1);
    in_3.simulate(1);
    inhibit.simulate(1);
    strobe.simulate(1);

    c4514.simulate(1);
    c4514.simulate(1);

    std::vector<size_t> output_pins = {11, 9, 10, 8, 7, 6, 5, 4, 18, 17, 20, 19, 14, 13, 16, 15};
    size_t expected_active_output = 5;

    for (size_t i = 0; i < output_pins.size(); ++i) {
        size_t pin = output_pins[i];
        if (i == expected_active_output) {
            cr_assert_eq(c4514.compute(pin), nts::Tristate::True, "Output %zu should be HIGH", pin);
        } else {
            cr_assert_eq(c4514.compute(pin), nts::Tristate::False, "Output %zu should be LOW", pin);
        }
    }
}

Test(C4514, computeInputsInhibitTrue)
{
    C4514 c4514;
    Input in_0;
    Input in_1;
    Input in_2;
    Input in_3;
    Input inhibit;
    Input strobe;

    c4514.setLink(2, in_0, 1);
    in_0.setLink(1, c4514, 2);

    c4514.setLink(3, in_1, 1);
    in_1.setLink(1, c4514, 3);

    c4514.setLink(21, in_2, 1);
    in_2.setLink(1, c4514, 21);

    c4514.setLink(22, in_3, 1);
    in_3.setLink(1, c4514, 22);

    c4514.setLink(23, inhibit, 1);
    inhibit.setLink(1, c4514, 23);

    c4514.setLink(1, strobe, 1);
    strobe.setLink(1, c4514, 1);

    in_0.setState(nts::Tristate::True);
    in_1.setState(nts::Tristate::False);
    in_2.setState(nts::Tristate::True);
    in_3.setState(nts::Tristate::False);
    inhibit.setState(nts::Tristate::True);
    strobe.setState(nts::Tristate::True);

    in_0.simulate(1);
    in_1.simulate(1);
    in_2.simulate(1);
    in_3.simulate(1);
    inhibit.simulate(1);
    strobe.simulate(1);

    c4514.simulate(1);

    std::vector<size_t> output_pins = {11, 9, 10, 8, 7, 6, 5, 4, 18, 17, 20, 19, 14, 13, 16, 15};

    for (size_t i = 0; i < output_pins.size(); ++i) {
        size_t pin = output_pins[i];
        cr_assert_eq(c4514.compute(pin), nts::Tristate::False, "Output %zu should be LOW", pin);
    }
}

Test(C4514, computeInputsInhibitUndefined)
{
    C4514 c4514;
    Input in_0;
    Input in_1;
    Input in_2;
    Input in_3;
    Input inhibit;
    Input strobe;

    c4514.setLink(2, in_0, 1);
    in_0.setLink(1, c4514, 2);

    c4514.setLink(3, in_1, 1);
    in_1.setLink(1, c4514, 3);

    c4514.setLink(21, in_2, 1);
    in_2.setLink(1, c4514, 21);

    c4514.setLink(22, in_3, 1);
    in_3.setLink(1, c4514, 22);

    c4514.setLink(23, inhibit, 1);
    inhibit.setLink(1, c4514, 23);

    c4514.setLink(1, strobe, 1);
    strobe.setLink(1, c4514, 1);

    in_0.setState(nts::Tristate::True);
    in_1.setState(nts::Tristate::False);
    in_2.setState(nts::Tristate::True);
    in_3.setState(nts::Tristate::False);
    inhibit.setState(nts::Tristate::Undefined);
    strobe.setState(nts::Tristate::Undefined);

    in_0.simulate(1);
    in_1.simulate(1);
    in_2.simulate(1);
    in_3.simulate(1);
    inhibit.simulate(1);
    strobe.simulate(1);

    c4514.simulate(1);

    std::vector<size_t> output_pins = {11, 9, 10, 8, 7, 6, 5, 4, 18, 17, 20, 19, 14, 13, 16, 15};

    for (size_t i = 0; i < output_pins.size(); ++i) {
        size_t pin = output_pins[i];
        cr_assert_eq(c4514.compute(pin), nts::Tristate::Undefined, "Output %zu should be Undefined", pin);
    }
}

Test(C4514, computeInputsSrobeFalse)
{
    C4514 c4514;
    Input in_0;
    Input in_1;
    Input in_2;
    Input in_3;
    Input inhibit;
    Input strobe;

    c4514.setLink(2, in_0, 1);
    in_0.setLink(1, c4514, 2);

    c4514.setLink(3, in_1, 1);
    in_1.setLink(1, c4514, 3);

    c4514.setLink(21, in_2, 1);
    in_2.setLink(1, c4514, 21);

    c4514.setLink(22, in_3, 1);
    in_3.setLink(1, c4514, 22);

    c4514.setLink(23, inhibit, 1);
    inhibit.setLink(1, c4514, 23);

    c4514.setLink(1, strobe, 1);
    strobe.setLink(1, c4514, 1);

    in_0.setState(nts::Tristate::Undefined);
    in_1.setState(nts::Tristate::Undefined);
    in_2.setState(nts::Tristate::Undefined);
    in_3.setState(nts::Tristate::Undefined);
    inhibit.setState(nts::Tristate::False);
    strobe.setState(nts::Tristate::False);

    in_0.simulate(1);
    in_1.simulate(1);
    in_2.simulate(1);
    in_3.simulate(1);
    inhibit.simulate(1);
    strobe.simulate(1);

    c4514.simulate(1);

    std::vector<size_t> output_pins = {11, 9, 10, 8, 7, 6, 5, 4, 18, 17, 20, 19, 14, 13, 16, 15};

    for (size_t i = 0; i < output_pins.size(); ++i) {
        size_t pin = output_pins[i];
        cr_assert_eq(c4514.compute(pin), nts::Tristate::Undefined, "Output %zu should be Undefined", pin);
    }
}

Test(C4514, computeInputsSimulateandStrobeAfter)
{
    C4514 c4514;
    Input in_0;
    Input in_1;
    Input in_2;
    Input in_3;
    Input inhibit;
    Input strobe;

    c4514.setLink(2, in_0, 1);
    in_0.setLink(1, c4514, 2);

    c4514.setLink(3, in_1, 1);
    in_1.setLink(1, c4514, 3);

    c4514.setLink(21, in_2, 1);
    in_2.setLink(1, c4514, 21);

    c4514.setLink(22, in_3, 1);
    in_3.setLink(1, c4514, 22);

    c4514.setLink(23, inhibit, 1);
    inhibit.setLink(1, c4514, 23);

    c4514.setLink(1, strobe, 1);
    strobe.setLink(1, c4514, 1);

    in_0.setState(nts::Tristate::False);
    in_1.setState(nts::Tristate::False);
    in_2.setState(nts::Tristate::False);
    in_3.setState(nts::Tristate::False);

    in_0.simulate(1);
    in_1.simulate(1);
    in_2.simulate(1);
    in_3.simulate(1);

    c4514.simulate(1);

    inhibit.setState(nts::Tristate::False);
    strobe.setState(nts::Tristate::False);
    inhibit.simulate(1);
    strobe.simulate(1);

    c4514.simulate(2);
    std::vector<size_t> output_pins = {11, 9, 10, 8, 7, 6, 5, 4, 18, 17, 20, 19, 14, 13, 16, 15};

    for (size_t i = 0; i < output_pins.size(); ++i) {
        size_t pin = output_pins[i];
        cr_assert_eq(c4514.compute(pin), nts::Tristate::Undefined, "Output %zu should be Undefined", pin);
    }
}

Test(C4514, computeInputsAllFalse)
{
    C4514 c4514;
    Input in_0;
    Input in_1;
    Input in_2;
    Input in_3;
    Input inhibit;
    Input strobe;

    c4514.setLink(2, in_0, 1);
    in_0.setLink(1, c4514, 2);

    c4514.setLink(3, in_1, 1);
    in_1.setLink(1, c4514, 3);

    c4514.setLink(21, in_2, 1);
    in_2.setLink(1, c4514, 21);

    c4514.setLink(22, in_3, 1);
    in_3.setLink(1, c4514, 22);

    c4514.setLink(23, inhibit, 1);
    inhibit.setLink(1, c4514, 23);

    c4514.setLink(1, strobe, 1);
    strobe.setLink(1, c4514, 1);

    in_0.setState(nts::Tristate::False);
    in_1.setState(nts::Tristate::False);
    in_2.setState(nts::Tristate::False);
    in_3.setState(nts::Tristate::False);
    inhibit.setState(nts::Tristate::False);
    strobe.setState(nts::Tristate::False);

    in_0.simulate(1);
    in_1.simulate(1);
    in_2.simulate(1);
    in_3.simulate(1);
    inhibit.simulate(1);
    strobe.simulate(1);

    c4514.simulate(2);
    std::vector<size_t> output_pins = {11, 9, 10, 8, 7, 6, 5, 4, 18, 17, 20, 19, 14, 13, 16, 15};

    for (size_t i = 0; i < output_pins.size(); ++i) {
        size_t pin = output_pins[i];
        cr_assert_eq(c4514.compute(pin), nts::Tristate::Undefined, "Output %zu should be Undefined", pin);
    }
}
