/*
** EPITECH PROJECT, 2024
** NTS
** File description:
** AComponent
*/

#include "AComponent.hpp"
#include "Error.hpp"
#include "True.hpp"
#include "False.hpp"

// Constructor
AComponent::AComponent()
{
}

// Destructor
AComponent::~AComponent()
{
}

nts::Tristate AComponent::compute(std::size_t pin)
{
    if (!isValidPin(pin))
        throw nts::InvalidArgument("Invalid pin");

    return computeOutput(pin);
}

nts::Tristate AComponent::getLink(std::size_t pin) const
{
    auto it = _links.find(pin);
    if (it == _links.end())
        return nts::Undefined;

    const auto& [component, otherPin] = it->second;

    return component->compute(otherPin);
}

std::shared_ptr<nts::IComponent> AComponent::getLinkComponent(std::size_t pin) const
{
    auto it = _links.find(pin);
    if (it == _links.end())
        return nullptr;

    return it->second.first;
}

void AComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (!isValidPin(pin))
        throw nts::InvalidArgument("Invalid pin");

    _links[pin] = {std::shared_ptr<nts::IComponent>(&other, [](nts::IComponent *) {}), otherPin};
}

void AComponent::simulate(std::size_t tick)
{
    (void)tick;
}
