#include "Orc.h"
#include "StatusEffect.h"
#include <string>
#include <cstdlib>
#include <iostream>

#define RESET  "\033[0m"
#define RED    "\033[31m"
#define YELLOW "\033[33m"

Orc::Orc(int round)
    : Inimigo("Orc (Nvl " + std::to_string(round) + ")", 100 + (round * 25), 5 + (round * 5)) {}

void Orc::atacar(Personagem& alvo) {
    // 15% chance: stunning strike — heavy hit that stuns for 1 turn
    if (rand() % 100 < 15) {
        int dano = danoBase + (rand() % (danoBase / 2 + 1));
        alvo.receberDano(dano);
        alvo.aplicarEfeito({StatusEffect::Tipo::ATORDOADO, 1, 0});
        std::cout << RED << nome << " deu um GOLPE ATORDOANTE causando "
                  << dano << " de dano!\n" << RESET;
    } else {
        Personagem::atacar(alvo);
    }
}
