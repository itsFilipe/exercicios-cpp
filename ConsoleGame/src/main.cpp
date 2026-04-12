#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>
#include <fstream>
#include <vector>

#include "Heroi.h" 
#include "Inimigo.h"
#include "Vampiro.h"
#include "Orc.h"
#include "Goblin.h"
#include "Item.h"
#include "PocaoVida.h" 
#include "PocaoMana.h"

void limparTela();
void menuLoja(Heroi &h); 
void salvarJogo(Heroi &h, int round);
bool carregarJogo(Heroi &h, int &round);

int main() {
    srand(time(0));

    std::cout << "--- RPG TERMINAL ---\n";
    std::cout << "[1] Novo Jogo\n[2] Carregar Jogo\nEscolha: ";
    int opInicial;
    std::cin >> opInicial;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string nomeJogador = "Viajante";
    int round = 1;
    bool carregou = false;

    if (opInicial == 1) {
        std::cout << "Digite o nome do heroi: ";
        std::getline(std::cin, nomeJogador);
    }
    
    Heroi heroi(nomeJogador);

    if (opInicial == 2) {
        if (carregarJogo(heroi, round)) {
            carregou = true;
        } else {
            std::cout << "Iniciando novo jogo...\n";
            heroi.adicionarItem(std::make_unique<PocaoVida>(1, "Pocao Pequena", "Recupera 50 HP", 50));
        }
    } else {
        heroi.adicionarItem(std::make_unique<PocaoVida>(1, "Pocao Pequena", "Recupera 50 HP", 50));
        heroi.adicionarItem(std::make_unique<PocaoVida>(1, "Pocao Pequena", "Recupera 50 HP", 50));
    }

    while(heroi.estaVivo()) { 
        std::unique_ptr<Inimigo> vilao;

        int randomMonster = rand() % 100;
        if (randomMonster < 20) {
            vilao = std::make_unique<Vampiro>(round);
        } else if (randomMonster < 60) {
            vilao = std::make_unique<Orc>(round);
        } else {
            vilao = std::make_unique<Goblin>(round);
        }

        std::cout << "\n>>> ROUND " << round << " <<<\n";
        std::cout << "Um " << vilao->getNome() << " apareceu!\n";

        std::cout << "O que deseja fazer?\n[1] Lutar  [2] Salvar Jogo  [3] Sair\n";
        int opMenu;
        std::cin >> opMenu;
        std::cin.ignore();

        if (opMenu == 2) {
            salvarJogo(heroi, round);
            std::cout << "Pressione Enter para continuar...";
            std::cin.get();
        } else if (opMenu == 3) {
            std::cout << "Saindo...\n";
            break; 
        }

        while(vilao->estaVivo() && heroi.estaVivo()) {
            limparTela();
            std::cout << "--- BATTLE ROUND " << round << " ---\n";
            heroi.desenharBarra(); 
            vilao->desenharBarra();

            bool isNotValid = true;

            do{
                std::cout << "\n[1] Atacar  [2] Mochila  [3] Habilidades\nEscolha: ";
                int escolha;
                std::cin >> escolha;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

                if (escolha == 1) {
                    heroi.atacar(*vilao); 
                    isNotValid = false;
                } else if (escolha == 2) {
                    heroi.mostrarInventario();
                    std::cout << "Item (-1 voltar): ";
                    int idx; std::cin >> idx; std::cin.ignore();
                    if(idx != -1) heroi.usarItem(idx);
                    isNotValid = false;
                }
                else if (escolha == 3) {
                    std::cout << "[1] Golpe (30mp) [2] Drenar (50mp): ";
                    int h; std::cin >> h; std::cin.ignore();
                    if(h==1) heroi.ataqueEspecial(*vilao);
                    else if(h==2) heroi.drenarVida(*vilao);
                    isNotValid = false;
                } else {
                    std::cout << "Opcao invalida.\n";
                }

                if (!vilao->estaVivo()) break;
                std::cout << "\nInimigo ataca...\n";
                vilao->atacar(heroi);
                if (!heroi.estaVivo()) break;
                std::cout << "(Enter)"; std::cin.get();

            } while(isNotValid);
        }

        if (heroi.estaVivo()) {
            std::cout << "Venceu! Loot...\n";
            heroi.ganharOuro(30);

            if ((rand() % 100) < 30) {
                std::cout << "\n*** VOCE ENCONTROU UM BAU MAGICO! ***\n";
                if ((rand() % 2) == 0) {
                    std::cout << "Dentro havia uma Pocao Grande!\n";
                    heroi.adicionarItem(std::make_unique<PocaoVida>(2, "Pocao Grande", "Recupera 100 HP", 100));
                } else {
                    std::cout << "Dentro havia uma Pocao de Mana!\n";
                    heroi.adicionarItem(std::make_unique<PocaoMana>(3, "Pocao Mana", "Recupera 30 MP", 30));
                }
            }

            bool isNotValid = true;
            int opLoja {0};

            do{
                std::cout << "Deseja ir para a loja? (1 - Sim / 2 - Nao)\n";
                std::cin >> opLoja;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if(opLoja == 1){
                    menuLoja(heroi);
                    isNotValid = false;
                } else if (opLoja == 2){
                    isNotValid = false;
                } else {
                    std::cout << "Opcao invalida, pense um pouco mais.\n";
                }
                    
            }while(isNotValid);

            round++;
        }
    }
    
    std::cout << "FIM DE JOGO.\n";
    return 0;
}

void menuLoja(Heroi &h) {
    bool sair = false;
    do {
        limparTela();
        std::cout << "=== LOJA ===\n";
        std::cout << "Ouro: " << h.getOuro() << "\n";
        std::cout << "[1] Pocao Pequena (50g)  [2] Pocao Grande (100g)\n";
        std::cout << "[3] Afiar Espada (150g)  [4] Pocao Mana (70g)\n";
        std::cout << "[5] Sair\n";
        
        int op;
        std::cin >> op;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if(op == 5) sair = true;
        else if(op == 1 && h.getOuro() >= 50) {
            h.diminuirOuro(50);
            h.adicionarItem(std::make_unique<PocaoVida>(1, "Pocao Pequena", "Recupera 50 HP", 50)); 
        }
        else if(op == 2 && h.getOuro() >= 100) {
            h.diminuirOuro(100);
            h.adicionarItem(std::make_unique<PocaoVida>(2, "Pocao Grande", "Recupera 100 HP", 100)); 
        }
        else if(op == 3 && h.getOuro() >= 150) {
            h.diminuirOuro(150);
            h.aumentarDano(5);
        } 
        else if(op == 4 && h.getOuro() >= 70) {
            h.diminuirOuro(70);
            h.adicionarItem(std::make_unique<PocaoMana>(3, "Pocao Mana", "Recupera 30 MP", 30));
        } else {
            std::cout << "Opcao invalida ou ouro insuficiente.\n";
            std::cout << "Pressione Enter para continuar...";
            std::cin.get();
        }
    } while(!sair);
}

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void salvarJogo(Heroi &h, int round) {
    std::ofstream arquivo("savegame.txt"); 
    
    if (arquivo.is_open()) {
        arquivo << h.getNome() << "\n";
        arquivo << h.serializarStats() << "\n";
        arquivo << round << "\n";
        
        std::vector<int> inventarioIds = h.getInventarioIds();
        arquivo << inventarioIds.size() << "\n";
        for (int id : inventarioIds) {
            arquivo << id << " ";
        }
        arquivo << "\n";
        
        std::cout << "\n=== JOGO SALVO COM SUCESSO! ===\n";
        arquivo.close();
    } else {
        std::cout << "Erro ao abrir arquivo de save!\n";
    }
}

bool carregarJogo(Heroi &h, int &round) {
    std::ifstream arquivo("savegame.txt"); 
    
    if (arquivo.is_open()) {
        std::string nome;
        int v, vm, d, m, mm, o, r, qtdItens;

        std::getline(arquivo, nome); 

        arquivo >> v >> vm >> d >> m >> mm >> o;
        h.carregarStats(v, vm, d, m, mm, o);

        arquivo >> r;
        round = r;

        arquivo >> qtdItens;
        h.limparInventario(); 
        
        for(int i=0; i < qtdItens; i++) {
            int idItem;
            arquivo >> idItem;
            if (idItem == 1) {
                h.adicionarItem(std::make_unique<PocaoVida>(1, "Pocao Pequena", "Recupera 50 HP", 50));
            } else if (idItem == 2) {
                h.adicionarItem(std::make_unique<PocaoVida>(2, "Pocao Grande", "Recupera 100 HP", 100));
            } else if (idItem == 3) {
                h.adicionarItem(std::make_unique<PocaoMana>(3, "Pocao Mana", "Recupera 30 MP", 30));
            }
        }

        std::cout << "\n=== JOGO CARREGADO! (Round " << round << ") ===\n";
        arquivo.close();
        return true;
    } else {
        std::cout << "Nenhum save encontrado.\n";
        return false;
    }
}