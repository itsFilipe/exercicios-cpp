#ifndef HEROI_H
#define HEROI_H

#include "Personagem.h"

class Heroi : public Personagem {
private:
    int mana;
    int manaMaxima;
    int ouro;
    int pocoes;

public:
    Heroi(std::string n, int v, int d, int m);

    // Sobrescrita (Override)
    void atacar(Personagem &alvo) override;
    void desenharBarra() override;

    // Métodos Exclusivos
    void curar();
    void ataqueEspecial(Personagem &alvo);
    void drenarVida(Personagem &alvo);

    // Métodos de Economia (Para a Loja)
    int getOuro() const { return ouro; }
    void ganharOuro(int qtd) { ouro += qtd; }
    void diminuirOuro(int qtd) { ouro -= qtd; }
    int getPocaoVida() const { return pocoes; }
    void aumentarPocao() { pocoes++; }
};

#endif