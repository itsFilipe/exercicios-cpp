#include "Heroi.h"
#include <iostream>
#include <cstdlib>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

Heroi::Heroi(std::string n, int v, int d, int m) 
    : Personagem(n, v, d), mana(m), manaMaxima(m), ouro(0), pocoes(3) {}

void Heroi::atacar(Personagem &alvo) {
    // 1. Chama o ataque básico do Pai
    Personagem::atacar(alvo); 

    // 2. Adiciona a lógica de Mana (Exclusiva do Heroi)
    mana += 10;
    if(mana > manaMaxima) mana = manaMaxima;
    std::cout << BLUE << "(Mana +10) " << RESET;
}

void Heroi::desenharBarra() {
    // 1. O Pai desenha a vida
    Personagem::desenharBarra(); 
    
    // 2. O Filho desenha a mana ao lado
    std::cout << BLUE << " | MANA: " << mana << "/" << manaMaxima << RESET << "\n";
}

void Heroi::curar() {
    if(vida == vidaMaxima) {
        std::cout << "Vida cheia!\n";
        return;
    }
    if(pocoes <= 0) {
        std::cout << "Sem pocoes!\n";
        return;
    }

    int cura = (rand() % 30) + 10;
    if(vida + cura > vidaMaxima) vida = vidaMaxima;
    else vida += cura;

    pocoes--;
    std::cout << GREEN << nome << " usou pocao e curou " << cura << " HP. (" << pocoes << " restando)\n" << RESET;
}

void Heroi::ataqueEspecial(Personagem &alvo) {
    if (mana < 30) {
        std::cout << "Mana insuficiente (Precisa de 30)!\n";
        return;
    }
    mana -= 30;

    if ((rand() % 100) < 25) { // 25% de chance de erro
        std::cout << YELLOW << nome << " errou o ataque especial!\n" << RESET;
        return;
    }

    int danoReal = danoBase + (rand() % (danoBase / 2 + 1));
    std::cout << RED << "GOLPE ESMAGADOR! ";
    alvo.receberDano(danoReal);
    std::cout << "Causou " << danoReal << " de dano!\n" << RESET;
}

void Heroi::drenarVida(Personagem &alvo) {
    if (mana < 50) {
        std::cout << "Mana insuficiente (Precisa de 50)!\n";
        return;
    }
    mana -= 50;

    int danoReal = (danoBase / 2) + (rand() % (danoBase / 2 + 1));
    alvo.receberDano(danoReal);

    int cura = danoReal / 2;
    if(vida + cura > vidaMaxima) vida = vidaMaxima;
    else vida += cura;

    std::cout << RED << "Drenou vida! Dano: " << danoReal << GREEN << " | Cura: " << cura << "\n" << RESET;
}