#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>
#include <vector>
#include <functional>
#include <thread>
#include <chrono>

#include "Heroi.h"
#include "Inimigo.h"
#include "Vampiro.h"
#include "Orc.h"
#include "Goblin.h"
#include "Item.h"
#include "ItemFactory.h"
#include "SaveManager.h"

#define RESET  "\033[0m"
#define YELLOW "\033[33m"

// ---------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ---------------------------------------------------------------
// Shop
// ---------------------------------------------------------------

void menuLoja(Heroi& h) {
    bool sair = false;
    do {
        limparTela();
        std::cout << "=== LOJA ===\n";
        std::cout << "Ouro: " << h.getOuro() << "\n\n";
        std::cout << "[1] Pocao Pequena  (50g)   [2] Pocao Grande   (100g)\n";
        std::cout << "[3] Afiar Espada   (150g)  [4] Pocao Mana      (70g)\n";
        std::cout << "[5] Frasco Veneno   (80g)  [6] Sair\n";

        int op;
        std::cin >> op;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        auto comprar = [&](int custo, int idItem) {
            if (h.getOuro() >= custo) {
                h.diminuirOuro(custo);
                h.adicionarItem(criarItem(idItem));
            } else {
                std::cout << "Ouro insuficiente!\n";
                std::cout << "Pressione Enter para continuar...";
                std::cin.get();
            }
        };

        switch (op) {
            case 1: comprar(50,  1); break;
            case 2: comprar(100, 2); break;
            case 3:
                if (h.getOuro() >= 150) { h.diminuirOuro(150); h.aumentarDano(5); std::cout << "Espada afiada! +5 dano.\n"; }
                else { std::cout << "Ouro insuficiente!\n"; std::cout << "Pressione Enter..."; std::cin.get(); }
                break;
            case 4: comprar(70,  3); break;
            case 5: comprar(80,  4); break;
            case 6: sair = true;     break;
            default:
                std::cout << "Opcao invalida.\n";
                std::cout << "Pressione Enter para continuar...";
                std::cin.get();
        }
    } while (!sair);
}

// ---------------------------------------------------------------
// Main
// ---------------------------------------------------------------

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    std::cout << "--- RPG TERMINAL ---\n";
    std::cout << "[1] Novo Jogo\n[2] Carregar Jogo\nEscolha: ";
    int opInicial;
    std::cin >> opInicial;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string nomeJogador = "Viajante";
    int round = 1;

    if (opInicial == 1) {
        std::cout << "Digite o nome do heroi: ";
        std::getline(std::cin, nomeJogador);
    }

    Heroi heroi(nomeJogador);

    if (opInicial == 2) {
        if (!SaveManager::carregar(heroi, round)) {
            std::cout << "Iniciando novo jogo...\n";
            heroi.adicionarItem(criarItem(1));
        }
    } else {
        heroi.adicionarItem(criarItem(1));
        heroi.adicionarItem(criarItem(1));
    }

    // Loot chest pool — add new entries here alongside ItemFactory
    struct LootBau { std::string nome; std::function<void()> acao; };
    std::vector<LootBau> possiveisItens = {
        {"Pocao Grande",      [&]() { std::cout << "Uma Pocao Grande brilha no bau!\n";         heroi.adicionarItem(criarItem(2)); }},
        {"Pocao de Mana",     [&]() { std::cout << "Uma Pocao de Mana fumega no bau!\n";         heroi.adicionarItem(criarItem(3)); }},
        {"Frasco de Veneno",  [&]() { std::cout << "Um Frasco de Veneno verde esta no bau!\n";   heroi.adicionarItem(criarItem(4)); }},
    };

    // ---------------------------------------------------------------
    // Game loop
    // ---------------------------------------------------------------
    while (heroi.estaVivo()) {
        std::unique_ptr<Inimigo> vilao;

        int randomMonster = rand() % 100;
        if      (randomMonster < 20) vilao = std::make_unique<Vampiro>(round);
        else if (randomMonster < 60) vilao = std::make_unique<Orc>(round);
        else                         vilao = std::make_unique<Goblin>(round);

        std::cout << "\n>>> ROUND " << round << " <<<\n";
        std::cout << "Um " << vilao->getNome() << " apareceu!\n\n";

        std::cout << "O que deseja fazer?\n[1] Lutar  [2] Salvar Jogo  [3] Sair\n";
        int opMenu;
        std::cin >> opMenu;
        std::cin.ignore();

        if (opMenu == 2) {
            SaveManager::salvar(heroi, round);
            std::cout << "Pressione Enter para continuar...";
            std::cin.get();
        } else if (opMenu == 3) {
            std::cout << "Saindo...\n";
            break;
        }

        // -----------------------------------------------------------
        // Battle loop
        // -----------------------------------------------------------
        while (vilao->estaVivo() && heroi.estaVivo()) {
            limparTela();
            std::cout << "--- BATTLE ROUND " << round << " ---\n";
            heroi.desenharBarra();
            vilao->desenharBarra();
            std::cout << "\n";

            // Tick status effects (check stun BEFORE decrementing it)
            bool heroiAtordoado = heroi.estaAtordoado();
            heroi.tickEfeitos();
            vilao->tickEfeitos();

            if (!heroi.estaVivo() || !vilao->estaVivo()) break;

            // --- Player turn ---
            if (heroiAtordoado) {
                std::cout << YELLOW << "Voce esta atordoado! Perdeu o turno.\n" << RESET;
            } else {
                bool acaoValida = false;
                do {
                    std::cout << "\n[1] Atacar  [2] Mochila  [3] Habilidades\nEscolha: ";
                    int escolha;
                    std::cin >> escolha;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (escolha == 1) {
                        heroi.atacar(*vilao);
                        acaoValida = true;
                    } else if (escolha == 2) {
                        heroi.mostrarInventario();
                        std::cout << "Item (-1 voltar): ";
                        int idx; std::cin >> idx; std::cin.ignore();
                        if (idx != -1) {
                            Item* itemPtr = heroi.getItemPtr(idx);
                            if (itemPtr) {
                                // Offensive items target the enemy; others target self
                                Personagem* alvo = itemPtr->esOfensivo()
                                    ? static_cast<Personagem*>(vilao.get())
                                    : static_cast<Personagem*>(&heroi);
                                heroi.usarItem(idx, alvo);
                            }
                        }
                        acaoValida = true; // opening bag uses the turn
                    } else if (escolha == 3) {
                        std::cout << "[1] Golpe Esmagador (30mp)  [2] Drenar Vida (50mp): ";
                        int h; std::cin >> h; std::cin.ignore();
                        if      (h == 1) { heroi.ataqueEspecial(*vilao); acaoValida = true; }
                        else if (h == 2) { heroi.drenarVida(*vilao);     acaoValida = true; }
                        else             std::cout << "Opcao invalida.\n";
                    } else {
                        std::cout << "Opcao invalida.\n";
                    }
                } while (!acaoValida);
            }

            if (!vilao->estaVivo()) break;

            // --- Enemy turn ---
            std::cout << "\nInimigo ataca...\n";
            vilao->atacar(heroi);

            if (!heroi.estaVivo()) break;
            std::cout << "(Enter)"; std::cin.get();
        }

        // -----------------------------------------------------------
        // After battle
        // -----------------------------------------------------------
        if (heroi.estaVivo()) {
            std::cout << "\nVenceu! Loot...\n";
            heroi.ganharOuro(30);
            heroi.restaurarMana(20);
            std::cout << YELLOW << "(Mana +20 pos-batalha)\n" << RESET;

            // Magic chest (30% chance)
            if ((rand() % 100) < 30) {
                std::cout << "\n*** VOCE ENCONTROU UM BAU MAGICO! ***\n";
                std::cout << "Deseja abrir? (S - Sim) ";
                std::string escolha;
                std::cin >> escolha;

                if (!escolha.empty() && toupper(escolha[0]) == 'S') {
                    std::this_thread::sleep_for(std::chrono::milliseconds(800));
                    int sorteio = rand() % static_cast<int>(possiveisItens.size());
                    possiveisItens[sorteio].acao();
                } else {
                    std::cout << "Ok... siga seu caminho.\n";
                }
            }

            // Shop prompt
            bool inputValido = false;
            do {
                std::cout << "\nDeseja ir para a loja? (1 - Sim / 2 - Nao)\n";
                int opLoja;
                std::cin >> opLoja;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if      (opLoja == 1) { menuLoja(heroi); inputValido = true; }
                else if (opLoja == 2) { inputValido = true; }
                else    std::cout << "Opcao invalida.\n";
            } while (!inputValido);

            round++;
        }
    }

    std::cout << "\nFIM DE JOGO.\n";
    return 0;
}
