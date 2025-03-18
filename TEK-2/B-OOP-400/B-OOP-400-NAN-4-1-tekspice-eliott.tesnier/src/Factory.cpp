/*
** EPITECH PROJECT, 2024
** NTS
** File description:
** Factory
*/

#include "Factory.hpp"
#include "Input.hpp"
#include "Output.hpp"
#include "True.hpp"
#include "False.hpp"
#include "Clock.hpp"
#include "And.hpp"
#include "Or.hpp"
#include "Xor.hpp"
#include "Not.hpp"
#include "4001.hpp"
#include "4011.hpp"
#include "4030.hpp"
#include "4069.hpp"
#include "4071.hpp"
#include "4081.hpp"
#include "4008.hpp"
#include "4013.hpp"
#include "4017.hpp"
#include "4040.hpp"
#include "4094.hpp"
#include "4512.hpp"
#include "4514.hpp"
#include "4801.hpp"
#include "2716.hpp"
#include "Logger.hpp"

Factory::Factory()
{
    _creators["input"] = []() { return std::make_unique<Input>(); };
    _creators["output"] = []() { return std::make_unique<Output>(); };
    _creators["true"] = []() { return std::make_unique<True>(); };
    _creators["false"] = []() { return std::make_unique<False>(); };
    _creators["clock"] = []() { return std::make_unique<Clock>(); };
    _creators["and"] = []() { return std::make_unique<And>(); };
    _creators["or"] = []() { return std::make_unique<Or>(); };
    _creators["xor"] = []() { return std::make_unique<Xor>(); };
    _creators["not"] = []() { return std::make_unique<Not>(); };
    _creators["4001"] = []() { return std::make_unique<C4001>(); };
    _creators["4011"] = []() { return std::make_unique<C4011>(); };
    _creators["4030"] = []() { return std::make_unique<C4030>(); };
    _creators["4069"] = []() { return std::make_unique<C4069>(); };
    _creators["4071"] = []() { return std::make_unique<C4071>(); };
    _creators["4081"] = []() { return std::make_unique<C4081>(); };
    _creators["4008"] = []() { return std::make_unique<C4008>(); };
    _creators["4013"] = []() { return std::make_unique<C4013>(); };
    _creators["4017"] = []() { return std::make_unique<C4017>(); };
    _creators["4040"] = []() { return std::make_unique<C4040>(); };
    _creators["4094"] = []() { return std::make_unique<C4094>(); };
    _creators["4512"] = []() { return std::make_unique<C4512>(); };
    _creators["4514"] = []() { return std::make_unique<C4514>(); };
    _creators["4801"] = []() { return std::make_unique<C4801>(); };
    _creators["2716"] = []() { return std::make_unique<C2716>(); };
    _creators["logger"] = []() { return std::make_unique<Logger>(); };
}

Factory::~Factory()
{
}

std::unique_ptr<nts::IComponent> Factory::createComponent(const std::string &type)
{
    return _creators[type]();
}
