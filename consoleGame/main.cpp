#include <iostream>
#include <cstdlib> 
#include <ctime>   
#include <limits>  
#include <string>  
#include "Lutador.h" 

// Função auxiliar para limpar tela cross-platform
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

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

            std::cout << "\n[1] Atacar  [2] Curar\nEscolha: ";
            int escolha;
            std::cin >> escolha;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

            if (escolha == 1) heroi.atacar(vilao);
            else if (escolha == 2) heroi.curar();
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
            heroi.receberBonus();
            round++;
        } else {
            std::cout << "\n=== FIM DE JOGO ===\n";
            std::cout << "Voce chegou ao Round " << round << "\n";
        }
    }
    return 0;
}