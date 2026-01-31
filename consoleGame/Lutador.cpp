#include "Lutador.h" 
#include <iostream>
#include <cstdlib> // Para rand()

// --- DEFINIÇÃO DE CORES (Códigos ANSI) ---
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

// Implementação do Construtor
Lutador::Lutador(std::string n, size_t v, size_t d, size_t vm, size_t pv, size_t m, size_t mm)
    : nome(n), vida(v), dano(d), vida_maxima(vm), pocao_vida(pv), mana(m), mana_maxima(mm) {}

// Implementação dos Getters
std::string Lutador::getNome() const { return nome; }
size_t Lutador::getVida() const { return vida; }
size_t Lutador::getDano() const { return dano; }
size_t Lutador::getVidaMaxima() const { return vida_maxima; }
size_t Lutador::getPocaoVida() const { return pocao_vida; }
size_t Lutador::getMana() const { return mana; }
size_t Lutador::getManaMaxima() const { return mana_maxima; }

// Ações
void Lutador::atacar(Lutador &l) {
    size_t dano_real = (dano / 2) + (rand() % (dano / 2 + 1));
    
    if (l.vida <= dano_real) {
        l.vida = 0;
    } else {
        l.vida -= dano_real;
    }

    // Cor Vermelha para ataque
    std::cout << RED << nome << " atacou " << l.nome 
              << " causando " << dano_real << " de dano." << RESET << "\n";

    l.mana += 10;

    // Cor Verde para Mana
    std::cout << GREEN << nome << " ganhou " << "10 de mana nesse ataque\n"
              << RESET << "\n";
}

void Lutador::curar() {
    if(vida == vida_maxima){
        std::cout << nome << " ja esta com vida maxima" << std::endl;
        return;
    } 

    if(pocao_vida == 0){
        std::cout << "As pocoes de cura acabaram" << std::endl;
        return;
    }

    size_t cura = (rand() % 30) + 10;
    if (vida + cura > vida_maxima) {
        vida = vida_maxima;
    } else {
        vida += cura;
    }

    // Cor Verde para cura
    std::cout << GREEN << nome << " curou " << cura << " pontos de vida. (" 
              << pocao_vida - 1 << " restando)" << RESET << "\n";
    pocao_vida -= 1;
}

void Lutador::receberBonus() {
    vida_maxima += 10;
    dano += 5;
    vida += 20;
    if(vida > vida_maxima) vida = vida_maxima;
    std::cout << BLUE << "\n[LEVEL UP] " << nome << " ficou mais forte!" << RESET << "\n";
}

void Lutador::ataqueEspecial(Lutador &l){
    size_t dano_real = dano + (rand() % (dano / 2 + 1)); //como aumento a chance de errar?
    
    if (l.vida <= dano_real) {
        l.vida = 0;
    } else {
        l.vida -= dano_real;
    }
    // Cor Vermelha para ataque
    std::cout << RED << nome << " usou o ataque especial " << l.nome 
              << " causando " << dano_real << " de dano." << RESET << "\n";
}

void Lutador::drenarVida(Lutador &l){
    size_t dano_real = (dano / 2) + (rand() % (dano / 2 + 1));
    
    if (l.vida <= dano_real) {
        l.vida = 0;
    } else {
        l.vida -= dano_real;
    }

    size_t cura = dano_real / 2;

    if (vida + cura > vida_maxima) {
        vida = vida_maxima;
    } else {
        vida += cura;
    }

    // Cor Vermelha para ataque
    std::cout << RED << nome << " atacou " << l.nome 
              << " causando " << dano_real << " de dano e aumentou sua vida em " << cura
              << RESET << "\n";
}

void Lutador::desenharBarra() {
    std::cout << nome << " HP [";
    
    size_t barras = (vida * 20) / vida_maxima;

    // Lógica da Cor da Barra (Dinâmica)
    if (barras < 5) std::cout << RED;      // Menos de 25%: Vermelho
    else if (barras < 10) std::cout << YELLOW; // Menos de 50%: Amarelo
    else std::cout << GREEN;               // Saudável: Verde

    for (size_t i = 0; i < barras; i++) std::cout << "#";
    for (size_t i = barras; i < 20; i++) std::cout << ".";

    std::cout << RESET << "] " << vida << "/" << vida_maxima
    << " MANA: " << mana << "/" << mana_maxima << "\n";
}
