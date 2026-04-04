#ifndef VAMPIRO_H
#define VAMPIRO_H

#include "Inimigo.h"

class Vampiro : public Inimigo {
public:
    Vampiro(int nivel); // Construtor baseado no round
    
    // A MÁGICA: Vamos sobrescrever o ataque!
    void atacar(Personagem &alvo) override;
};

#endif