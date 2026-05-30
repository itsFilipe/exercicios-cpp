/**
 * @file counting_sort.cpp
 * @brief Implementação do Counting Sort (Método por Distribuição).
 *
 * O algoritmo:
 *   1. Encontra min e max do vetor.
 *   2. Cria um vetor de contagem de tamanho (max - min + 1).
 *   3. Conta as ocorrências de cada valor.
 *   4. Reconstrói o vetor original a partir das contagens.
 *
 * Nota sobre métricas:
 *   - "comparisons" conta as iterações no vetor de contagem (fase de contagem e reconstrução).
 *   - "swaps" conta cada posicionamento de elemento no vetor final.
 */

#include "counting_sort.h"
#include <chrono>
#include <algorithm> // std::min_element, std::max_element

void countingSort(std::vector<int>& arr, SortMetrics& metrics) {
    metrics.algorithm   = "Counting Sort";
    metrics.size        = static_cast<int>(arr.size());
    metrics.comparisons = 0;
    metrics.swaps       = 0;

    if (arr.empty()) return;

    // ── Início da medição de tempo ───────────────────────────────────────────
    auto t_start = std::chrono::high_resolution_clock::now();

    // 1. Encontra o intervalo [min, max] do vetor
    int min_val = arr[0], max_val = arr[0];
    for (size_t i = 1; i < arr.size(); ++i) {
        metrics.comparisons++;        // comparação com min
        if (arr[i] < min_val) min_val = arr[i];
        metrics.comparisons++;        // comparação com max
        if (arr[i] > max_val) max_val = arr[i];
    }

    int range = max_val - min_val + 1;

    // 2. Vetor de contagem
    std::vector<int> count(range, 0);
    for (int val : arr) {
        count[val - min_val]++;
        metrics.comparisons++;        // acesso/indexação contabilizado como "distribuição"
    }

    // 3. Reconstrói o vetor original a partir das contagens
    int idx = 0;
    for (int i = 0; i < range; ++i) {
        metrics.comparisons++;        // iteração sobre o vetor de contagem
        while (count[i] > 0) {
            arr[idx++] = i + min_val;
            count[i]--;
            metrics.swaps++;          // cada posicionamento = um "swap" conceitual
        }
    }

    // ── Fim da medição de tempo ──────────────────────────────────────────────
    auto t_end = std::chrono::high_resolution_clock::now();
    metrics.elapsed_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
}
