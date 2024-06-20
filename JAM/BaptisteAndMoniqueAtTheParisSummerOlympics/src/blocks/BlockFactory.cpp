/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <utility>
#include "blocks/BlockFactory.hpp"

BlockFactory::BlockFactory() = default;

static bool validateBlockData(const JsonObject *block_data)
{
    try {
        block_data->getString("type");
        block_data->getValue<JsonObject>("data");
        block_data->getValue<JsonObject>("pos");
    } catch (const std::exception &e) {
        return false;
    }
    return true;
}

AbstractBlock *BlockFactory::createBlock(const JsonObject *block_data) const
{
    if (!validateBlockData(block_data))
        return nullptr;
    auto block_name = block_data->getString("type");
    auto creator = _block_creators.find(block_name);
    if (creator == _block_creators.end())
        return nullptr;
    return creator->second(block_data);
}

void BlockFactory::registerBlock(const std::string &block_name, const BlockCreator& creator)
{
    _block_creators[block_name] = std::move(creator);
}

BlockFactory &BlockFactory::operator=(const BlockFactory &other)
{
    if (this == &other)
        return *this;
    _block_creators = other._block_creators;
    return *this;
}

AbstractBlock *BlockFactory::operator()(const JsonObject *block_data) const
{
    return createBlock(block_data);
}
