#include "Goblin.h"
#include <string>

Goblin::Goblin(int round) 
    : Inimigo("Goblin (Nvl " + std::to_string(round) + ")", 60 + (round * 15), 15 + (round * 6)) {
}
