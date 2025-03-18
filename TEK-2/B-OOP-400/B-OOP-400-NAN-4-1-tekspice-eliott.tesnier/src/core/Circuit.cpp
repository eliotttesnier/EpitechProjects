/*
** EPITECH PROJECT, 2024
** NTS
** File description:
** Circuit
*/

#include "Circuit.hpp"
#include "Factory.hpp"
#include "Error.hpp"
#include "Input.hpp"
#include "Clock.hpp"
#include "Output.hpp"
#include <iostream>

// Constructor
/**
 * @brief Constructor for the class Circuit.
 */
Circuit::Circuit()
{
    _tick = 0;
}

/**
 * @brief Destructor for the class Circuit.
 *
 * Destroy the Circuit object.
 */
Circuit::~Circuit()
{
}

// Methods
/**
 * @brief Simulate the circuit.
 */
void Circuit::simulate()
{
    for (auto &component : _components)
        component.second->simulate(_tick);
    _tick++;
}

/**
 * @brief Display the circuit.
 */
void Circuit::display() const
{
    std::cout << "tick: " << _tick << std::endl;
    displayInputs();
    displayOutputs();
}

// Component handling
/**
 * @brief Add a component to the circuit.
 *
 * @param name the name of the component
 * @param type the type of the component
 * @param factory the factory
 */
void Circuit::addComponent(const std::string &name, const std::string &type, Factory &factory)
{
    _components[name] = factory.createComponent(type);
}

/**
 * @brief Check if the circuit has a component.
 *
 * @param name the name of the component
 *
 * @return bool.
 */
bool Circuit::hasComponent(const std::string &name) const
{
    return _components.find(name) != _components.end();
}

/**
 * @brief Link two components.
 *
 * @param name1 the name of the first component
 * @param pin1 the pin of the first component
 * @param name2 the name of the second component
 * @param pin2 the pin of the second component
 */
void Circuit::linkComponents(const std::string &name1, std::size_t pin1, const std::string &name2, std::size_t pin2)
{
    _components[name1]->setLink(pin1, *_components[name2], pin2);
    _components[name2]->setLink(pin2, *_components[name1], pin1);
}

// Input/Output handling
/**
 * @brief Set the input.
 *
 * @param name the name of the input
 * @param value the value of the input
 */
void Circuit::setInput(const std::string &name, nts::Tristate value)
{
    if (!hasComponent(name))
        throw nts::InvalidInput("Error: component \"" + name + "\" does not exist.");
    if (dynamic_cast<Input *>(_components[name].get()) == nullptr && dynamic_cast<Clock *>(_components[name].get()) == nullptr)
        throw nts::InvalidInput("Error: component \"" + name + "\" is not an input.or a clock.");
    if (dynamic_cast<Input *>(_components[name].get()) != nullptr)
        dynamic_cast<Input *>(_components[name].get())->setState(value);
    if (dynamic_cast<Clock *>(_components[name].get()) != nullptr)
        dynamic_cast<Clock *>(_components[name].get())->setState(value);
}

/**
 * @brief Display the inputs of the circuit.
 */
void Circuit::displayInputs() const
{
    std::string name;
    nts::Tristate state;
    std::cout << "input(s):" << std::endl;

    for (auto &component : _components) {
        if (dynamic_cast<Input *>(component.second.get()) != nullptr || dynamic_cast<Clock *>(component.second.get()) != nullptr) {
            name = component.first;
            state = component.second->compute(1);

            std::cout << "  " << name << ": ";
            std::cout << (state == nts::Tristate::Undefined ? "U" : state == nts::Tristate::True ? "1" : "0") << std::endl;
        }
    }
}

/**
 * @brief Display the outputs of the circuit.
 */
void Circuit::displayOutputs() const
{
    std::string name;
    nts::Tristate state;
    std::cout << "output(s):" << std::endl;

    for (auto &component : _components) {
        if (dynamic_cast<Output *>(component.second.get()) != nullptr) {
            name = component.first;
            state = component.second->compute(1);

            std::cout << "  " << name << ": ";
            std::cout << (state == nts::Tristate::Undefined ? "U" : state == nts::Tristate::True ? "1" : "0") << std::endl;
        }
    }
}
