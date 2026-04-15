#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <string>
#include <iostream>
#include <vector>
#include "StatusEffect.h"

class Personagem {
protected:
    std::string nome;
    int vida;
    int vidaMaxima;
    int danoBase;
    std::vector<StatusEffect> efeitos;

public:
    Personagem(std::string n, int v, int d);
    virtual ~Personagem() {} // Destrutor Virtual é obrigatório

    // Getters
    std::string getNome() const;
    int getVida() const;
    int getVidaMaxima() const;
    int getDano() const;
    bool estaVivo() const;

    // Métodos Virtuais (Polimorfismo)
    virtual void atacar(Personagem &alvo);
    virtual void receberDano(int dano);
    virtual void desenharBarra();
    
    void aumentarVidaMaxima(int qtd);
    void aumentarDano(int qtd);
    void receberCura(int quantidade);

    // Status effects
    void aplicarEfeito(StatusEffect e);
    void tickEfeitos();
    bool estaAtordoado() const;
};

#endif