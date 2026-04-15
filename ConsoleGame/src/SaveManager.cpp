#include "SaveManager.h"
#include "ItemFactory.h"
#include <fstream>
#include <iostream>

void SaveManager::salvar(const Heroi& h, int round) {
    std::ofstream arquivo("savegame.txt");
    if (!arquivo.is_open()) {
        std::cout << "Erro ao abrir arquivo de save!\n";
        return;
    }

    arquivo << h.getNome() << "\n";
    arquivo << h.serializarStats() << "\n";
    arquivo << round << "\n";

    std::vector<int> ids = h.getInventarioIds();
    arquivo << ids.size() << "\n";
    for (int id : ids) arquivo << id << " ";
    arquivo << "\n";

    std::cout << "\n=== JOGO SALVO COM SUCESSO! ===\n";
}

bool SaveManager::carregar(Heroi& h, int& round) {
    std::ifstream arquivo("savegame.txt");
    if (!arquivo.is_open()) {
        std::cout << "Nenhum save encontrado.\n";
        return false;
    }

    std::string nome;
    int v, vm, d, m, mm, o, r, qtdItens;

    std::getline(arquivo, nome);
    arquivo >> v >> vm >> d >> m >> mm >> o;
    h.carregarStats(v, vm, d, m, mm, o);
    arquivo >> r;
    round = r;
    arquivo >> qtdItens;

    h.limparInventario();
    for (int i = 0; i < qtdItens; i++) {
        int idItem;
        arquivo >> idItem;
        auto item = criarItem(idItem);
        if (item) h.adicionarItem(std::move(item));
    }

    std::cout << "\n=== JOGO CARREGADO! (Round " << round << ") ===\n";
    return true;
}
