#include <iostream>
#include <cstdlib> // rand, srand, system
#include <ctime>   // time
#include <limits>  // numeric_limits
#include <string>  // to_string

// IMPORTANTE: Incluimos as classes novas
#include "Heroi.h" 
#include "Inimigo.h"

// Protótipos das funções auxiliares
void limparTela();
void menuLoja(Heroi &h); // Note que a loja recebe especificamente um Heroi

int main() {
    // 1. Inicializa o gerador de números aleatórios
    srand(time(0));

    // 2. Criação do Jogador
    std::string nomeJogador;
    std::cout << "Digite o nome do seu heroi: ";
    std::getline(std::cin, nomeJogador);
    
    // Instancia o Herói (Nome, Vida, Dano, Mana)
    Heroi heroi(nomeJogador, 150, 40, 100); 
    
    int round = 1;

    // --- LOOP PRINCIPAL DO JOGO (WAR LOOP) ---
    // O método 'estaVivo()' vem da classe base Personagem
    while(heroi.estaVivo()) { 
        
        // 3. Geração Aleatória de Inimigo
        std::string tipos[] = {"Orc", "Goblin", "Esqueleto", "Troll", "Fantasma", "Slime"};
        std::string adjetivos[] = {"Furioso", "Nojento", "Maldito", "Gigante", "Caolho", "Vingativo"};
        
        std::string nomeVilao = tipos[rand() % 6] + " " + adjetivos[rand() % 6] + " (Nvl " + std::to_string(round) + ")";
        
        // Escalonamento de dificuldade (Inimigos ficam mais fortes a cada round)
        int vidaVilao = 80 + (round * 20);
        int danoVilao = 10 + (round * 5);
        
        // Instancia um Inimigo
        Inimigo vilao(nomeVilao, vidaVilao, danoVilao);

        // Introdução da Batalha
        std::cout << "\n>>> ROUND " << round << " <<<\n";
        std::cout << "Um " << vilao.getNome() << " apareceu!\n";
        std::cout << "Pressione ENTER para lutar...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa buffer se tiver lixo
        std::cin.get(); // Espera Enter

        // --- LOOP DE BATALHA (BATTLE LOOP) ---
        while(vilao.estaVivo() && heroi.estaVivo()) {
            limparTela();
            
            // UI: Desenha as barras
            std::cout << "--- ROUND " << round << " ---\n";
            heroi.desenharBarra(); // Desenha Vida + Mana (Override do Heroi)
            vilao.desenharBarra(); // Desenha só Vida (Padrão do Personagem)

            // Turno do Jogador
            std::cout << "\nFaca sua jogada: \n";
            std::cout << "[1] Atacar  [2] Curar  [3] Habilidades\nEscolha: ";
            
            int escolha;
            std::cin >> escolha;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o Enter do buffer

            // Processa Escolha
            if (escolha == 1) {
                // POLIMORFISMO EM AÇÃO:
                // O método atacar pede um 'Personagem', e 'vilao' É UM 'Personagem'.
                heroi.atacar(vilao); 
            }
            else if (escolha == 2) {
                heroi.curar();
            }
            else if (escolha == 3) {
                std::cout << "Escolha Habilidade: [1] Golpe Pesado (30 MP) [2] Drenar Vida (50 MP)\nOpcao: ";
                int hab;
                std::cin >> hab;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (hab == 1) heroi.ataqueEspecial(vilao);
                else if (hab == 2) heroi.drenarVida(vilao);
                else std::cout << "Habilidade cancelada.\n";
            }
            else {
                std::cout << "Voce tropeçou e perdeu a vez!\n";
            }

            // Verifica Vitória Imediata
            if (!vilao.estaVivo()) {
                std::cout << "\n>>> VOCE VENCEU O INIMIGO! <<<\n";
                break; // Sai do loop de batalha
            }

            // Turno do Inimigo
            std::cout << "\nTurno do inimigo...\n";
            vilao.atacar(heroi); // Inimigo ataca Herói

            // Verifica Derrota Imediata
            if (!heroi.estaVivo()) {
                std::cout << "\n>>> VOCE FOI DERROTADO! <<<\n";
                break; // Sai do loop de batalha
            }

            std::cout << "\n(Pressione ENTER para proximo turno)";
            std::cin.get();
        }

        // --- PÓS-BATALHA ---
        if (heroi.estaVivo()) {
            // Recompensa
            int ouroGanho = (rand() % 50) + 20;
            heroi.ganharOuro(ouroGanho);
            std::cout << "\nVoce saqueou " << ouroGanho << " de ouro do monstro.\n";
            
            // Loja
            std::cout << "Pressione ENTER para visitar a loja...";
            std::cin.get();
            menuLoja(heroi);

            // Prepara próximo round
            round++;
        } else {
            // Fim de Jogo
            std::cout << "\n=============================\n";
            std::cout << " FIM DE JOGO\n";
            std::cout << " Heroi: " << heroi.getNome() << "\n";
            std::cout << " Alcancou o Round: " << round << "\n";
            std::cout << "=============================\n";
        }
    }
    return 0;
}

// Implementação da função Limpar Tela
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Implementação do Menu da Loja
void menuLoja(Heroi &h) {
    bool sair = false;
    do {
        limparTela();
        std::cout << "=== LOJA DO GOBLIN ===\n";
        std::cout << "Seu Ouro: " << h.getOuro() << "\n";
        std::cout << "Seus Stats: Vida Max " << h.getVidaMaxima() << " | Dano " << h.getDano() << "\n\n";
        
        std::cout << "[1] Pocao de Vida (50g)  - Atual: " << h.getPocaoVida() << "\n";
        std::cout << "[2] Afiar Espada  (100g) - +5 Dano\n";
        std::cout << "[3] Armadura Nova (150g) - +10 Vida Max\n";
        std::cout << "[4] Sair e Lutar\n";
        std::cout << "Escolha: ";

        int op;
        std::cin >> op;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (op) {
            case 1:
                if (h.getOuro() >= 50) {
                    h.diminuirOuro(50);
                    h.aumentarPocao();
                    std::cout << "Voce comprou uma Pocao!\n";
                } else std::cout << "Ouro insuficiente!\n";
                break;
            
            case 2:
                if (h.getOuro() >= 100) {
                    h.diminuirOuro(100);
                    // AumentarDano é um método da classe base Personagem, 
                    // mas como Heroi herda dela, funciona perfeitamente!
                    h.aumentarDano(5); 
                    std::cout << "Sua espada esta mais afiada!\n";
                } else std::cout << "Ouro insuficiente!\n";
                break;

            case 3:
                if (h.getOuro() >= 150) {
                    h.diminuirOuro(150);
                    // Mesma coisa aqui, método herdado de Personagem
                    h.aumentarVidaMaxima(10); 
                    std::cout << "Sua armadura brilha mais forte!\n";
                } else std::cout << "Ouro insuficiente!\n";
                break;

            case 4:
                sair = true;
                std::cout << "Voltando para a arena...\n";
                break;

            default:
                std::cout << "Opcao invalida!\n";
        }

        if(!sair) {
            std::cout << "(Enter para continuar na loja)";
            std::cin.get();
        }

    } while (!sair);
}