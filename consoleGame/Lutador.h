#ifndef LUTADOR_H // Se não definido
#define LUTADOR_H // defina agora

#include <string> 
#include <iostream> 

class Lutador {
private:
    std::string nome;
    size_t vida;
    size_t dano;
    size_t vida_maxima;
    size_t pocao_vida;

public:
    // Construtor
    Lutador(std::string n, size_t v, size_t d, size_t vm = 0, size_t pv = 0);

    // Getters
    std::string getNome() const;
    size_t getVida() const;
    size_t getDano() const;
    size_t getVidaMaxima() const;
    size_t getPocaoVida() const;

    // Ações
    void atacar(Lutador &l);
    void curar();
    void receberBonus();
    void desenharBarra(); 
};

#endif // Fim do IF