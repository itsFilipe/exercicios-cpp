#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
#include "Personagem.h" 

class Item {
protected:
    std::string nome;
    std::string descricao;

public:
    Item(std::string n, std::string desc) : nome(n), descricao(desc) {}
    virtual ~Item() {} 

    std::string getNome() const { return nome; }
    std::string getDescricao() const { return descricao; }

    virtual void aplicar(Personagem* alvo) = 0; 
};

#endif