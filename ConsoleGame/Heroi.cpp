#include "Heroi.h"
#include "Item.h" 
#include <iostream>
#include <sstream> // Importante para o serializarStats

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BLUE    "\033[34m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"

Heroi::Heroi(std::string n, int v, int d, int m) 
    : Personagem(n, v, d), mana(m), manaMaxima(m), ouro(0) {
}

Heroi::~Heroi() {
    limparInventario();
}

void Heroi::atacar(Personagem &alvo) {
    Personagem::atacar(alvo); 
    mana += 10;
    if(mana > manaMaxima) mana = manaMaxima;
    std::cout << BLUE << "(Mana +10) " << RESET;
}

void Heroi::desenharBarra() {
    Personagem::desenharBarra(); 
    std::cout << BLUE << " | MANA: " << mana << "/" << manaMaxima << RESET << "\n";
}

void Heroi::ataqueEspecial(Personagem &alvo) {
    if (mana < 30) {
        std::cout << "Mana insuficiente (30)!\n";
        return;
    }
    mana -= 30;

    if ((rand() % 100) < 25) { 
        std::cout << YELLOW << nome << " errou o ataque especial!\n" << RESET;
        return;
    }

    int danoReal = (getDano() * 1.5) + (rand() % (getDano() / 2));
    std::cout << RED << "GOLPE ESMAGADOR! ";
    alvo.receberDano(danoReal);
    std::cout << "Causou " << danoReal << " de dano!\n" << RESET;
}

void Heroi::drenarVida(Personagem &alvo) {
    if (mana < 50) {
        std::cout << "Mana insuficiente (50)!\n";
        return;
    }
    mana -= 50;

    int danoReal = getDano(); 
    alvo.receberDano(danoReal);

    int cura = danoReal / 2;
    receberCura(cura); 

    std::cout << RED << "Drenou vida! Dano: " << danoReal << "\n" << RESET;
}

// --- SISTEMA DE INVENTÁRIO ---

void Heroi::adicionarItem(Item* novoItem) {
    inventario.push_back(novoItem);
    std::cout << "Item obtido: " << novoItem->getNome() << "!\n";
}

void Heroi::mostrarInventario() {
    std::cout << "--- MOCHILA ---\n";
    if (inventario.empty()) {
        std::cout << "(Vazia)\n";
        return;
    }
    for (size_t i = 0; i < inventario.size(); i++) {
        std::cout << "[" << i << "] " << inventario[i]->getNome() 
                  << " - " << inventario[i]->getDescricao() << "\n";
    }
}

void Heroi::usarItem(int indice) {
    if (indice < 0 || indice >= inventario.size()) {
        std::cout << "Item invalido!\n";
        return;
    }

    Item* item = inventario[indice];
    item->aplicar(this); 

    inventario.erase(inventario.begin() + indice);
    delete item;
}

int Heroi::getTamanhoInventario() const {
    return inventario.size();
}

void Heroi::limparInventario() {
    for (Item* item : inventario) {
        delete item;
    }
    inventario.clear();
}

// --- SISTEMA DE SAVE / LOAD ---

std::string Heroi::serializarStats() {
    std::stringstream ss;
    // Ordem: Vida VidaMax Dano Mana ManaMax Ouro
    ss << vida << " " << vidaMaxima << " " << getDano() << " " 
       << mana << " " << manaMaxima << " " << ouro;
    return ss.str();
}

void Heroi::carregarStats(int v, int vm, int d, int m, int mm, int o) {
    vida = v;
    vidaMaxima = vm;
    // Como danoBase é protected em Personagem, podemos alterar direto:
    danoBase = d; 
    mana = m;
    manaMaxima = mm;
    ouro = o;
}