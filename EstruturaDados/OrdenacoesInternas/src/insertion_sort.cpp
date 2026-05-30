/**
 * @file insertion_sort.cpp
 * @brief Implementação do Insertion Sort (Método por Inserção).
 *
 * O algoritmo:
 *   Para cada elemento i (da posição 1 até n-1):
 *     - Armazena arr[i] como "chave".
 *     - Desloca para a direita todos os elementos arr[j] > chave (j < i).
 *     - Insere a chave na posição correta.
 *
 * O deslocamento (shift) é contado como swap pois move um elemento por posição.
 * No vetor já ordenado, nenhum deslocamento ocorre → O(n) comparações, 0 swaps.
 */

#include "insertion_sort.h"
#include <chrono>

void insertionSort(std::vector<int>& arr, SortMetrics& metrics) {
    metrics.algorithm   = "Insertion Sort";
    metrics.size        = static_cast<int>(arr.size());
    metrics.comparisons = 0;
    metrics.swaps       = 0;

    auto t_start = std::chrono::high_resolution_clock::now();

    int n = static_cast<int>(arr.size());

    for (int i = 1; i < n; ++i) {
        int key = arr[i];   // elemento a ser inserido na posição correta
        int j   = i - 1;

        // Desloca elementos maiores que 'key' uma posição à frente
        while (j >= 0 && arr[j] > key) {
            metrics.comparisons++;    // comparação arr[j] > key
            arr[j + 1] = arr[j];     // deslocamento (shift) = swap conceitual
            metrics.swaps++;
            j--;
        }

        // Contabiliza a comparação que falhou (saída do while por arr[j] <= key)
        if (j >= 0) metrics.comparisons++;

        arr[j + 1] = key;            // insere a chave na posição correta
    }

    auto t_end = std::chrono::high_resolution_clock::now();
    metrics.elapsed_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
}
