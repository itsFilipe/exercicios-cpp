#ifndef _FUNCIONARIO_
#define _FUNCIONARIO_

#include <iostream>
#include <string>

class Funcionario
{
private:
    std::string nome;
    int id;
public:
    Funcionario(std::string nm, int id) : nome(nm), id(id) {}

    void apresentar(){ 
        std::cout << "Ola, meu nome e " << nome << " e meu id e " << id << std::endl;
    }
};

#endif