#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
#include "Personagem.h" 

class Item {
protected:
    int id;
    std::string nome;
    std::string descricao;

public:
    Item(int i, std::string n, std::string desc) : id(i), nome(n), descricao(desc) {}
    virtual ~Item() {} 

    int getId() const { return id; }
    std::string getNome() const { return nome; }
    std::string getDescricao() const { return descricao; }

    virtual void aplicar(Personagem* alvo) = 0; 
};

#endif