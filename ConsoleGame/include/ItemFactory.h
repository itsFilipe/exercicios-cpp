#ifndef ITEM_FACTORY_H
#define ITEM_FACTORY_H

#include <memory>
#include "Item.h"
#include "PocaoVida.h"
#include "PocaoMana.h"
#include "VenenoFrasco.h"

// Single place that maps item IDs to concrete objects.
// Used by save/load, loot chest, and shop — add new items here only.
inline std::unique_ptr<Item> criarItem(int id) {
    switch (id) {
        case 1: return std::make_unique<PocaoVida>(1, "Pocao Pequena", "Recupera 50 HP",  50);
        case 2: return std::make_unique<PocaoVida>(2, "Pocao Grande",  "Recupera 100 HP", 100);
        case 3: return std::make_unique<PocaoMana>(3, "Pocao Mana",    "Recupera 30 MP",  30);
        case 4: return std::make_unique<VenenoFrasco>();
        default: return nullptr;
    }
}

#endif
