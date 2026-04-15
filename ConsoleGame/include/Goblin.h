#ifndef GOBLIN_H
#define GOBLIN_H

#include "Inimigo.h"

class Goblin : public Inimigo {
public:
    Goblin(int round);
    void atacar(Personagem& alvo) override;
};

#endif
