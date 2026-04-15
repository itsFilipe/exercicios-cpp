#ifndef HEROI_H
#define HEROI_H

#include <memory>
#include <vector>
#include <string>
#include <fstream> // Necessário para salvar arquivos
#include "Personagem.h"

// Forward declaration para evitar erro de include circular
class Item; 

class Heroi : public Personagem {
private:
    int mana;
    int manaMaxima;
    int ouro;
  
    std::vector<std::unique_ptr<Item>> inventario;

public:
    Heroi(std::string n);
    Heroi(std::string n, int v, int d, int m);
    ~Heroi(); // Destrutor para limpar memória dos itens!

    void atacar(Personagem &alvo) override;
    void desenharBarra() override;

    // Métodos Especiais
    void ataqueEspecial(Personagem &alvo);
    void drenarVida(Personagem &alvo);
    void restaurarMana(int quantidade);

    // Mana
    int getMana() const;
    int getManaMaxima() const;

    // Gestão de Inventário
    void adicionarItem(std::unique_ptr<Item> novoItem);
    void usarItem(int indice, Personagem* alvo);
    Item* getItemPtr(int indice) const;
    void mostrarInventario();
    int getTamanhoInventario() const;
    void limparInventario();
    std::vector<int> getInventarioIds() const;

    // Economia
    int getOuro() const { return ouro; }
    void ganharOuro(int qtd) { ouro += qtd; }
    void diminuirOuro(int qtd) { ouro -= qtd; }

    // --- SAVE / LOAD ---
    // Estes eram os métodos que faltavam no seu arquivo .h
    std::string serializarStats() const;
    void carregarStats(int v, int vm, int d, int m, int mm, int o);
};

#endif