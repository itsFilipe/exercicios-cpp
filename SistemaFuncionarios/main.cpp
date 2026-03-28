#include <iostream>
#include <vector> // Importante para usar a lista (std::vector)
#include "Funcionario.h"
#include "OperadorMaquina.h"
#include "AnalistaTi.h"
#include "AssistenteAdministrativo.h"
#include "OperadorTrefiladeira.h"

int main(){
    // 1. Criamos os nossos objetos normalmente
    Funcionario f1("Filipe", 123);
    OperadorMaquina op1("Joao", 789, "Montagem");
    AnalistaTi at1("Leo", 100, "Java", true);
    AssistenteAdministrativo aa1("Victor", 200, "estanhagem", 10);
    OperadorTrefiladeira ot1("Carlos", 300, "Trefilagem", 0.5, 100);

    // Demonstração 1: Usando métodos específicos diretamente nos objetos (Sem polimorfismo)
    std::cout << "--- 1. DEMONSTRANDO METODOS ESPECIFICOS DIRETOS ---" << std::endl;
    at1.resolverChamado();
    aa1.gerarRelatorio();
    op1.fazerManutencao();
    ot1.trocarFieira();
    std::cout << std::endl;

    // 2. Criamos a lista que aceita APENAS ponteiros de Funcionario
    std::vector<Funcionario*> listaDaFabrica;

    // 3. Colocamos os endereços (&) de todos os objetos na lista
    listaDaFabrica.push_back(&f1);
    listaDaFabrica.push_back(&op1);
    listaDaFabrica.push_back(&at1);
    listaDaFabrica.push_back(&aa1);
    listaDaFabrica.push_back(&ot1);

    std::cout << "--- 2. CHAMADA GERAL DA FABRICA (POLIMORFISMO) ---" << std::endl;

    // 4. Um loop que passa por cada ponteiro na lista
    for (Funcionario* func : listaDaFabrica) {
        
        // ATENÇÃO AQUI: Como "func" é um ponteiro, usamos a setinha (->) em vez de ponto (.) para chamar a função!
        func->baterPonto(); // Chama método base
        func->apresentar(); // Chama a versão específica de cada classe (override)
        func->trabalhar();  // Chama a versão específica de cada classe (override)
        std::cout << "----------------------" << std::endl;
    }

    // Demonstração extra muito didática: Downcasting com dynamic_cast
    std::cout << "--- 3. TESTANDO dynamic_cast ---" << std::endl;
    std::cout << "Procurando Analistas de TI na lista base para acessar metodos especificos..." << std::endl;
    
    for (Funcionario* func : listaDaFabrica) {
        // Tenta converter o ponteiro genérico "Funcionario" de volta para o tipo específico "AnalistaTi"
        AnalistaTi* ti = dynamic_cast<AnalistaTi*>(func);
        
        // Se a conversão der certo (não for nulo), significa que o ponteiro apontava de fato para um Analista de TI!
        if (ti != nullptr) {
            std::cout << "Encontramos um Analista! Pedindo para reiniciar o sistema via ponteiro convertido:" << std::endl;
            ti->reiniciarSistema();
        }
    }

    return 0;
}