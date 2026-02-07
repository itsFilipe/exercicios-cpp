#ifndef POCAO_VIDA_H
#define POCAO_VIDA_H

#include "Item.h"

class PocaoVida : public Item {
private:
    int cura;

public:
    PocaoVida(int quantidadeCura) 
        : Item("Pocao de Vida", "Recupera HP"), cura(quantidadeCura) {}

    void aplicar(Personagem* alvo) override {
        std::cout << "Usando " << nome << "...\n";
        alvo->receberCura(cura); 
    }
};

#endif