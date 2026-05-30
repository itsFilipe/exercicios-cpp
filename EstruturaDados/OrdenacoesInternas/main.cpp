/**
 * @file main.cpp
 * @brief Benchmark de algoritmos de ordenação interna.
 *
 * Testa 5 algoritmos em 3 cenários × 3 tamanhos de vetor:
 *   Algoritmos : Counting Sort, Insertion Sort, Merge Sort, Selection Sort, Quick Sort
 *   Cenários   : Aleatório, Ordenado, Inversamente Ordenado
 *   Tamanhos   : 5.000 | 10.000 | 50.000 elementos
 *
 * Saída:
 *   - Tabela formatada no terminal (stdout).
 *   - Arquivo CSV  → results/benchmark_results.csv  (para geração de gráficos)
 *
 * Compilação sugerida:
 *   g++ -O0 -std=c++17 -Iinclude src/*.cpp main.cpp -o benchmark
 *   (use -O0 para que o compilador não otimize a ordenação e os tempos sejam reais)
 *
 * @author  Benchmark de Ordenações Internas
 * @date    2026
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <random>
#include <numeric>    // std::iota
#include <algorithm>  // std::shuffle, std::reverse, std::is_sorted
#include <filesystem> // std::filesystem::create_directories (C++17)

#include "counting_sort.h"
#include "insertion_sort.h"
#include "merge_sort.h"
#include "selection_sort.h"
#include "quick_sort.h"
#include <functional>  // std::function

// ── Constantes de configuração ───────────────────────────────────────────────
namespace cfg {
    /// Tamanhos de vetor a serem testados
    const std::vector<int> SIZES = { 5'000, 10'000, 50'000 };

    /// Semente fixa para reprodutibilidade dos resultados
    constexpr unsigned SEED = 42;

    /// Diretório de saída para o CSV
    const std::string OUTPUT_DIR = "results";

    /// Nome do arquivo CSV
    const std::string CSV_FILE   = OUTPUT_DIR + "/benchmark_results.csv";
}

// ── Tipos ────────────────────────────────────────────────────────────────────
using SortFunction = void(*)(std::vector<int>&, SortMetrics&);

struct Algorithm {
    std::string  name;
    SortFunction fn;
};

// ── Geração de vetores ───────────────────────────────────────────────────────

/**
 * @brief Gera um vetor de inteiros aleatórios no intervalo [1, n].
 * @param n     Tamanho do vetor.
 * @param seed  Semente para o gerador (para reprodutibilidade).
 */
std::vector<int> generateRandom(int n, unsigned seed = cfg::SEED) {
    std::vector<int> arr(n);
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(1, n);
    for (int& v : arr) v = dist(rng);
    return arr;
}

/**
 * @brief Gera um vetor de inteiros já ordenados em ordem crescente [1..n].
 */
std::vector<int> generateSorted(int n) {
    std::vector<int> arr(n);
    std::iota(arr.begin(), arr.end(), 1);   // 1, 2, 3, ..., n
    return arr;
}

/**
 * @brief Gera um vetor de inteiros em ordem decrescente [n..1].
 */
std::vector<int> generateReverse(int n) {
    std::vector<int> arr(n);
    std::iota(arr.begin(), arr.end(), 1);
    std::reverse(arr.begin(), arr.end());   // n, n-1, ..., 1
    return arr;
}

// ── Impressão de resultados ──────────────────────────────────────────────────

/**
 * @brief Imprime o cabeçalho da tabela de resultados no terminal.
 */
void printHeader() {
    std::cout << "\n";
    std::cout << std::string(110, '=') << "\n";
    std::cout << std::left
              << std::setw(18) << "Algoritmo"
              << std::setw(12) << "Tamanho"
              << std::setw(22) << "Cenário"
              << std::setw(18) << "Tempo (ms)"
              << std::setw(22) << "Comparações"
              << std::setw(18) << "Swaps"
              << "\n";
    std::cout << std::string(110, '-') << "\n";
}

/**
 * @brief Imprime uma linha de resultado da tabela no terminal.
 */
void printRow(const SortMetrics& m) {
    std::cout << std::left
              << std::setw(18) << m.algorithm
              << std::setw(12) << m.size
              << std::setw(22) << m.scenario
              << std::setw(18) << std::fixed << std::setprecision(4) << m.elapsed_ms
              << std::setw(22) << m.comparisons
              << std::setw(18) << m.swaps
              << "\n";
}

/**
 * @brief Escreve o cabeçalho do CSV no arquivo de saída.
 */
void writeCsvHeader(std::ofstream& file) {
    file << "Algoritmo,Tamanho,Cenario,Tempo_ms,Comparacoes,Swaps\n";
}

/**
 * @brief Escreve uma linha de resultado no arquivo CSV.
 */
void writeCsvRow(std::ofstream& file, const SortMetrics& m) {
    file << m.algorithm << ","
         << m.size      << ","
         << m.scenario  << ","
         << std::fixed << std::setprecision(6) << m.elapsed_ms << ","
         << m.comparisons << ","
         << m.swaps       << "\n";
}

// ── Verificação de corretude ─────────────────────────────────────────────────

/**
 * @brief Verifica se o vetor está ordenado de forma não-decrescente.
 * @return true se ordenado corretamente, false caso contrário.
 */
bool isCorrectlySorted(const std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] < arr[i - 1]) return false;
    }
    return true;
}

// ── Runner de benchmark ──────────────────────────────────────────────────────

/**
 * @brief Executa o benchmark de um algoritmo em um cenário específico.
 *
 * @param algo     Struct com nome e ponteiro de função do algoritmo.
 * @param original Vetor original a ser copiado (não é modificado).
 * @param scenario Nome textual do cenário.
 * @param file     Stream do arquivo CSV de saída.
 */
void runBenchmark(const Algorithm& algo,
                  const std::vector<int>& original,
                  const std::string& scenario,
                  std::ofstream& file)
{
    std::vector<int> arr = original;   // cópia — cada algoritmo recebe um vetor igual

    SortMetrics metrics;
    metrics.scenario = scenario;

    algo.fn(arr, metrics);             // executa o algoritmo com coleta de métricas

    // Verifica corretude após a ordenação
    bool ok = isCorrectlySorted(arr);
    if (!ok) {
        std::cerr << "[ERRO] " << metrics.algorithm
                  << " não ordenou corretamente! (cenário: " << scenario
                  << ", tamanho: " << metrics.size << ")\n";
    }

    printRow(metrics);
    writeCsvRow(file, metrics);
}

// ── Main ─────────────────────────────────────────────────────────────────────
int main() {
    // Cria o diretório de resultados (C++17)
    std::filesystem::create_directories(cfg::OUTPUT_DIR);

    // Abre o arquivo CSV para escrita
    std::ofstream csv(cfg::CSV_FILE);
    if (!csv.is_open()) {
        std::cerr << "Erro ao criar o arquivo CSV: " << cfg::CSV_FILE << "\n";
        return 1;
    }
    writeCsvHeader(csv);

    // Lista de algoritmos na ordem da especificação
    std::vector<Algorithm> algorithms = {
        { "Counting Sort",  countingSort  },
        { "Insertion Sort", insertionSort },
        { "Merge Sort",     mergeSort     },
        { "Selection Sort", selectionSort },
        { "Quick Sort",     quickSort     },
    };

    // Lista de cenários: nome → função geradora
    using GenFunc = std::function<std::vector<int>(int)>;
    struct Scenario {
        std::string name;
        GenFunc     gen;
    };

    std::vector<Scenario> scenarios;
    scenarios.push_back({ "Aleatorio",     GenFunc([](int n){ return generateRandom(n);  }) });
    scenarios.push_back({ "Ordenado",      GenFunc([](int n){ return generateSorted(n);  }) });
    scenarios.push_back({ "Inv. Ordenado", GenFunc([](int n){ return generateReverse(n); }) });

    // ── Loop principal de benchmark ──────────────────────────────────────────
    std::cout << "\n╔══════════════════════════════════════════════════════╗\n";
    std::cout <<   "║   BENCHMARK DE ALGORITMOS DE ORDENAÇÃO INTERNA      ║\n";
    std::cout <<   "╚══════════════════════════════════════════════════════╝\n";
    std::cout << "Tamanhos testados: ";
    for (int s : cfg::SIZES) std::cout << s << "  ";
    std::cout << "\nArquivo CSV gerado em: " << cfg::CSV_FILE << "\n";

    for (int size : cfg::SIZES) {
        std::cout << "\n\n◆ Tamanho do vetor: " << size << "\n";
        printHeader();

        for (const auto& scenario : scenarios) {
            std::vector<int> base = scenario.gen(size);

            for (const auto& algo : algorithms) {
                runBenchmark(algo, base, scenario.name, csv);
            }
            std::cout << std::string(110, '-') << "\n";
        }
    }

    std::cout << "\n" << std::string(110, '=') << "\n";
    std::cout << "Benchmark concluído! Resultados salvos em: " << cfg::CSV_FILE << "\n\n";

    csv.close();
    return 0;
}
