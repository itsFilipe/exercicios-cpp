#ifndef INIMIGO_H
#define INIMIGO_H

#include "Personagem.h"

class Inimigo : public Personagem {
public:
    // Construtor apenas repassa os dados para o Pai
    Inimigo(std::string n, int v, int d);
};

#endif