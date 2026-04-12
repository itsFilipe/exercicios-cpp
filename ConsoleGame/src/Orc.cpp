#include "Orc.h"
#include <string>

Orc::Orc(int round) 
    : Inimigo("Orc (Nvl " + std::to_string(round) + ")", 100 + (round * 25), 5 + (round * 5)) {
}
