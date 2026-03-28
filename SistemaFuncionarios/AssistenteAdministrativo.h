#ifndef _ASSISADMIN_
#define _ASSISADMIN_

#include "Funcionario.h"

class AssistenteAdministrativo : public Funcionario {
    private:
    std::string setorALocado;
    int nivelAcesso;

    public:
    AssistenteAdministrativo(std::string nm, int id, std::string sa, int na) 
        : Funcionario(nm, id), setorALocado(sa), nivelAcesso(na) {}
    //isso é uma lista de inicialização

    // Sobrescrevendo métodos da classe base Funcionario
    void apresentar() override {
        std::cout << "[Admin] Sou " << nome << ", Assistente Administrativo do setor de " << setorALocado << "." << std::endl;
    }

    void trabalhar() override {
        std::cout << "[Admin] " << nome << " esta cuidando das rotinas administrativas do setor " << setorALocado << "." << std::endl;
    }

    // Implementação dos métodos específicos da classe
    void gerarRelatorio() {
        std::cout << "[Admin] " << nome << " gerou um relatorio gerencial com nivel de acesso " << nivelAcesso << "." << std::endl;
    }

    void organizarDocumentos() {
        std::cout << "[Admin] " << nome << " esta arquivando e organizando a papelada." << std::endl;
    }
};

#endif