#include <iostream>
#include <cstdlib> 
#include <ctime>   
#include <limits>  
#include <string>  
#include "Lutador.h" 

// Função auxiliar para limpar tela cross-platform
void limparTela();
void menuLoja(Lutador &l);

int main() {
    srand(time(0));

    std::string NomeJogador;
    std::cout << "Digite o nome do seu lutador: ";
    std::getline(std::cin, NomeJogador);
    
    Lutador heroi(NomeJogador, 150, 40, 150, 3);
    int round = 1;

    while(heroi.getVida() > 0) {
        std::string nomeVilao = "Vilao Nivel " + std::to_string(round);
        size_t vidaVilao = 80 + (round * 20);
        size_t danoVilao = 10 + (round * 5);
        
        Lutador vilao(nomeVilao, vidaVilao, danoVilao, vidaVilao);

        std::cout << "\n>>> ROUND " << round << " <<<\n";
        std::cout << "Pressione ENTER...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpeza inicial
        std::cin.get();

        while(vilao.getVida() > 0 && heroi.getVida() > 0) {
            limparTela();
            
            std::cout << "--- ROUND " << round << " ---\n";
            heroi.desenharBarra();
            vilao.desenharBarra();

            std::cout << "Faça sua jogada: \n";
            std::cout << "[1] Atacar  [2] Curar [3] Especiais\nEscolha: ";
            int escolha;
            std::cin >> escolha;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

            if (escolha == 1) heroi.atacar(vilao);
            else if (escolha == 2) heroi.curar();
            else if (escolha == 3) {
                std::cout << "Escolha Habilidade: [1] Ataque Pesado (30 MP) [2] Drenar Vida (50 MP)\n";
                int habilidade;
                std::cin >> habilidade;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

                if (habilidade == 1) heroi.ataqueEspecial(vilao);
                else if (habilidade == 2) heroi.drenarVida(vilao);
                else std::cout << "Habilidade inexistente.\n";
            }
            else std::cout << "Opcao invalida! Perdeu a vez.\n";

            if (vilao.getVida() == 0) {
                std::cout << "\nVOCE VENCEU O ROUND!\n";
                break; 
            }

            std::cout << "\nTurno do inimigo...\n";
            vilao.atacar(heroi);

            if (heroi.getVida() == 0) {
                std::cout << "\nVOCE MORREU!\n";
                break;
            }

            std::cout << "\n(Enter para continuar)";
            std::cin.get();
        }

        if (heroi.getVida() > 0) {
            heroi.ganharOuro((rand() % 50) + 20);
            std::cout << "\nVoce ganhou ouro! Total de Ouro: " << heroi.getOuro() << "\n";  
            round++;
        } else {
            std::cout << "\n=== FIM DE JOGO ===\n";
            std::cout << "Voce chegou ao Round " << round << "\n";
        }
    }
    return 0;
}

/*
Entre rounds, em vez de curar automático, abra um Menu de Loja:

--- LOJA DO GOBLIN ---

Seu Ouro: 120

[1] Poção de Vida (50 ouro)

[2] Afiar Espada (+5 Dano) (100 ouro)

[3] Armadura Nova (+10 Vida Max) (150 ouro)

[4] Sair e Lutar

Por que implementar? Adiciona profundidade estratégica. 
O jogador precisa gerenciar recursos escassos (Dinheiro vs Vida). 
*/

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void menuLoja(Lutador &l){
    std::cout << "--- LOJA DO GOBLIN ---\n";
    std::cout << "Seu ouro: " << l.getOuro() << "\n";
    std::cout << "[1] Poção de Vida (50 ouro)\n";
    std::cout << "[2] Afiar Espada (+5 Dano) (100 ouro)\n";
    std::cout << "[3] Armadura Nova (+10 Vida Max) (150 ouro)\n";
    std::cout << "[4] Sair e Lutar\n";
    std::cout << "Digite uma opcao: ";

    size_t op {0};
    std::cin >> op;

    do
    {
        switch (op)
        {
        case 1:     
            //comprar ouro
            break;

        case 2:
            //comprar dano
            break;

        case 3:
            //comprar vida
            break;  

        case 4:
            std::cout << "Saindo da loja...\n";
            break;
        
        default: 
            std::cout << "Opcao invalida\n";
            break;
        }
    } while (op != 4);
    
    





}