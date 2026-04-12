#include "Vampiro.h"
#include <iostream>

// Construtor: Chama o Inimigo, que chama o Personagem
Vampiro::Vampiro(int nivel) 
    : Inimigo("Conde Drac", 60 + (nivel*10), 10 + (nivel*2)) {}

void Vampiro::atacar(Personagem &alvo) {
    // 1. Calcula dano
    int dano = (danoBase / 2) + (rand() % (danoBase / 2 + 1));
    
    // 2. Aplica dano
    alvo.receberDano(dano);

    // 3. COMPORTAMENTO ÚNICO: Rouba Vida
    int cura = dano / 3; // Cura 33% do dano causado
    vida += cura;
    if(vida > vidaMaxima) vida = vidaMaxima;

    std::cout << "\033[31m" << nome << " MORDEU voce causando " << dano 
              << " e recuperou " << cura << " de vida!\033[0m\n";
}