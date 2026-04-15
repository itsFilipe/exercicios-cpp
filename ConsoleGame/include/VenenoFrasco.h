#ifndef VENENO_FRASCO_H
#define VENENO_FRASCO_H

#include "Item.h"
#include "StatusEffect.h"

class VenenoFrasco : public Item {
private:
    int danoTick;
    int duracao;

public:
    VenenoFrasco()
        : Item(4, "Frasco de Veneno", "Envenena o inimigo: 8 dmg/turno por 3 turnos"),
          danoTick(8), duracao(3) {}

    bool esOfensivo() const override { return true; }

    void aplicar(Personagem* alvo) override {
        std::cout << "Voce jogou o frasco de veneno!\n";
        alvo->aplicarEfeito({StatusEffect::Tipo::VENENO, duracao, danoTick});
    }
};

#endif
