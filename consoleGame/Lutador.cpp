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
Lutador::Lutador(std::string n, size_t v, size_t d, size_t vm, size_t pv, size_t m, size_t mm, size_t o)
    : nome(n), vida(v), dano(d), vida_maxima(vm), pocao_vida(pv), mana(m), mana_maxima(mm), ouro(o) {}

// Implementação dos Getters
std::string Lutador::getNome() const { return nome; }
size_t Lutador::getVida() const { return vida; }
size_t Lutador::getDano() const { return dano; }
size_t Lutador::getVidaMaxima() const { return vida_maxima; }
size_t Lutador::getPocaoVida() const { return pocao_vida; }
size_t Lutador::getMana() const { return mana; }
size_t Lutador::getManaMaxima() const { return mana_maxima; }
size_t Lutador::getOuro() const { return ouro; }

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

void Lutador::ataqueEspecial(Lutador &l) {
    // 1. Custo e Verificação
    if (mana < 30) {
        std::cout << "Mana insuficiente para Ataque Pesado!\n";
        return;
    }
    
    // 2. Gastar a Mana (MUITO IMPORTANTE)
    mana -= 30;

    // 3. Chance de Errar (RNG)
    // Gera número de 0 a 99. Se for menor que 25 (0 a 24), errou.
    if ((rand() % 100) < 25) { 
        std::cout << YELLOW << nome << " tentou um golpe pesado, escorregou e ERROU feio!" << RESET << "\n";
        return; // Sai da função, não causa dano
    }

    // Se passou pelo if acima, acertou!
    size_t dano_real = dano + (rand() % (dano / 2 + 1)); 
    
    if (l.vida <= dano_real) {
        l.vida = 0;
    } else {
        l.vida -= dano_real;
    }

    std::cout << RED << nome << " ACERTOU UM GOLPE DEVASTADOR em " << l.nome 
              << " causando " << dano_real << " de dano!" << RESET << "\n";
}

void Lutador::drenarVida(Lutador &l) {
    // Vamos definir que esse custa mais caro, ex: 50
    if (mana < 50) {
        std::cout << "Mana insuficiente para Drenar Vida (Precisa de 50)!\n";
        return;
    }

    mana -= 50; // Desconta a mana

    // Dano um pouco menor que o ataque normal, pois cura
    size_t dano_real = (dano / 2) + (rand() % (dano / 2 + 1));
    
    if (l.vida <= dano_real) l.vida = 0;
    else l.vida -= dano_real;

    size_t cura = dano_real / 2; // Cura metade do dano causado

    if (vida + cura > vida_maxima) vida = vida_maxima;
    else vida += cura;

    std::cout << RED << nome << " drenou a energia vital de " << l.nome 
              << "! (Dano: " << dano_real << " | " << GREEN << "Cura: +" << cura << RESET << ")\n";
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

void Lutador::ganharOuro(size_t quantidade) {
    ouro += quantidade;
}