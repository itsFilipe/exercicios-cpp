#ifndef _ANALISTATI_
#define _ANALISTATI_

#include "Funcionario.h"

class AnalistaTi : public Funcionario {
    private:
    std::string linguagemPrincipal;
    bool temAcessoServidor;

    public:
    AnalistaTi(std::string nm, int id, std::string lp, bool t) 
        : Funcionario(nm, id), linguagemPrincipal(lp), temAcessoServidor(t) {}
    //isso é uma lista de inicialização

    void apresentar() override {
        std::cout << "[TI] Sou " << nome << ", Analista de TI, e programo em " << linguagemPrincipal << "." << std::endl;
    }

    // Sobrescrevendo a função trabalhar da classe base
    void trabalhar() override {
        std::cout << "[TI] " << nome << " esta desenvolvendo sistemas e corrigindo bugs em " << linguagemPrincipal << "." << std::endl;
    }

    // Implementação dos métodos específicos da classe
    void resolverChamado() {
        std::cout << "[TI] " << nome << " esta resolvendo um chamado no helpdesk (alguem esqueceu a senha de novo)." << std::endl;
    }

    void reiniciarSistema() {
        if(temAcessoServidor) {
            std::cout << "[TI] " << nome << " tem acesso root. Reiniciando o servidor principal..." << std::endl;
        } else {
            std::cout << "[TI] " << nome << " tentou reiniciar o servidor, mas acesso foi NEGADO." << std::endl;
        }
    }
};

#endif