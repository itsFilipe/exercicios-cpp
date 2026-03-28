#ifndef _FUNCIONARIO_
#define _FUNCIONARIO_

#include <iostream>
#include <string>

class Funcionario
{
private:
    

protected:
    std::string nome;
    int id;
public:
    Funcionario(std::string nm, int id) : nome(nm), id(id) {}

    virtual ~Funcionario() {}
    
    // Método virtual que pode ser sobrescrito (override) nas classes filhas
    virtual void apresentar() { 
        std::cout << "Ola, meu nome e " << nome << " e meu id e " << id << std::endl;
    }

    // Novos métodos virtuais adicionados para didática
    virtual void trabalhar() {
        std::cout << "[Funcionario] " << nome << " esta realizando suas tarefas diarias genéricas." << std::endl;
    }

    virtual void baterPonto() {
        std::cout << "[Relogio Ponto] Funcionario " << nome << " registrou o ponto." << std::endl;
    }
};

#endif