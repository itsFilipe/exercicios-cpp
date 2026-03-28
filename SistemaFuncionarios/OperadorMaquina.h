#ifndef _OPMAQUINA_
#define _OPMAQUINA_  

#include "Funcionario.h"

class OperadorMaquina : public Funcionario
{
private:
    std::string setor;
public:
    // We pass 'nm' and 'id' directly up to the Funcionario constructor
    OperadorMaquina(std::string nm, int id, std::string s)
        : Funcionario(nm, id), setor(s) {} 

    void apresentar() override { 
        std::cout << "[Fabrica] Ola, eu sou " << nome << " (ID: " << id << "). Trabalho como Operador de Maquina no Setor de " << setor << "." << std::endl;
    }

    void trabalhar() override {
        std::cout << "[Fabrica] " << nome << " esta operando as maquinas pesadas no setor de " << setor << "." << std::endl;
    }

    // Método específico da classe
    void fazerManutencao() {
        std::cout << "[Fabrica] " << nome << " esta realizando a manutencao preventiva da maquina." << std::endl;
    }
};

#endif