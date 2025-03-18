/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** tests_acomponent
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>

#include "AComponent.hpp"
#include "True.hpp"
#include "Error.hpp"

// Constructor
Test(AComponent, constructor)
{
    True trueComponent;
}

// Destructor
Test(AComponent, destructor)
{
    True trueComponent;
}

// Compute
Test(AComponent, compute)
{
    True trueComponent;

    cr_assert_eq(trueComponent.compute(1), nts::True);
}

Test(AComponent, compute_invalid_pin)
{
    True trueComponent;

    cr_assert_throw(trueComponent.compute(0), nts::InvalidArgument);
}


// GetLink
Test(AComponent, get_link)
{
    True trueComponent;

    trueComponent.setLink(1, trueComponent, 1);
    cr_assert_eq(trueComponent.getLink(1), nts::True);
}

Test(AComponent, get_link_invalid_pin)
{
    True trueComponent;

    cr_assert_eq(trueComponent.getLink(0), nts::Undefined);
}

// GetLinkComponent
Test(AComponent, get_link_component)
{
    True trueComponent;

    trueComponent.setLink(1, trueComponent, 1);
    cr_assert_not_null(trueComponent.getLinkComponent(1));
}

Test(AComponent, get_link_component_invalid_pin)
{
    True trueComponent;

    cr_assert_null(trueComponent.getLinkComponent(0));
}

// SetLink
Test(AComponent, set_link)
{
    True trueComponent;
    True trueComponent2;

    trueComponent.setLink(1, trueComponent2, 1);
    cr_assert_eq(trueComponent.getLink(1), nts::True);
}

Test(AComponent, set_link_invalid_pin)
{
    True trueComponent;
    True trueComponent2;

    cr_assert_throw(trueComponent.setLink(0, trueComponent2, 1), nts::InvalidArgument);
}

// Simulate
Test(AComponent, simulate)
{
    True trueComponent;

    cr_assert_no_throw(trueComponent.simulate(1));
}
