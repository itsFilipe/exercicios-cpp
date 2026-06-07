#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct Alerta {
    int id_maquina;
    std::string setor;
    int criticidade;
};

std::ostream& operator<<(std::ostream& os, const Alerta& alerta) {
    os << "ID: " << alerta.id_maquina << " | Setor: " << alerta.setor << " | Criticidade: " << alerta.criticidade;
    return os;
}

void print_alertas(const std::vector<Alerta>& a){
    for (const auto& alerta : a)
        std::cout << alerta << std::endl;
}

int main() {

    std::vector<Alerta> alertas = {
        {102, "Extrusao", 3},
        {105, "Usinagem", 5},
        {101, "Trefilacao", 3},
        {108, "Embalagem", 1},
        {104, "Forno", 5}
    };

    std::sort(alertas.begin(), alertas.end(), [](const Alerta &a, const Alerta &b) {
        if (a.criticidade != b.criticidade)
            return a.criticidade > b.criticidade;

        return a.id_maquina < b.id_maquina;
    });

    print_alertas(alertas);
    
    return 0;
}

/*
#include <iostream>
#include <map>
#include <string>

struct Alerta {
    int id_maquina;
    std::string processo;
    int criticidade;
};

// 1. Criamos uma estrutura para servir de chave composta
struct ChaveAlerta {
    int criticidade;
    int id_maquina;

    // 2. Operador '<' ensina o std::map a se auto-ordenar
    bool operator<(const ChaveAlerta& outra) const {
        if (criticidade != outra.criticidade) {
            return criticidade > outra.criticidade; // Maior criticidade primeiro
        }
        return id_maquina < outra.id_maquina;       // Menor ID segundo
    }
};

int main() {
    // 3. Inicializamos o map: a chave é a estrutura de ordenação, o valor é o processo
    std::map<ChaveAlerta, std::string> mapa_alertas = {
        {{3, 102}, "Extrusao"},
        {{5, 105}, "Usinagem"},
        {{3, 101}, "Trefilacao"},
        {{1, 108}, "Embalagem"},
        {{5, 104}, "Forno"}
    };

    // 4. Imprimindo os resultados (já saem ordenados!)
    for (const auto& [chave, processo] : mapa_alertas) {
        std::cout << "Criticidade: " << chave.criticidade 
                  << " | Maquina: " << chave.id_maquina 
                  << " | Processo: " << processo << "\n";
    }

    return 0;
}

*/