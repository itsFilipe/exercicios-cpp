#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>
#include <fstream>

#include "Heroi.h" 
#include "Inimigo.h"
#include "Vampiro.h"
#include "PocaoVida.h" // Incluir para poder criar poções na loja

void limparTela();
void menuLoja(Heroi &h); 
void salvarJogo(Heroi &h, int round);
bool carregarJogo(Heroi &h, int &round);

// --- MAIN ---

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

    // Herói padrão (será sobrescrito se carregar)
    if (opInicial == 1) {
        std::cout << "Digite o nome do heroi: ";
        std::getline(std::cin, nomeJogador);
    }
    
    Heroi heroi(nomeJogador, 150, 40, 100); 

    if (opInicial == 2) {
        if (carregarJogo(heroi, round)) {
            carregou = true;
        } else {
            std::cout << "Iniciando novo jogo...\n";
            heroi.adicionarItem(new PocaoVida(50));
        }
    } else {
        // Novo jogo ganha itens iniciais
        heroi.adicionarItem(new PocaoVida(50));
        heroi.adicionarItem(new PocaoVida(50));
    }

    // --- LOOP DO JOGO ---
    while(heroi.estaVivo()) { 
        // ... (Toda a lógica de criar inimigo que já fizemos) ...
        Personagem *vilao = nullptr;
        if ((rand() % 100) < 20) vilao = new Vampiro(round); 
        else {
             std::string tipos[] = {"Orc", "Goblin", "Troll", "Slime"};
             std::string nomeVilao = tipos[rand()%4] + " (Nvl " + std::to_string(round) + ")";
             vilao = new Inimigo(nomeVilao, 80 + (round * 20), 10 + (round * 5));
        }

        std::cout << "\n>>> ROUND " << round << " <<<\n";
        std::cout << "Um " << vilao->getNome() << " apareceu!\n";
        
        // MENU DE PREPARAÇÃO (Salvar antes de lutar)
        std::cout << "O que deseja fazer?\n[1] Lutar  [2] Salvar Jogo  [3] Sair\n";
        int opMenu;
        std::cin >> opMenu;
        std::cin.ignore();

        if (opMenu == 2) {
            salvarJogo(heroi, round);
            std::cout << "Pressione Enter para continuar...";
            std::cin.get();
        } else if (opMenu == 3) {
            delete vilao;
            break; // Sai do jogo
        }

        // --- BATTLE LOOP (Cópia do anterior) ---
        while(vilao->estaVivo() && heroi.estaVivo()) {
            limparTela();
            // ... (Lógica de desenhar barra e turnos igual ao anterior) ...
            std::cout << "--- BATTLE ROUND " << round << " ---\n";
            heroi.desenharBarra(); 
            vilao->desenharBarra();

            std::cout << "\n[1] Atacar  [2] Mochila  [3] Habilidades\nEscolha: ";
            int escolha;
            std::cin >> escolha;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

            if (escolha == 1) heroi.atacar(*vilao);
            else if (escolha == 2) {
                 heroi.mostrarInventario();
                 std::cout << "Item (-1 voltar): ";
                 int idx; std::cin >> idx; std::cin.ignore();
                 if(idx != -1) heroi.usarItem(idx);
            }
            else if (escolha == 3) {
                // ... menu habilidades ...
                 std::cout << "[1] Golpe (30mp) [2] Drenar (50mp): ";
                 int h; std::cin >> h; std::cin.ignore();
                 if(h==1) heroi.ataqueEspecial(*vilao);
                 else if(h==2) heroi.drenarVida(*vilao);
            }

            if (!vilao->estaVivo()) break;
            std::cout << "\nInimigo ataca...\n";
            vilao->atacar(heroi);
            if (!heroi.estaVivo()) break;
            std::cout << "(Enter)"; std::cin.get();
        }

        delete vilao;

        if (heroi.estaVivo()) {
            // ... (Lógica de Loot e Loja) ...
            std::cout << "Venceu! Loot...\n";
            heroi.ganharOuro(30);
            menuLoja(heroi);
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
        std::cout << "[3] Afiar Espada (150g)  [4] Sair\n";
        
        int op;
        std::cin >> op;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if(op == 4) sair = true;
        else if(op == 1 && h.getOuro() >= 50) {
            h.diminuirOuro(50);
            h.adicionarItem(new PocaoVida(50)); // Cria Objeto Dinâmico
        }
        else if(op == 2 && h.getOuro() >= 100) {
            h.diminuirOuro(100);
            h.adicionarItem(new PocaoVida(100)); // Poção mais forte!
        }
        else if(op == 3 && h.getOuro() >= 150) {
            h.diminuirOuro(150);
            h.aumentarDano(5);
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

// --- FUNÇÕES DE PERSISTÊNCIA ---

void salvarJogo(Heroi &h, int round) {
    std::ofstream arquivo("savegame.txt"); // Abre para ESCREVER
    
    if (arquivo.is_open()) {
        // 1. Dados Básicos
        arquivo << h.getNome() << "\n";
        arquivo << h.serializarStats() << "\n"; // Vida, Mana, Ouro...
        arquivo << round << "\n";
        
        // 2. Inventário
        // Precisamos salvar o ID dos itens. 
        // Vamos convencionar: 101 = PocaoVida, 102 = PocaoGrande (exemplo)
        // Precisamos varrer o vetor. Como ele é privado, vamos ter que
        // ou criar um getter do vetor ou fazer o Heroi salvar seus itens.
        // Para simplificar: Vamos salvar apenas QUANTAS poções ele tem
        // (Isso requer um loop na Main acessando algum método, mas vamos simplificar).
        
        // CORREÇÃO DE ARQUITETURA RÁPIDA:
        // O ideal é o Heroi salvar seus itens. Mas vamos salvar "Na bruta" aqui:
        // Vamos salvar apenas o número de itens por enquanto para testar a lógica
        arquivo << h.getTamanhoInventario() << "\n";
        
        // Como não temos acesso direto ao vetor aqui, vamos assumir que
        // todos os itens são "PocaoVida" por simplicidade neste passo.
        // Em um jogo real, Heroi.cpp deveria escrever linha por linha os IDs.
        
        std::cout << "\n=== JOGO SALVO COM SUCESSO! ===\n";
        arquivo.close();
    } else {
        std::cout << "Erro ao abrir arquivo de save!\n";
    }
}

bool carregarJogo(Heroi &h, int &round) {
    std::ifstream arquivo("savegame.txt"); // Abre para LER
    
    if (arquivo.is_open()) {
        std::string nome;
        int v, vm, d, m, mm, o, r, qtdItens;

        // 1. Lê o Nome (Ignora porque o nome já foi setado no inicio, ou sobrescreve)
        std::getline(arquivo, nome); // Pula linha do nome ou usa se quiser

        // 2. Lê os Stats
        arquivo >> v >> vm >> d >> m >> mm >> o;
        h.carregarStats(v, vm, d, m, mm, o);

        // 3. Lê o Round
        arquivo >> r;
        round = r;

        // 4. Lê o Inventário
        arquivo >> qtdItens;
        h.limparInventario(); // Esvazia mochila atual
        
        // Recria os itens (Assumindo que tudo é Poção Vida por enquanto)
        for(int i=0; i < qtdItens; i++) {
            h.adicionarItem(new PocaoVida(50));
        }

        std::cout << "\n=== JOGO CARREGADO! (Round " << round << ") ===\n";
        arquivo.close();
        return true;
    } else {
        std::cout << "Nenhum save encontrado.\n";
        return false;
    }
}