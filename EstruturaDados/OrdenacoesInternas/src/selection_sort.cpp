/**
 * @file selection_sort.cpp
 * @brief Implementação do Selection Sort (Método por Seleção).
 *
 * O algoritmo:
 *   Para cada posição i (de 0 a n-2):
 *     - Encontra o índice do menor elemento no sub-vetor arr[i..n-1].
 *     - Troca arr[i] com esse menor elemento.
 *
 * Propriedade notável: realiza exatamente n-1 swaps no máximo,
 * independentemente do estado inicial do vetor. Isso o torna valioso
 * quando o custo de escrita é alto (e.g., memória EEPROM/flash).
 *
 * O número de comparações é sempre n*(n-1)/2, fixo para qualquer cenário.
 */

#include "selection_sort.h"
#include <chrono>

void selectionSort(std::vector<int>& arr, SortMetrics& metrics) {
    metrics.algorithm   = "Selection Sort";
    metrics.size        = static_cast<int>(arr.size());
    metrics.comparisons = 0;
    metrics.swaps       = 0;

    auto t_start = std::chrono::high_resolution_clock::now();

    int n = static_cast<int>(arr.size());

    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;  // assume que o menor está na posição atual

        // Busca o índice do menor elemento no sub-vetor restante
        for (int j = i + 1; j < n; ++j) {
            metrics.comparisons++;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        // Só faz swap se o menor não estiver já na posição correta
        if (min_idx != i) {
            std::swap(arr[i], arr[min_idx]);
            metrics.swaps++;
        }
    }

    auto t_end = std::chrono::high_resolution_clock::now();
    metrics.elapsed_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
}
