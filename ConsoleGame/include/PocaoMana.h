#ifndef POCAO_MANA_H
#define POCAO_MANA_H

#include "Item.h"
#include "Heroi.h"

class PocaoMana : public Item {
private:
    int recarga;

public:
    PocaoMana(int id, std::string nome, std::string desc, int quantidade) 
        : Item(id, nome, desc), recarga(quantidade) {}

    void aplicar(Personagem* alvo) override {
        Heroi* h = dynamic_cast<Heroi*>(alvo);
        if(h) {
            std::cout << "Usando " << nome << "...\n";
            h->restaurarMana(recarga);
        } else {
            std::cout << "Apenas herois podem usar isso!\n";
        }
    }
};

#endif
