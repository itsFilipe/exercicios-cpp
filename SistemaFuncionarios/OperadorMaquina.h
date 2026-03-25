#include "Funcionario.h"

#include "Funcionario.h"

class OperadorMaquina : public Funcionario
{
private:
    std::string setor;
public:
    // We pass 'nm' and 'id' directly up to the Funcionario constructor
    OperadorMaquina(std::string nm, int id, std::string s)
        : Funcionario(nm, id), setor(s) {} 

    void apresentar(){ 
        std::cout << 
        "Trabalho como Operador de Maquina no Setor de " << setor << std::endl;
    }
};

