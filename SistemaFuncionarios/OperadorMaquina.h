#include "Funcionario.h"

class OperadorMaquina : public Funcionario
{
private:
    std::string setor;
public:
    OperadorMaquina(std::string nm, int id, std::string s)
        : nome(nm), id(id), setor(s) {}

    void apresentar(){ 
        std::cout << 
        "Trabalho como Operador de Maquina no Setor de " << setor << std::endl;
    }
    
};


//wtf am i doing, i dont know a lot of this yet, study!

