#include "Personagem.h"
#include <cstdlib>

// Cores
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"

Personagem::Personagem(std::string n, int v, int d) 
    : nome(n), vida(v), vidaMaxima(v), danoBase(d) {}

std::string Personagem::getNome() const { return nome; }
int Personagem::getVida() const { return vida; }
int Personagem::getVidaMaxima() const { return vidaMaxima; }
int Personagem::getDano() const { return danoBase; }
bool Personagem::estaVivo() const { return vida > 0; }

void Personagem::atacar(Personagem &alvo) {
    // Lógica básica de dano
    int danoReal = (danoBase / 2) + (rand() % (danoBase / 2 + 1));
    
    std::cout << RED << nome << " atacou " << alvo.getNome() 
              << " causando " << danoReal << " de dano." << RESET << "\n";
              
    alvo.receberDano(danoReal);
}

void Personagem::receberDano(int dano) {
    if (vida <= dano) vida = 0;
    else vida -= dano;
}

void Personagem::desenharBarra() {
    std::cout << nome << " HP [";
    int barras = (vida * 20) / vidaMaxima;

    if (barras < 5) std::cout << RED;
    else if (barras < 10) std::cout << YELLOW;
    else std::cout << GREEN;

    for (int i = 0; i < barras; i++) std::cout << "#";
    for (int i = barras; i < 20; i++) std::cout << ".";

    std::cout << RESET << "] " << vida << "/" << vidaMaxima;
}

void Personagem::aumentarVidaMaxima(int qtd) { vidaMaxima += qtd; vida += qtd; }
void Personagem::aumentarDano(int qtd) { danoBase += qtd; }

void Personagem::receberCura(int quantidade) {
    vida += quantidade;
    if (vida > vidaMaxima) vida = vidaMaxima;
    std::cout << "\033[32m" << nome << " recuperou " << quantidade << " de vida!\033[0m\n";
}