#ifndef _OPTREFILA_
#define _OPTREFILA_

#include "OperadorMaquina.h"

class OperadorTrefiladeira : public OperadorMaquina {
    private:
    double espFioMm;
    int veloMtsPmnt;

    public:
    OperadorTrefiladeira(std::string nm, int id, std::string s, double e, int v) 
        : OperadorMaquina(nm, id, s), espFioMm(e), veloMtsPmnt(v) {}
    //isso é uma lista de inicialização

    // Sobrescrevendo métodos da classe pai
    void apresentar() override {
        std::cout << "[Trefiladeira] Sou " << nome << ", Operador de Trefiladeira. Produzo fios com " << espFioMm << "mm espessura." << std::endl;
    }

    void trabalhar() override {
        std::cout << "[Trefiladeira] " << nome << " esta operando a maquina na velocidade de " << veloMtsPmnt << " m/min." << std::endl;
    }

    // Implementação dos métodos específicos da classe
    void ajustarTensao() {
        std::cout << "[Trefiladeira] " << nome << " ajustou a tensao da fieira para evitar quebra do fio." << std::endl;
    }

    void trocarFieira() {
        std::cout << "[Trefiladeira] " << nome << " realizou a troca da fieira para o calibre " << espFioMm << "mm." << std::endl;
    }
};

#endif