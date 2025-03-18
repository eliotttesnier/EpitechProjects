/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** tests_4512
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>

#include "AComponent.hpp"
#include "4512.hpp"
#include "Input.hpp"
#include "Error.hpp"

// Constructor
Test(C4512, constructor)
{
    C4512 c4512;
}

// Destructor
Test(C4512, destructor)
{
    C4512 c4512;
}

// IsValidPin
Test(C4512, isValidPin)
{
    C4512 c4512;
    // Valid pins : 1 - 16

    cr_assert_throw(c4512.compute(0), nts::InvalidArgument)
    cr_assert_no_throw(c4512.compute(1))
    cr_assert_no_throw(c4512.compute(2))
    cr_assert_no_throw(c4512.compute(3))
    cr_assert_no_throw(c4512.compute(4))
    cr_assert_no_throw(c4512.compute(5))
    cr_assert_no_throw(c4512.compute(6))
    cr_assert_no_throw(c4512.compute(7))
    cr_assert_no_throw(c4512.compute(8))
    cr_assert_no_throw(c4512.compute(9))
    cr_assert_no_throw(c4512.compute(10))
    cr_assert_no_throw(c4512.compute(11))
    cr_assert_no_throw(c4512.compute(12))
    cr_assert_no_throw(c4512.compute(13))
    cr_assert_no_throw(c4512.compute(14))
    cr_assert_no_throw(c4512.compute(15))
    cr_assert_no_throw(c4512.compute(16))
    cr_assert_throw(c4512.compute(17), nts::InvalidArgument)
}

// ComputeOutput
Test(C4512, computeOeTrue)
{
    C4512 c4512;
    Input enable;
    Input inhibit;
    Input a;
    Input b;
    Input c;
    Input in_0;
    Input in_1;
    Input in_2;
    Input in_3;
    Input in_4;
    Input in_5;
    Input in_6;
    Input in_7;

    c4512.setLink(15, enable, 1);
    enable.setLink(1, c4512, 15);

    c4512.setLink(10, inhibit, 1);
    inhibit.setLink(1, c4512, 10);

    c4512.setLink(11, a, 1);
    a.setLink(1, c4512, 11);

    c4512.setLink(12, b, 1);
    b.setLink(1, c4512, 12);

    c4512.setLink(13, c, 1);
    c.setLink(1, c4512, 13);

    c4512.setLink(1, in_0, 1);
    in_0.setLink(1, c4512, 1);

    c4512.setLink(2, in_1, 1);
    in_1.setLink(1, c4512, 2);

    c4512.setLink(3, in_2, 1);
    in_2.setLink(1, c4512, 3);

    c4512.setLink(4, in_3, 1);
    in_3.setLink(1, c4512, 4);

    c4512.setLink(5, in_4, 1);
    in_4.setLink(1, c4512, 5);

    c4512.setLink(6, in_5, 1);
    in_5.setLink(1, c4512, 6);

    c4512.setLink(7, in_6, 1);
    in_6.setLink(1, c4512, 7);

    c4512.setLink(9, in_7, 1);
    in_7.setLink(1, c4512, 9);

    enable.setState(nts::Tristate::True);
    enable.simulate(1);

    cr_assert_eq(c4512.compute(14), nts::Tristate::Undefined);
}

Test(C4512, computeInhibitTrue)
{
    C4512 c4512;
    Input enable;
    Input inhibit;
    Input a;
    Input b;
    Input c;
    Input in_0;
    Input in_1;
    Input in_2;
    Input in_3;
    Input in_4;
    Input in_5;
    Input in_6;
    Input in_7;

    c4512.setLink(15, enable, 1);
    enable.setLink(1, c4512, 15);

    c4512.setLink(10, inhibit, 1);
    inhibit.setLink(1, c4512, 10);

    c4512.setLink(11, a, 1);
    a.setLink(1, c4512, 11);

    c4512.setLink(12, b, 1);
    b.setLink(1, c4512, 12);

    c4512.setLink(13, c, 1);
    c.setLink(1, c4512, 13);

    c4512.setLink(1, in_0, 1);
    in_0.setLink(1, c4512, 1);

    c4512.setLink(2, in_1, 1);
    in_1.setLink(1, c4512, 2);

    c4512.setLink(3, in_2, 1);
    in_2.setLink(1, c4512, 3);

    c4512.setLink(4, in_3, 1);
    in_3.setLink(1, c4512, 4);

    c4512.setLink(5, in_4, 1);
    in_4.setLink(1, c4512, 5);

    c4512.setLink(6, in_5, 1);
    in_5.setLink(1, c4512, 6);

    c4512.setLink(7, in_6, 1);
    in_6.setLink(1, c4512, 7);

    c4512.setLink(9, in_7, 1);
    in_7.setLink(1, c4512, 9);

    inhibit.setState(nts::Tristate::True);
    inhibit.simulate(1);

    cr_assert_eq(c4512.compute(14), nts::Tristate::False);
}

Test(C4512, computeUndefined)
{
    C4512 c4512;
    Input enable;
    Input inhibit;
    Input a;
    Input b;
    Input c;
    Input in_0;
    Input in_1;
    Input in_2;
    Input in_3;
    Input in_4;
    Input in_5;
    Input in_6;
    Input in_7;

    c4512.setLink(15, enable, 1);
    enable.setLink(1, c4512, 15);

    c4512.setLink(10, inhibit, 1);
    inhibit.setLink(1, c4512, 10);

    c4512.setLink(11, a, 1);
    a.setLink(1, c4512, 11);

    c4512.setLink(12, b, 1);
    b.setLink(1, c4512, 12);

    c4512.setLink(13, c, 1);
    c.setLink(1, c4512, 13);

    c4512.setLink(1, in_0, 1);
    in_0.setLink(1, c4512, 1);

    c4512.setLink(2, in_1, 1);
    in_1.setLink(1, c4512, 2);

    c4512.setLink(3, in_2, 1);
    in_2.setLink(1, c4512, 3);

    c4512.setLink(4, in_3, 1);
    in_3.setLink(1, c4512, 4);

    c4512.setLink(5, in_4, 1);
    in_4.setLink(1, c4512, 5);

    c4512.setLink(6, in_5, 1);
    in_5.setLink(1, c4512, 6);

    c4512.setLink(7, in_6, 1);
    in_6.setLink(1, c4512, 7);

    c4512.setLink(9, in_7, 1);
    in_7.setLink(1, c4512, 9);

    enable.setState(nts::Tristate::False);
    enable.simulate(1);
    inhibit.setState(nts::Tristate::False);
    inhibit.simulate(1);

    cr_assert_eq(c4512.compute(14), nts::Tristate::Undefined);
}

Test(C4512, computeZero)
{
    C4512 c4512;
    Input enable;
    Input inhibit;
    Input a;
    Input b;
    Input c;
    Input in_0;
    Input in_1;
    Input in_2;
    Input in_3;
    Input in_4;
    Input in_5;
    Input in_6;
    Input in_7;

    c4512.setLink(15, enable, 1);
    enable.setLink(1, c4512, 15);

    c4512.setLink(10, inhibit, 1);
    inhibit.setLink(1, c4512, 10);

    c4512.setLink(11, a, 1);
    a.setLink(1, c4512, 11);

    c4512.setLink(12, b, 1);
    b.setLink(1, c4512, 12);

    c4512.setLink(13, c, 1);
    c.setLink(1, c4512, 13);

    c4512.setLink(1, in_0, 1);
    in_0.setLink(1, c4512, 1);

    c4512.setLink(2, in_1, 1);
    in_1.setLink(1, c4512, 2);

    c4512.setLink(3, in_2, 1);
    in_2.setLink(1, c4512, 3);

    c4512.setLink(4, in_3, 1);
    in_3.setLink(1, c4512, 4);

    c4512.setLink(5, in_4, 1);
    in_4.setLink(1, c4512, 5);

    c4512.setLink(6, in_5, 1);
    in_5.setLink(1, c4512, 6);

    c4512.setLink(7, in_6, 1);
    in_6.setLink(1, c4512, 7);

    c4512.setLink(9, in_7, 1);
    in_7.setLink(1, c4512, 9);

    enable.setState(nts::Tristate::False);
    enable.simulate(1);
    inhibit.setState(nts::Tristate::False);
    inhibit.simulate(1);
    a.setState(nts::Tristate::False);
    a.simulate(1);
    b.setState(nts::Tristate::False);
    b.simulate(1);
    c.setState(nts::Tristate::False);
    c.simulate(1);

    cr_assert_eq(c4512.compute(14), nts::Tristate::Undefined);
}

Test(C4512, computeOne)
{
    C4512 c4512;
    Input enable;
    Input inhibit;
    Input a;
    Input b;
    Input c;
    Input in_0;
    Input in_1;
    Input in_2;
    Input in_3;
    Input in_4;
    Input in_5;
    Input in_6;
    Input in_7;

    c4512.setLink(15, enable, 1);
    enable.setLink(1, c4512, 15);

    c4512.setLink(10, inhibit, 1);
    inhibit.setLink(1, c4512, 10);

    c4512.setLink(11, a, 1);
    a.setLink(1, c4512, 11);

    c4512.setLink(12, b, 1);
    b.setLink(1, c4512, 12);

    c4512.setLink(13, c, 1);
    c.setLink(1, c4512, 13);

    c4512.setLink(1, in_0, 1);
    in_0.setLink(1, c4512, 1);

    c4512.setLink(2, in_1, 1);
    in_1.setLink(1, c4512, 2);

    c4512.setLink(3, in_2, 1);
    in_2.setLink(1, c4512, 3);

    c4512.setLink(4, in_3, 1);
    in_3.setLink(1, c4512, 4);

    c4512.setLink(5, in_4, 1);
    in_4.setLink(1, c4512, 5);

    c4512.setLink(6, in_5, 1);
    in_5.setLink(1, c4512, 6);

    c4512.setLink(7, in_6, 1);
    in_6.setLink(1, c4512, 7);

    c4512.setLink(9, in_7, 1);
    in_7.setLink(1, c4512, 9);

    enable.setState(nts::Tristate::False);
    enable.simulate(1);
    inhibit.setState(nts::Tristate::False);
    inhibit.simulate(1);
    a.setState(nts::Tristate::True);
    a.simulate(1);
    b.setState(nts::Tristate::False);
    b.simulate(1);
    c.setState(nts::Tristate::False);
    c.simulate(1);

    cr_assert_eq(c4512.compute(14), nts::Tristate::Undefined);
}

Test(C4512, computeTwo)
{
    C4512 c4512;
    Input enable;
    Input inhibit;
    Input a;
    Input b;
    Input c;
    Input in_0;
    Input in_1;
    Input in_2;
    Input in_3;
    Input in_4;
    Input in_5;
    Input in_6;
    Input in_7;

    c4512.setLink(15, enable, 1);
    enable.setLink(1, c4512, 15);

    c4512.setLink(10, inhibit, 1);
    inhibit.setLink(1, c4512, 10);

    c4512.setLink(11, a, 1);
    a.setLink(1, c4512, 11);

    c4512.setLink(12, b, 1);
    b.setLink(1, c4512, 12);

    c4512.setLink(13, c, 1);
    c.setLink(1, c4512, 13);

    c4512.setLink(1, in_0, 1);
    in_0.setLink(1, c4512, 1);

    c4512.setLink(2, in_1, 1);
    in_1.setLink(1, c4512, 2);

    c4512.setLink(3, in_2, 1);
    in_2.setLink(1, c4512, 3);

    c4512.setLink(4, in_3, 1);
    in_3.setLink(1, c4512, 4);

    c4512.setLink(5, in_4, 1);
    in_4.setLink(1, c4512, 5);

    c4512.setLink(6, in_5, 1);
    in_5.setLink(1, c4512, 6);

    c4512.setLink(7, in_6, 1);
    in_6.setLink(1, c4512, 7);

    c4512.setLink(9, in_7, 1);
    in_7.setLink(1, c4512, 9);

    enable.setState(nts::Tristate::False);
    enable.simulate(1);
    inhibit.setState(nts::Tristate::False);
    inhibit.simulate(1);
    a.setState(nts::Tristate::False);
    a.simulate(1);
    b.setState(nts::Tristate::True);
    b.simulate(1);
    c.setState(nts::Tristate::False);
    c.simulate(1);

    cr_assert_eq(c4512.compute(14), nts::Tristate::Undefined);
}

Test(C4512, computeThree)
{
    C4512 c4512;
    Input enable;
    Input inhibit;
    Input a;
    Input b;
    Input c;
    Input in_0;
    Input in_1;
    Input in_2;
    Input in_3;
    Input in_4;
    Input in_5;
    Input in_6;
    Input in_7;

    c4512.setLink(15, enable, 1);
    enable.setLink(1, c4512, 15);

    c4512.setLink(10, inhibit, 1);
    inhibit.setLink(1, c4512, 10);

    c4512.setLink(11, a, 1);
    a.setLink(1, c4512, 11);

    c4512.setLink(12, b, 1);
    b.setLink(1, c4512, 12);

    c4512.setLink(13, c, 1);
    c.setLink(1, c4512, 13);

    c4512.setLink(1, in_0, 1);
    in_0.setLink(1, c4512, 1);

    c4512.setLink(2, in_1, 1);
    in_1.setLink(1, c4512, 2);

    c4512.setLink(3, in_2, 1);
    in_2.setLink(1, c4512, 3);

    c4512.setLink(4, in_3, 1);
    in_3.setLink(1, c4512, 4);

    c4512.setLink(5, in_4, 1);
    in_4.setLink(1, c4512, 5);

    c4512.setLink(6, in_5, 1);
    in_5.setLink(1, c4512, 6);

    c4512.setLink(7, in_6, 1);
    in_6.setLink(1, c4512, 7);

    c4512.setLink(9, in_7, 1);
    in_7.setLink(1, c4512, 9);

    enable.setState(nts::Tristate::False);
    enable.simulate(1);
    inhibit.setState(nts::Tristate::False);
    inhibit.simulate(1);
    a.setState(nts::Tristate::True);
    a.simulate(1);
    b.setState(nts::Tristate::True);
    b.simulate(1);
    c.setState(nts::Tristate::False);
    c.simulate(1);

    cr_assert_eq(c4512.compute(14), nts::Tristate::Undefined);
}

Test(C4512, computeFour)
{
    C4512 c4512;
    Input enable;
    Input inhibit;
    Input a;
    Input b;
    Input c;
    Input in_0;
    Input in_1;
    Input in_2;
    Input in_3;
    Input in_4;
    Input in_5;
    Input in_6;
    Input in_7;

    c4512.setLink(15, enable, 1);
    enable.setLink(1, c4512, 15);

    c4512.setLink(10, inhibit, 1);
    inhibit.setLink(1, c4512, 10);

    c4512.setLink(11, a, 1);
    a.setLink(1, c4512, 11);

    c4512.setLink(12, b, 1);
    b.setLink(1, c4512, 12);

    c4512.setLink(13, c, 1);
    c.setLink(1, c4512, 13);

    c4512.setLink(1, in_0, 1);
    in_0.setLink(1, c4512, 1);

    c4512.setLink(2, in_1, 1);
    in_1.setLink(1, c4512, 2);

    c4512.setLink(3, in_2, 1);
    in_2.setLink(1, c4512, 3);

    c4512.setLink(4, in_3, 1);
    in_3.setLink(1, c4512, 4);

    c4512.setLink(5, in_4, 1);
    in_4.setLink(1, c4512, 5);

    c4512.setLink(6, in_5, 1);
    in_5.setLink(1, c4512, 6);

    c4512.setLink(7, in_6, 1);
    in_6.setLink(1, c4512, 7);

    c4512.setLink(9, in_7, 1);
    in_7.setLink(1, c4512, 9);

    enable.setState(nts::Tristate::False);
    enable.simulate(1);
    inhibit.setState(nts::Tristate::False);
    inhibit.simulate(1);
    a.setState(nts::Tristate::False);
    a.simulate(1);
    b.setState(nts::Tristate::False);
    b.simulate(1);
    c.setState(nts::Tristate::True);
    c.simulate(1);

    cr_assert_eq(c4512.compute(14), nts::Tristate::Undefined);
}

Test(C4512, computeFive)
{
    C4512 c4512;
    Input enable;
    Input inhibit;
    Input a;
    Input b;
    Input c;
    Input in_0;
    Input in_1;
    Input in_2;
    Input in_3;
    Input in_4;
    Input in_5;
    Input in_6;
    Input in_7;

    c4512.setLink(15, enable, 1);
    enable.setLink(1, c4512, 15);

    c4512.setLink(10, inhibit, 1);
    inhibit.setLink(1, c4512, 10);

    c4512.setLink(11, a, 1);
    a.setLink(1, c4512, 11);

    c4512.setLink(12, b, 1);
    b.setLink(1, c4512, 12);

    c4512.setLink(13, c, 1);
    c.setLink(1, c4512, 13);

    c4512.setLink(1, in_0, 1);
    in_0.setLink(1, c4512, 1);

    c4512.setLink(2, in_1, 1);
    in_1.setLink(1, c4512, 2);

    c4512.setLink(3, in_2, 1);
    in_2.setLink(1, c4512, 3);

    c4512.setLink(4, in_3, 1);
    in_3.setLink(1, c4512, 4);

    c4512.setLink(5, in_4, 1);
    in_4.setLink(1, c4512, 5);

    c4512.setLink(6, in_5, 1);
    in_5.setLink(1, c4512, 6);

    c4512.setLink(7, in_6, 1);
    in_6.setLink(1, c4512, 7);

    c4512.setLink(9, in_7, 1);
    in_7.setLink(1, c4512, 9);

    enable.setState(nts::Tristate::False);
    enable.simulate(1);
    inhibit.setState(nts::Tristate::False);
    inhibit.simulate(1);
    a.setState(nts::Tristate::True);
    a.simulate(1);
    b.setState(nts::Tristate::False);
    b.simulate(1);
    c.setState(nts::Tristate::True);
    c.simulate(1);

    cr_assert_eq(c4512.compute(14), nts::Tristate::Undefined);
}

Test(C4512, computeSix)
{
    C4512 c4512;
    Input enable;
    Input inhibit;
    Input a;
    Input b;
    Input c;
    Input in_0;
    Input in_1;
    Input in_2;
    Input in_3;
    Input in_4;
    Input in_5;
    Input in_6;
    Input in_7;

    c4512.setLink(15, enable, 1);
    enable.setLink(1, c4512, 15);

    c4512.setLink(10, inhibit, 1);
    inhibit.setLink(1, c4512, 10);

    c4512.setLink(11, a, 1);
    a.setLink(1, c4512, 11);

    c4512.setLink(12, b, 1);
    b.setLink(1, c4512, 12);

    c4512.setLink(13, c, 1);
    c.setLink(1, c4512, 13);

    c4512.setLink(1, in_0, 1);
    in_0.setLink(1, c4512, 1);

    c4512.setLink(2, in_1, 1);
    in_1.setLink(1, c4512, 2);

    c4512.setLink(3, in_2, 1);
    in_2.setLink(1, c4512, 3);

    c4512.setLink(4, in_3, 1);
    in_3.setLink(1, c4512, 4);

    c4512.setLink(5, in_4, 1);
    in_4.setLink(1, c4512, 5);

    c4512.setLink(6, in_5, 1);
    in_5.setLink(1, c4512, 6);

    c4512.setLink(7, in_6, 1);
    in_6.setLink(1, c4512, 7);

    c4512.setLink(9, in_7, 1);
    in_7.setLink(1, c4512, 9);

    enable.setState(nts::Tristate::False);
    enable.simulate(1);
    inhibit.setState(nts::Tristate::False);
    inhibit.simulate(1);
    a.setState(nts::Tristate::False);
    a.simulate(1);
    b.setState(nts::Tristate::True);
    b.simulate(1);
    c.setState(nts::Tristate::True);
    c.simulate(1);

    cr_assert_eq(c4512.compute(14), nts::Tristate::Undefined);
}

Test(C4512, computeSeven)
{
    C4512 c4512;
    Input enable;
    Input inhibit;
    Input a;
    Input b;
    Input c;
    Input in_0;
    Input in_1;
    Input in_2;
    Input in_3;
    Input in_4;
    Input in_5;
    Input in_6;
    Input in_7;

    c4512.setLink(15, enable, 1);
    enable.setLink(1, c4512, 15);

    c4512.setLink(10, inhibit, 1);
    inhibit.setLink(1, c4512, 10);

    c4512.setLink(11, a, 1);
    a.setLink(1, c4512, 11);

    c4512.setLink(12, b, 1);
    b.setLink(1, c4512, 12);

    c4512.setLink(13, c, 1);
    c.setLink(1, c4512, 13);

    c4512.setLink(1, in_0, 1);
    in_0.setLink(1, c4512, 1);

    c4512.setLink(2, in_1, 1);
    in_1.setLink(1, c4512, 2);

    c4512.setLink(3, in_2, 1);
    in_2.setLink(1, c4512, 3);

    c4512.setLink(4, in_3, 1);
    in_3.setLink(1, c4512, 4);

    c4512.setLink(5, in_4, 1);
    in_4.setLink(1, c4512, 5);

    c4512.setLink(6, in_5, 1);
    in_5.setLink(1, c4512, 6);

    c4512.setLink(7, in_6, 1);
    in_6.setLink(1, c4512, 7);

    c4512.setLink(9, in_7, 1);
    in_7.setLink(1, c4512, 9);

    enable.setState(nts::Tristate::False);
    enable.simulate(1);
    inhibit.setState(nts::Tristate::False);
    inhibit.simulate(1);
    a.setState(nts::Tristate::True);
    a.simulate(1);
    b.setState(nts::Tristate::True);
    b.simulate(1);
    c.setState(nts::Tristate::True);
    c.simulate(1);

    cr_assert_eq(c4512.compute(14), nts::Tristate::Undefined);
}
