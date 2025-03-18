/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** tests_simulator
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>
#include <signal.h>
#include <sys/wait.h>

#include "Simulator.hpp"
#include "AComponent.hpp"
#include "Error.hpp"

// Constructor
Test(Simulator, constructor)
{
    Simulator simulator("tests/files/nts_single/and.nts");

    cr_assert_eq(simulator.getReturnCode(), 0);
}

Test(Simulator, invalidConstructor, .init = cr_redirect_stderr)
{
    Simulator simulator("invalid");

    cr_assert_eq(simulator.getReturnCode(), 84);
}

// Destructor
Test(Simulator, destructor)
{
    Simulator *simulator = new Simulator("tests/files/nts_single/and.nts");

    cr_assert_no_throw(delete simulator);
}

// Getters
Test(Simulator, getCircuit, .init = cr_redirect_stdout)
{
    Simulator simulator("tests/files/nts_single/and.nts");
    Circuit &circuit = simulator.getCircuit();

    (void)circuit;
    cr_assert_no_throw();
}

Test(Simulator, getReturnCode)
{
    Simulator simulator("tests/files/nts_single/and.nts");

    cr_assert_eq(simulator.getReturnCode(), 0);
}

// Member functions
Test(Simulator, initCircuit)
{
    Simulator simulator("tests/files/nts_single/and.nts");

    cr_assert_no_throw();
}

Test(Simulator, initCircuitInvalid, .init = cr_redirect_stderr)
{
    Simulator simulator("tests/files/nts_single/and.nts");

    cr_assert_throw(simulator.initCircuit("invalid"), nts::InvalidFile);
}

// Shell functions
// parseInput
Test(Simulator, parseInputExit, .init = cr_redirect_stdout)
{
    Simulator simulator("tests/files/nts_single/and.nts");

    cr_assert_no_throw(simulator.parseInput("exit"));
}

Test(Simulator, parseInputDisplay, .init = cr_redirect_stdout)
{
    Simulator simulator("tests/files/nts_single/and.nts");

    cr_assert_no_throw(simulator.parseInput("display"));
}

Test(Simulator, parseInputSimulate, .init = cr_redirect_stdout)
{
    Simulator simulator("tests/files/nts_single/and.nts");

    cr_assert_no_throw(simulator.parseInput("simulate"));
}

Test(Simulator, parseInputLoop, .init = cr_redirect_stdout)
{
    cr_redirect_stderr();
    Simulator simulator("tests/files/nts_single/and.nts");
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        simulator.parseInput("loop");
        exit(0);

    } else if (pid > 0) {
        // Parent process
        usleep(100000);
        kill(pid, SIGINT);
    }
    cr_assert_eq(0, 0);
}

Test(Simulator, parseInputEqual, .init = cr_redirect_stdout)
{
    Simulator simulator("tests/files/nts_single/and.nts");

    cr_assert_no_throw(simulator.parseInput("in_1=1"));
}

Test(Simulator, parseInvalidInput, .init = cr_redirect_stderr)
{
    Simulator simulator("tests/files/nts_single/and.nts");

    cr_assert_throw(simulator.parseInput("invalid"), nts::InvalidInput);
}

// userSetInput
Test(Simulator, userSetInput, .init = cr_redirect_stdout)
{
    Simulator simulator("tests/files/nts_single/and.nts");

    cr_assert_no_throw(simulator.userSetInput("in_1=1"));
}

Test(Simulator, userSetInputInvalidValue, .init = cr_redirect_stderr)
{
    Simulator simulator("tests/files/nts_single/and.nts");

    cr_assert_throw(simulator.userSetInput("in_1=2"), nts::InvalidInput);
}

Test(Simulator, userSetInputInvalidComponent, .init = cr_redirect_stderr)
{
    Simulator simulator("tests/files/nts_single/and.nts");

    cr_assert_no_throw(simulator.userSetInput("invalid=1"));
    cr_assert_eq(simulator.getReturnCode(), 84);
}

// userExit
Test(Simulator, userExit, .init = cr_redirect_stdout)
{
    Simulator simulator("tests/files/nts_single/and.nts");

    cr_assert_no_throw(simulator.userExit());
}

// userDisplay
Test(Simulator, userDisplay, .init = cr_redirect_stdout)
{
    Simulator simulator("tests/files/nts_single/and.nts");

    cr_assert_no_throw(simulator.userDisplay());
}

Test(Simulator, userDisplayInvalidArgument, .init = cr_redirect_stdout)
{
    cr_redirect_stderr();
    Factory factory;
    Simulator simulator("tests/files/nts_single/and.nts");

    simulator.getCircuit().addComponent("output", "output", factory);
    cr_assert_no_throw(simulator.userDisplay());
    cr_assert_eq(simulator.getReturnCode(), 84);
}

// userSimulate
Test(Simulator, userSimulate, .init = cr_redirect_stdout)
{
    Simulator simulator("tests/files/nts_single/and.nts");

    cr_assert_no_throw(simulator.userSimulate());
}

// userLoop
Test(Simulator, userLoop, .init = cr_redirect_stdout)
{
    cr_redirect_stderr();
    Simulator simulator("tests/files/nts_single/and.nts");
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        simulator.userLoop();
        exit(0);

    } else if (pid > 0) {
        // Parent process
        usleep(100000);
        kill(pid, SIGINT);
    }
    cr_assert_eq(0, 0);
}

// runShell
Test(Simulator, runShell, .init = cr_redirect_stdout)
{
    Simulator simulator("tests/files/nts_single/and.nts");

    // Test with EOF
    std::stringstream input;
    auto cinbuf = std::cin.rdbuf(input.rdbuf());

    cr_assert_no_throw(simulator.runShell());

    // Restore cin
    std::cin.rdbuf(cinbuf);
}

Test(Simulator, runShellWithExit, .init = cr_redirect_stdout)
{
    Simulator simulator("tests/files/nts_single/and.nts");

    // Test with "exit" command
    std::stringstream input("exit\n");
    auto cinbuf = std::cin.rdbuf(input.rdbuf());

    cr_assert_no_throw(simulator.runShell());

    // Restore cin
    std::cin.rdbuf(cinbuf);
}

Test(Simulator, runShellWithError, .init = cr_redirect_stdout)
{
    cr_redirect_stderr();
    Simulator simulator("tests/files/nts_single/and.nts");

    // Test with invalid command
    std::stringstream input("invalid\n");
    auto cinbuf = std::cin.rdbuf(input.rdbuf());

    cr_assert_no_throw(simulator.runShell());
    cr_assert_eq(simulator.getReturnCode(), 84);

    // Restore cin
    std::cin.rdbuf(cinbuf);
}
