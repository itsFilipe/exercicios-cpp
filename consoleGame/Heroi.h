#ifndef HEROI_H
#define HEROI_H

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
    
    // O Inventário Real!
    std::vector<Item*> inventario;

public:
    Heroi(std::string n, int v, int d, int m);
    ~Heroi(); // Destrutor para limpar memória dos itens!

    void atacar(Personagem &alvo) override;
    void desenharBarra() override;

    // Métodos Especiais
    void ataqueEspecial(Personagem &alvo);
    void drenarVida(Personagem &alvo);

    // Gestão de Inventário
    void adicionarItem(Item* novoItem);
    void usarItem(int indice);
    void mostrarInventario();
    int getTamanhoInventario() const; 
    void limparInventario(); // <--- NOVO: Necessário para o Load

    // Economia
    int getOuro() const { return ouro; }
    void ganharOuro(int qtd) { ouro += qtd; }
    void diminuirOuro(int qtd) { ouro -= qtd; }

    // --- SAVE / LOAD ---
    // Estes eram os métodos que faltavam no seu arquivo .h
    std::string serializarStats(); 
    void carregarStats(int v, int vm, int d, int m, int mm, int o);
};

#endif