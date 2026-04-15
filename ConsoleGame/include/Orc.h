#ifndef ORC_H
#define ORC_H

#include "Inimigo.h"

class Orc : public Inimigo {
public:
    Orc(int round);
    void atacar(Personagem& alvo) override;
};

#endif
