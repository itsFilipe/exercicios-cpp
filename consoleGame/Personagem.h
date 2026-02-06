#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <string>
#include <iostream>

class Personagem {
protected: // "Filhos" podem acessar essas variáveis
    std::string nome;
    int vida;
    int vidaMaxima;
    int danoBase;

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
    
    // Setter necessário para o Heroi aumentar vida na loja
    void aumentarVidaMaxima(int qtd);
    void aumentarDano(int qtd);
};

#endif