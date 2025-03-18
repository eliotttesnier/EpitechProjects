/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <functional>
#include <unordered_map>
#include "json/Json.hpp"
#include "AbstractBlock.hpp"

class BlockFactory {
public:
    typedef std::function<AbstractBlock *(const JsonObject *)> BlockCreator;
protected:
    std::unordered_map<std::string, BlockCreator> _block_creators;
public:
    BlockFactory();
    ~BlockFactory() = default;
    BlockFactory(const BlockFactory &other) = default;

    // ---------- Methods ----------
    AbstractBlock *createBlock(const JsonObject *block_data) const;
    void registerBlock(const std::string &block_name, const BlockCreator& creator);

    // ---------- Operator Overloads ----------
    BlockFactory &operator=(const BlockFactory &other);
    AbstractBlock *operator()(const JsonObject *block_data) const;
};
