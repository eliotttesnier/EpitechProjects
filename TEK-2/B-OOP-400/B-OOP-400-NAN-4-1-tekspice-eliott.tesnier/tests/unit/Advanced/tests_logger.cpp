/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** tests_4001
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>

#include "AComponent.hpp"
#include "Logger.hpp"
#include "Input.hpp"
#include "Clock.hpp"
#include "Error.hpp"

// Constructor
Test(Logger, constructor)
{
    Logger logger;
}

// Destructor
Test(Logger, destructor)
{
    Logger logger;
}

// IsValidPin
Test(Logger, isValidPin)
{
    Logger logger;
    // Valid pins : 1 - 10

    cr_assert_throw(logger.compute(0), nts::InvalidArgument)
    cr_assert_no_throw(logger.compute(1))
    cr_assert_no_throw(logger.compute(2))
    cr_assert_no_throw(logger.compute(3))
    cr_assert_no_throw(logger.compute(4))
    cr_assert_no_throw(logger.compute(5))
    cr_assert_no_throw(logger.compute(6))
    cr_assert_no_throw(logger.compute(7))
    cr_assert_no_throw(logger.compute(8))
    cr_assert_no_throw(logger.compute(9))
    cr_assert_no_throw(logger.compute(10))
    cr_assert_throw(logger.compute(11), nts::InvalidArgument)
}

// ComputeOutput
Test(Logger, computeOutputNoLinks)
{
    Logger logger;

    cr_assert_eq(logger.compute(1), nts::Tristate::Undefined);
}

Test(Logger, computeOutputInput)
{
    Logger logger;

    Input input;

    logger.setLink(1, input, 1);

    input.setState(nts::Tristate::True);
    input.simulate(1);

    cr_assert_eq(logger.compute(1), nts::Tristate::True);
}

Test(Logger, SimulateUndefined)
{
    Logger logger;
    Input in_001;
    Input in_002;
    Input in_004;
    Input in_008;
    Input in_016;
    Input in_032;
    Input in_064;
    Input in_128;
    Clock clock;
    Input inhibit;

    logger.setLink(1, in_001, 1);
    in_001.setLink(1, logger, 1);

    logger.setLink(2, in_002, 1);
    in_002.setLink(1, logger, 2);

    logger.setLink(3, in_004, 1);
    in_004.setLink(1, logger, 3);

    logger.setLink(4, in_008, 1);
    in_008.setLink(1, logger, 4);

    logger.setLink(5, in_016, 1);
    in_016.setLink(1, logger, 5);

    logger.setLink(6, in_032, 1);
    in_032.setLink(1, logger, 6);

    logger.setLink(7, in_064, 1);
    in_064.setLink(1, logger, 7);

    logger.setLink(8, in_128, 1);
    in_128.setLink(1, logger, 8);

    logger.setLink(9, clock, 1);
    clock.setLink(1, logger, 9);

    logger.setLink(10, inhibit, 1);
    inhibit.setLink(1, logger, 10);

    cr_assert_no_throw(logger.simulate(1));
}

Test(Logger, SimulateSameTick)
{
    Logger logger;
    Input in_001;
    Input in_002;
    Input in_004;
    Input in_008;
    Input in_016;
    Input in_032;
    Input in_064;
    Input in_128;
    Clock clock;
    Input inhibit;

    logger.setLink(1, in_001, 1);
    in_001.setLink(1, logger, 1);

    logger.setLink(2, in_002, 1);
    in_002.setLink(1, logger, 2);

    logger.setLink(3, in_004, 1);
    in_004.setLink(1, logger, 3);

    logger.setLink(4, in_008, 1);
    in_008.setLink(1, logger, 4);

    logger.setLink(5, in_016, 1);
    in_016.setLink(1, logger, 5);

    logger.setLink(6, in_032, 1);
    in_032.setLink(1, logger, 6);

    logger.setLink(7, in_064, 1);
    in_064.setLink(1, logger, 7);

    logger.setLink(8, in_128, 1);
    in_128.setLink(1, logger, 8);

    logger.setLink(9, clock, 1);
    clock.setLink(1, logger, 9);

    logger.setLink(10, inhibit, 1);
    inhibit.setLink(1, logger, 10);

    cr_assert_no_throw(logger.simulate(1));
    cr_assert_no_throw(logger.simulate(1));
}

Test(Logger, SimulateRisingEdge)
{
    Logger logger;
    Input in_001;
    Input in_002;
    Input in_004;
    Input in_008;
    Input in_016;
    Input in_032;
    Input in_064;
    Input in_128;
    Clock clock;
    Input inhibit;

    logger.setLink(1, in_001, 1);
    in_001.setLink(1, logger, 1);

    logger.setLink(2, in_002, 1);
    in_002.setLink(1, logger, 2);

    logger.setLink(3, in_004, 1);
    in_004.setLink(1, logger, 3);

    logger.setLink(4, in_008, 1);
    in_008.setLink(1, logger, 4);

    logger.setLink(5, in_016, 1);
    in_016.setLink(1, logger, 5);

    logger.setLink(6, in_032, 1);
    in_032.setLink(1, logger, 6);

    logger.setLink(7, in_064, 1);
    in_064.setLink(1, logger, 7);

    logger.setLink(8, in_128, 1);
    in_128.setLink(1, logger, 8);

    logger.setLink(9, clock, 1);
    clock.setLink(1, logger, 9);

    logger.setLink(10, inhibit, 1);
    inhibit.setLink(1, logger, 10);


    clock.setState(nts::Tristate::False);
    cr_assert_no_throw(logger.simulate(1));
    cr_assert_no_throw(logger.simulate(2));
}

Test(Logger, SimulateInhibit)
{
    Logger logger;
    Input in_001;
    Input in_002;
    Input in_004;
    Input in_008;
    Input in_016;
    Input in_032;
    Input in_064;
    Input in_128;
    Clock clock;
    Input inhibit;

    logger.setLink(1, in_001, 1);
    in_001.setLink(1, logger, 1);

    logger.setLink(2, in_002, 1);
    in_002.setLink(1, logger, 2);

    logger.setLink(3, in_004, 1);
    in_004.setLink(1, logger, 3);

    logger.setLink(4, in_008, 1);
    in_008.setLink(1, logger, 4);

    logger.setLink(5, in_016, 1);
    in_016.setLink(1, logger, 5);

    logger.setLink(6, in_032, 1);
    in_032.setLink(1, logger, 6);

    logger.setLink(7, in_064, 1);
    in_064.setLink(1, logger, 7);

    logger.setLink(8, in_128, 1);
    in_128.setLink(1, logger, 8);

    logger.setLink(9, clock, 1);
    clock.setLink(1, logger, 9);

    logger.setLink(10, inhibit, 1);
    inhibit.setLink(1, logger, 10);

    inhibit.setState(nts::Tristate::True);
    inhibit.simulate(1);
    cr_assert_no_throw(logger.simulate(2));
}

Test(Logger, SimulateAllTrue)
{
    Logger logger;
    Input in_001;
    Input in_002;
    Input in_004;
    Input in_008;
    Input in_016;
    Input in_032;
    Input in_064;
    Input in_128;
    Clock clock;
    Input inhibit;

    logger.setLink(1, in_001, 1);
    in_001.setLink(1, logger, 1);

    logger.setLink(2, in_002, 1);
    in_002.setLink(1, logger, 2);

    logger.setLink(3, in_004, 1);
    in_004.setLink(1, logger, 3);

    logger.setLink(4, in_008, 1);
    in_008.setLink(1, logger, 4);

    logger.setLink(5, in_016, 1);
    in_016.setLink(1, logger, 5);

    logger.setLink(6, in_032, 1);
    in_032.setLink(1, logger, 6);

    logger.setLink(7, in_064, 1);
    in_064.setLink(1, logger, 7);

    logger.setLink(8, in_128, 1);
    in_128.setLink(1, logger, 8);

    logger.setLink(9, clock, 1);
    clock.setLink(1, logger, 9);

    logger.setLink(10, inhibit, 1);
    inhibit.setLink(1, logger, 10);

    in_001.setState(nts::Tristate::True);
    in_001.simulate(1);
    in_002.setState(nts::Tristate::True);
    in_002.simulate(1);
    in_004.setState(nts::Tristate::True);
    in_004.simulate(1);
    in_008.setState(nts::Tristate::True);
    in_008.simulate(1);
    in_016.setState(nts::Tristate::True);
    in_016.simulate(1);
    in_032.setState(nts::Tristate::True);
    in_032.simulate(1);
    in_064.setState(nts::Tristate::True);
    in_064.simulate(1);
    in_128.setState(nts::Tristate::True);
    in_128.simulate(1);
    clock.setState(nts::Tristate::False);
    clock.simulate(1);
    inhibit.setState(nts::Tristate::False);
    inhibit.simulate(1);
    cr_assert_no_throw(logger.simulate(1));
    cr_assert_no_throw(logger.simulate(2));
}
