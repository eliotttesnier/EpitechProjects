/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** tests_parser
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include <iostream>

#include "Parser.hpp"
#include "Error.hpp"

// createParser
Test(Parser, createParser)
{
    Parser parser;

    cr_assert_eq(parser.getComponents().size(), 0);
    cr_assert_eq(parser.getLinks().size(), 0);
}

// checkFile
Test(Parser, checkFile, .init = cr_redirect_stderr)
{
    Parser parser;

    cr_assert_no_throw(parser.checkFile("tests/files/valid.nts"));
    cr_assert_throw(parser.checkFile("tests/files/not_existing.nts"), nts::InvalidFile);
    cr_assert_throw(parser.checkFile("tests/files/invalid_extension.txt"), nts::InvalidFile);
}

// parseFile
Test(Parser, parseFileValid, .init = cr_redirect_stderr)
{
    Parser parser;

    cr_assert_no_throw(parser.checkFile("tests/files/valid.nts"));
    cr_assert_no_throw(parser.parseFile());
    cr_assert_eq(parser.getComponents().size(), 4);
    cr_assert_eq(parser.getLinks().size(), 3);
}

Test(Parser, parseFileEmpty, .init = cr_redirect_stderr)
{
    Parser parser;

    cr_assert_no_throw(parser.checkFile("tests/files/empty.nts"));
    cr_assert_throw(parser.parseFile(), nts::InvalidFile);
}

Test(Parser, parseInvalidType, .init = cr_redirect_stderr)
{
    Parser parser;

    cr_assert_no_throw(parser.checkFile("tests/files/invalid_type.nts"));
    cr_assert_throw(parser.parseFile(), nts::InvalidFile);
}

Test(Parser, parseMultipleName, .init = cr_redirect_stderr)
{
    Parser parser;

    cr_assert_no_throw(parser.checkFile("tests/files/multiple_name.nts"));
    cr_assert_throw(parser.parseFile(), nts::InvalidFile);
}

Test(Parser, parseInvalidPin, .init = cr_redirect_stderr)
{
    Parser parser;

    cr_assert_no_throw(parser.checkFile("tests/files/invalid_pin.nts"));
    cr_assert_throw(parser.parseFile(), nts::InvalidFile);
}

Test(Parser, parseNegativePin, .init = cr_redirect_stderr)
{
    Parser parser;

    cr_assert_no_throw(parser.checkFile("tests/files/negative_pin.nts"));
    cr_assert_throw(parser.parseFile(), nts::InvalidFile);
}

Test(Parser, parseAlphabeticalPin, .init = cr_redirect_stderr)
{
    Parser parser;

    cr_assert_no_throw(parser.checkFile("tests/files/alphabetical_pin.nts"));
    cr_assert_throw(parser.parseFile(), nts::InvalidFile);
}

Test(Parser, parseOutOfRangePin, .init = cr_redirect_stderr)
{
    Parser parser;

    cr_assert_no_throw(parser.checkFile("tests/files/out_of_range_pin.nts"));
    cr_assert_throw(parser.parseFile(), nts::InvalidFile);
}

Test(Parser, parseInvalidName, .init = cr_redirect_stderr)
{
    Parser parser;

    cr_assert_no_throw(parser.checkFile("tests/files/invalid_name.nts"));
    cr_assert_throw(parser.parseFile(), nts::InvalidFile);
}

Test(Parser, parseNoChipsetStatement, .init = cr_redirect_stderr)
{
    Parser parser;

    cr_assert_no_throw(parser.checkFile("tests/files/no_chipset_statement.nts"));
    cr_assert_throw(parser.parseFile(), nts::InvalidFile);
}

Test(Parser, parseMultipleChipsetStatement, .init = cr_redirect_stderr)
{
    Parser parser;

    cr_assert_no_throw(parser.checkFile("tests/files/multiple_chipset_statement.nts"));
    cr_assert_throw(parser.parseFile(), nts::InvalidFile);
}

Test(Parser, parseInvalidFormat, .init = cr_redirect_stderr)
{
    Parser parser;

    cr_assert_no_throw(parser.checkFile("tests/files/invalid_format.nts"));
    cr_assert_throw(parser.parseFile(), nts::InvalidFile);
}

Test(Parser, parseEmptyComponentName, .init = cr_redirect_stderr)
{
    Parser parser;

    cr_assert_no_throw(parser.checkFile("tests/files/empty_component_name.nts"));
    cr_assert_throw(parser.parseFile(), nts::InvalidFile);
}

Test(Parser, parseNoComponents, .init = cr_redirect_stderr)
{
    Parser parser;

    cr_assert_no_throw(parser.checkFile("tests/files/no_components.nts"));
    cr_assert_throw(parser.parseFile(), nts::InvalidFile);
}

Test(Parser, parseNoLinksStatement, .init = cr_redirect_stderr)
{
    Parser parser;

    cr_assert_no_throw(parser.checkFile("tests/files/no_links_statement.nts"));
    cr_assert_throw(parser.parseFile(), nts::InvalidFile);
}

Test(Parser, parseMultipleLinksStatement, .init = cr_redirect_stderr)
{
    Parser parser;

    cr_assert_no_throw(parser.checkFile("tests/files/multiple_links_statement.nts"));
    cr_assert_throw(parser.parseFile(), nts::InvalidFile);
}

Test(Parser, parseInvalidLinkFormat, .init = cr_redirect_stderr)
{
    Parser parser;

    cr_assert_no_throw(parser.checkFile("tests/files/invalid_link_format.nts"));
    cr_assert_throw(parser.parseFile(), nts::InvalidFile);
}

Test(Parser, parseNoColon, .init = cr_redirect_stderr)
{
    Parser parser;

    cr_assert_no_throw(parser.checkFile("tests/files/no_colon.nts"));
    cr_assert_throw(parser.parseFile(), nts::InvalidFile);
}

Test(Parser, parseUnknownComponent, .init = cr_redirect_stderr)
{
    Parser parser;

    cr_assert_no_throw(parser.checkFile("tests/files/unknown_component.nts"));
    cr_assert_throw(parser.parseFile(), nts::InvalidFile);
}

Test(Parser, parseInvalid2Pin, .init = cr_redirect_stderr)
{
    Parser parser;

    cr_assert_no_throw(parser.checkFile("tests/files/invalid_2_pin.nts"));
    cr_assert_throw(parser.parseFile(), nts::InvalidFile);
}

// setComponents
Test(Parser, setComponents, .init = cr_redirect_stderr)
{
    Parser parser;
    Circuit circuit;
    Factory factory;

    cr_assert_no_throw(parser.checkFile("tests/files/valid.nts"));
    cr_assert_no_throw(parser.parseFile());
    cr_assert_no_throw(parser.setComponents(circuit, factory));
}

// setLinks
Test(Parser, setLinks, .init = cr_redirect_stderr)
{
    Parser parser;
    Circuit circuit;
    Factory factory;

    cr_assert_no_throw(parser.checkFile("tests/files/valid.nts"));
    cr_assert_no_throw(parser.parseFile());
    cr_assert_no_throw(parser.setComponents(circuit, factory));
    cr_assert_no_throw(parser.setLinks(circuit));
}
