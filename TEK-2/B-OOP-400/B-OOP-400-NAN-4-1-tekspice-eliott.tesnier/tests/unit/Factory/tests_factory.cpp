/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** tests_factory
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>

#include "Factory.hpp"
#include "Error.hpp"

// Input
Test(Factory, Input, .init = cr_redirect_stdout)
{
    Factory factory;
    std::unique_ptr<nts::IComponent> input = factory.createComponent("input");

    cr_assert_not_null(input);
}

// Output
Test(Factory, Output, .init = cr_redirect_stdout)
{
    Factory factory;
    std::unique_ptr<nts::IComponent> output = factory.createComponent("output");

    cr_assert_not_null(output);
}

// True
Test(Factory, True, .init = cr_redirect_stdout)
{
    Factory factory;
    std::unique_ptr<nts::IComponent> trueComponent = factory.createComponent("true");

    cr_assert_not_null(trueComponent);
}

// False
Test(Factory, False, .init = cr_redirect_stdout)
{
    Factory factory;
    std::unique_ptr<nts::IComponent> falseComponent = factory.createComponent("false");

    cr_assert_not_null(falseComponent);
}

// Clock
Test(Factory, Clock, .init = cr_redirect_stdout)
{
    Factory factory;
    std::unique_ptr<nts::IComponent> clock = factory.createComponent("clock");

    cr_assert_not_null(clock);
}

// And
Test(Factory, And, .init = cr_redirect_stdout)
{
    Factory factory;
    std::unique_ptr<nts::IComponent> andComponent = factory.createComponent("and");

    cr_assert_not_null(andComponent);
}

// Or
Test(Factory, Or, .init = cr_redirect_stdout)
{
    Factory factory;
    std::unique_ptr<nts::IComponent> orComponent = factory.createComponent("or");

    cr_assert_not_null(orComponent);
}

// Xor
Test(Factory, Xor, .init = cr_redirect_stdout)
{
    Factory factory;
    std::unique_ptr<nts::IComponent> xorComponent = factory.createComponent("xor");

    cr_assert_not_null(xorComponent);
}

// Not
Test(Factory, Not, .init = cr_redirect_stdout)
{
    Factory factory;
    std::unique_ptr<nts::IComponent> notComponent = factory.createComponent("not");

    cr_assert_not_null(notComponent);
}

// 4001
Test(Factory, C4001, .init = cr_redirect_stdout)
{
    Factory factory;
    std::unique_ptr<nts::IComponent> c4001 = factory.createComponent("4001");

    cr_assert_not_null(c4001);
}

// 4011
Test(Factory, C4011, .init = cr_redirect_stdout)
{
    Factory factory;
    std::unique_ptr<nts::IComponent> c4011 = factory.createComponent("4011");

    cr_assert_not_null(c4011);
}

// 4030
Test(Factory, C4030, .init = cr_redirect_stdout)
{
    Factory factory;
    std::unique_ptr<nts::IComponent> c4030 = factory.createComponent("4030");

    cr_assert_not_null(c4030);
}

// 4069
Test(Factory, C4069, .init = cr_redirect_stdout)
{
    Factory factory;
    std::unique_ptr<nts::IComponent> c4069 = factory.createComponent("4069");

    cr_assert_not_null(c4069);
}

// 4071
Test(Factory, C4071, .init = cr_redirect_stdout)
{
    Factory factory;
    std::unique_ptr<nts::IComponent> c4071 = factory.createComponent("4071");

    cr_assert_not_null(c4071);
}

// 4081
Test(Factory, C4081, .init = cr_redirect_stdout)
{
    Factory factory;
    std::unique_ptr<nts::IComponent> c4081 = factory.createComponent("4081");

    cr_assert_not_null(c4081);
}

// 4008
Test(Factory, C4008, .init = cr_redirect_stdout)
{
    Factory factory;
    std::unique_ptr<nts::IComponent> c4008 = factory.createComponent("4008");

    cr_assert_not_null(c4008);
}

// 4013
Test(Factory, C4013, .init = cr_redirect_stdout)
{
    Factory factory;
    std::unique_ptr<nts::IComponent> c4013 = factory.createComponent("4013");

    cr_assert_not_null(c4013);
}

// 4017
Test(Factory, C4017, .init = cr_redirect_stdout)
{
    Factory factory;
    std::unique_ptr<nts::IComponent> c4017 = factory.createComponent("4017");

    cr_assert_not_null(c4017);
}

// 4040
Test(Factory, C4040, .init = cr_redirect_stdout)
{
    Factory factory;
    std::unique_ptr<nts::IComponent> c4040 = factory.createComponent("4040");

    cr_assert_not_null(c4040);
}

// 4094
Test(Factory, C4094, .init = cr_redirect_stdout)
{
    Factory factory;
    std::unique_ptr<nts::IComponent> c4094 = factory.createComponent("4094");

    cr_assert_not_null(c4094);
}

// 4512
Test(Factory, C4512, .init = cr_redirect_stdout)
{
    Factory factory;
    std::unique_ptr<nts::IComponent> c4512 = factory.createComponent("4512");

    cr_assert_not_null(c4512);
}

// 4514
Test(Factory, C4514, .init = cr_redirect_stdout)
{
    Factory factory;
    std::unique_ptr<nts::IComponent> c4514 = factory.createComponent("4514");

    cr_assert_not_null(c4514);
}

// 4801
Test(Factory, C4801, .init = cr_redirect_stdout)
{
    Factory factory;
    std::unique_ptr<nts::IComponent> c4801 = factory.createComponent("4801");

    cr_assert_not_null(c4801);
}

// 2716
Test(Factory, C2716, .init = cr_redirect_stdout)
{
    Factory factory;
    std::unique_ptr<nts::IComponent> c2716 = factory.createComponent("2716");

    cr_assert_not_null(c2716);
}

// Logger
Test(Factory, Logger, .init = cr_redirect_stdout)
{
    Factory factory;
    std::unique_ptr<nts::IComponent> logger = factory.createComponent("logger");

    cr_assert_not_null(logger);
}