/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Game.hpp"
#include "blocks/bMap.hpp"
#include "blocks/platforms/tOneMap.hpp"
#include "blocks/platforms/tTwoMap.hpp"
#include "blocks/platforms/tThreeMap.hpp"
#include "blocks/platforms/tFourMap.hpp"
#include "blocks/action/Lever.hpp"
#include "blocks/platforms/moving/pOneBlock.hpp"
#include "blocks/platforms/moving/dOneBlock.hpp"
#include "blocks/platforms/effect/eOneMap.hpp"
#include "blocks/platforms/effect/eTwoMap.hpp"
#include "blocks/platforms/effect/eThreeMap.hpp"
#include "blocks/platforms/effect/fOneMap.hpp"
#include "blocks/platforms/effect/fTwoMap.hpp"
#include "blocks/platforms/effect/fThreeMap.hpp"
#include "blocks/platforms/effect/pOneMap.hpp"
#include "blocks/platforms/effect/pTwoMap.hpp"
#include "blocks/platforms/effect/pThreeMap.hpp"
#include "blocks/collectible/diamondBlue.hpp"
#include "blocks/collectible/diamondRed.hpp"
#include "blocks/platforms/pushable/Crate.hpp"

Game *currentGame = nullptr;

void fillFactory(BlockFactory &factory)
{
    factory.registerBlock("B_map", [](const JsonObject *block_data) -> AbstractBlock * { return new BMap(block_data);});
    factory.registerBlock("T1_map", [](const JsonObject *block_data) -> AbstractBlock * { return new TOneMap(block_data);});
    factory.registerBlock("T2_map", [](const JsonObject *block_data) -> AbstractBlock * { return new TTwoMap(block_data);});
    factory.registerBlock("T3_map", [](const JsonObject *block_data) -> AbstractBlock * { return new TThreeMap(block_data);});
    factory.registerBlock("T4_map", [](const JsonObject *block_data) -> AbstractBlock * { return new TFourMap(block_data);});

    factory.registerBlock("F1_map", [](const JsonObject *block_data) -> AbstractBlock * { return new FOneMap(block_data);});
    factory.registerBlock("F2_map", [](const JsonObject *block_data) -> AbstractBlock * { return new FTwoMap(block_data);});
    factory.registerBlock("F3_map", [](const JsonObject *block_data) -> AbstractBlock * { return new FThreeMap(block_data);});
    factory.registerBlock("E1_map", [](const JsonObject *block_data) -> AbstractBlock * { return new EOneMap(block_data);});
    factory.registerBlock("E2_map", [](const JsonObject *block_data) -> AbstractBlock * { return new ETwoMap(block_data);});
    factory.registerBlock("E3_map", [](const JsonObject *block_data) -> AbstractBlock * { return new EThreeMap(block_data);});
    factory.registerBlock("P1_map", [](const JsonObject *block_data) -> AbstractBlock * { return new POneMap(block_data);});
    factory.registerBlock("P2_map", [](const JsonObject *block_data) -> AbstractBlock * { return new PTwoMap(block_data);});
    factory.registerBlock("P3_map", [](const JsonObject *block_data) -> AbstractBlock * { return new PThreeMap(block_data);});

    factory.registerBlock("Block_map", [](const JsonObject *block_data) -> AbstractBlock * { return new Crate(block_data);});
    factory.registerBlock("L_map", [](const JsonObject *block_data) -> AbstractBlock * { return new Lever(block_data);});
    factory.registerBlock("P_map", [](const JsonObject *block_data) -> AbstractBlock * { return new POneBlock(block_data);});
    factory.registerBlock("D_map", [](const JsonObject *block_data) -> AbstractBlock * { return new DOneBlock(block_data);});
    factory.registerBlock("DiamondBlue", [](const JsonObject *block_data) -> AbstractBlock * { return new DiamondBlue(block_data);});
    factory.registerBlock("DiamondRed", [](const JsonObject *block_data) -> AbstractBlock * { return new DiamondRed(block_data);});
}

int main()
{
    BlockFactory factory;
    fillFactory(factory);
    auto *game = new Game("levels", factory);

    currentGame = game;
    game->run();
    delete game;
    return 0;
}
