/*
 * DEMO 01: Condição de Corrida (Race Condition)
 * Compile: g++ -std=c++17 -pthread -o demo1 01_condicao_de_corrida.cpp
 *
 * PARTE 1: sem mutex  -> resultado errado (race condition)
 * PARTE 2: com mutex  -> resultado sempre correto
 */
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>

int contador_sem_protecao = 0;
int contador_com_protecao = 0;
std::mutex mtx;

void incrementar_sem_mutex(int vezes) {
    for (int i = 0; i < vezes; i++)
        contador_sem_protecao++; // NAO atomico: LOAD, ADD, STORE -> race!
}

void incrementar_com_mutex(int vezes) {
    for (int i = 0; i < vezes; i++) {
        std::lock_guard<std::mutex> lock(mtx); // so uma thread por vez
        contador_com_protecao++;
    }
}

void sep(const std::string& t) {
    std::cout << "\n" << std::string(55,'=') << "\n  " << t << "\n" << std::string(55,'=') << "\n";
}

int main() {
    const int N = 10, INC = 100'000, ESP = N * INC;
    std::cout << "\n╔═════════════════════════════════════════════════════╗\n";
    std::cout <<   "║     DEMO 01: Condicao de Corrida vs. Mutex          ║\n";
    std::cout <<   "╚═════════════════════════════════════════════════════╝\n";
    std::cout << "\n  " << N << " threads x " << INC << " incrementos = " << ESP << " esperado\n";

    sep("PARTE 1: SEM MUTEX (Race Condition)");
    std::vector<std::thread> v1;
    for (int i = 0; i < N; i++) v1.emplace_back(incrementar_sem_mutex, INC);
    for (auto& t : v1) t.join();
    std::cout << "  Esperado : " << ESP << "\n";
    std::cout << "  Obtido   : " << contador_sem_protecao << "\n";
    std::cout << "  Perdidos : " << (ESP - contador_sem_protecao) << " incrementos!\n";
    std::cout << "  Execute de novo -> resultado diferente! Nao-deterministico.\n";

    sep("PARTE 2: COM MUTEX (Sincronizado)");
    std::vector<std::thread> v2;
    for (int i = 0; i < N; i++) v2.emplace_back(incrementar_com_mutex, INC);
    for (auto& t : v2) t.join();
    std::cout << "  Esperado : " << ESP << "\n";
    std::cout << "  Obtido   : " << contador_com_protecao << "\n";
    std::cout << (contador_com_protecao == ESP ? "  CORRETO! Mutex garantiu integridade.\n"
                                               : "  ERRO!\n");
    sep("LICAO");
    std::cout << "  Sem mutex: dado corrompido, nao-deterministico\n";
    std::cout << "  Com mutex: sempre correto\n";
    std::cout << "  REGRA: dados compartilhados entre threads SEMPRE precisam sync!\n\n";
    return 0;
}
