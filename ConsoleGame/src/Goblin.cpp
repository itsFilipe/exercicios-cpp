#include "Goblin.h"
#include <string>
#include <cstdlib>
#include <iostream>

#define RESET "\033[0m"
#define RED   "\033[31m"

Goblin::Goblin(int round)
    : Inimigo("Goblin (Nvl " + std::to_string(round) + ")", 60 + (round * 15), 15 + (round * 6)) {}

void Goblin::atacar(Personagem& alvo) {
    // Always attacks twice for 60% base damage each hit
    std::cout << RED << nome << " ataca DUAS VEZES furtivamente!\n" << RESET;
    for (int i = 0; i < 2; i++) {
        int base = static_cast<int>(danoBase * 0.6);
        int dano = (base / 2) + (rand() % (base / 2 + 1));
        alvo.receberDano(dano);
        std::cout << RED << "  Golpe " << (i + 1) << ": " << dano << " de dano!\n" << RESET;
    }
}
