/*
** EPITECH PROJECT, 2024
** NTS
** File description:
** Simulator
*/

#include "Simulator.hpp"
#include "Error.hpp"
#include <iostream>
#include <csignal>

volatile sig_atomic_t stopLoop = 0;

// Constructor

/**
 * @brief Constructor for the class Simulator.
 *
 * @param filename the filename of the file to parse
 */
Simulator::Simulator(const std::string &filename)
{
    _returnCode = 0;
    _filename = filename;
    _exit = false;
    _loop = false;
    _parser = Parser();
    _circuit = std::make_unique<Circuit>();
    _factory = Factory();

    try {
        initCircuit(filename);
    } catch (const nts::InvalidFile &e) {
        std::cerr << e.what() << std::endl;
        _returnCode = 84;
        _exit = true;
    }
}

/**
 * @brief Destructor for the class Simulator.
 *
 * Destroy the Simulator object.
 */
Simulator::~Simulator()
{
}

// Getters
/**
 * @brief Get the circuit.
 *
 * @return the circuit
 */
Circuit &Simulator::getCircuit() const
{
    return *_circuit;
}

/**
 * @brief Get the return code.
 *
 * @return the return code
 */
int Simulator::getReturnCode() const
{
    return _returnCode;
}

// Member functions
/**
 * @brief Initialize the circuit.
 *
 * @param filename the filename of the file to parse
 */
void Simulator::initCircuit(const std::string &filename)
{
    _parser.checkFile(filename);
    _parser.parseFile();
    _parser.setComponents(*_circuit, _factory);
    _parser.setLinks(*_circuit);
}

/**
 * @brief Run the shell.
 */
void Simulator::runShell()
{
    std::string input;

    while (!_exit) {
        std::cout << "> ";
        std::getline(std::cin, input);
        try {
            parseInput(input);
        } catch (const nts::InvalidInput &e) {
            std::cerr << e.what() << std::endl;
            _returnCode = 84;
            _exit = true;
        }
    }
}

// Shell functions
/**
 * @brief Parse the input.
 *
 * @param input the input to parse
 */
void Simulator::parseInput(const std::string &input)
{
    if (input == "exit" || std::cin.eof())
        userExit();
    else if (input == "display")
        userDisplay();
    else if (input == "simulate")
        userSimulate();
    else if (input == "loop")
        userLoop();
    else if (input.find_first_of("=") != std::string::npos)
        userSetInput(input);
    else
        throw nts::InvalidInput("Error: invalid command.");
}

/**
 * @brief Set the input.
 *
 * @param input the input to set
 */
void Simulator::userSetInput(const std::string &input)
{
    std::string name = input.substr(0, input.find_first_of("="));
    std::string value = input.substr(input.find_first_of("=") + 1);
    nts::Tristate state;

    if (value != "0" && value != "1" && value != "U")
        throw nts::InvalidInput("Error: invalid value.");
    state = value == "0" ? nts::Tristate::False : value == "1" ? nts::Tristate::True : nts::Tristate::Undefined;
    try {
        _circuit.get()->setInput(name, state);
    } catch (nts::InvalidInput &e) {
        std::cerr << e.what() << std::endl;
        _returnCode = 84;
        _exit = true;
    }
}

/**
 * @brief Exit the shell.
 */
void Simulator::userExit()
{
    _exit = true;
}

/**
 * @brief Display the circuit.
 */
void Simulator::userDisplay()
{
    try {
        _circuit->display();
    } catch (const nts::InvalidArgument &e) {
        std::cerr << e.what() << std::endl;
        _returnCode = 84;
        _exit = true;
    }
}

/**
 * @brief Simulate the circuit.
 */
void Simulator::userSimulate()
{
    _circuit->simulate();
}

/**
 * @brief Handle the signal SIGINT.
 *
 * @param signal the signal
 */
void handleSigint(int signal)
{
    (void)signal;
    stopLoop = 1;
}

/**
 * @brief Loop the simulation.
 */
void Simulator::userLoop()
{
    _loop = !_loop;
    std::signal(SIGINT, handleSigint);
    while (_loop && !stopLoop) {
        _circuit->simulate();
        _circuit->display();
        usleep(500000);
    }
    _loop = !_loop;
    stopLoop = 0;
}
