/**
 * @file merge_sort.cpp
 * @brief Implementação do Merge Sort (Método por Intercalação).
 *
 * O algoritmo divide-and-conquer:
 *   1. Divide recursivamente o vetor ao meio até ter sub-vetores de tamanho 1.
 *   2. Intercala (merge) os sub-vetores ordenados usando um buffer auxiliar.
 *
 * A fase de intercalação é onde todas as comparações e "trocas" ocorrem.
 * Cada cópia de elemento do buffer auxiliar de volta ao vetor original é
 * contada como swap.
 */

#include "merge_sort.h"
#include <chrono>
#include <vector>

// ── Função auxiliar: intercala dois sub-vetores ordenados ───────────────────
static void merge(std::vector<int>& arr,
                  int left, int mid, int right,
                  SortMetrics& metrics)
{
    // Copia as duas metades para buffers temporários
    std::vector<int> L(arr.begin() + left,  arr.begin() + mid  + 1);
    std::vector<int> R(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;

    // Intercala comparando os menores elementos de cada metade
    while (i < static_cast<int>(L.size()) && j < static_cast<int>(R.size())) {
        metrics.comparisons++;
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
        metrics.swaps++;              // cada posicionamento no vetor original
    }

    // Copia os elementos restantes de L (se houver)
    while (i < static_cast<int>(L.size())) {
        arr[k++] = L[i++];
        metrics.swaps++;
    }

    // Copia os elementos restantes de R (se houver)
    while (j < static_cast<int>(R.size())) {
        arr[k++] = R[j++];
        metrics.swaps++;
    }
}

// ── Função auxiliar: divisão recursiva ──────────────────────────────────────
static void mergeSortHelper(std::vector<int>& arr,
                             int left, int right,
                             SortMetrics& metrics)
{
    if (left >= right) return;       // caso base: sub-vetor de tamanho 0 ou 1

    int mid = left + (right - left) / 2;  // evita overflow de inteiro

    mergeSortHelper(arr, left,    mid,   metrics);  // ordena metade esquerda
    mergeSortHelper(arr, mid + 1, right, metrics);  // ordena metade direita
    merge(arr, left, mid, right, metrics);           // intercala as duas metades
}

// ── Interface pública ────────────────────────────────────────────────────────
void mergeSort(std::vector<int>& arr, SortMetrics& metrics) {
    metrics.algorithm   = "Merge Sort";
    metrics.size        = static_cast<int>(arr.size());
    metrics.comparisons = 0;
    metrics.swaps       = 0;

    if (arr.empty()) return;

    auto t_start = std::chrono::high_resolution_clock::now();

    mergeSortHelper(arr, 0, static_cast<int>(arr.size()) - 1, metrics);

    auto t_end = std::chrono::high_resolution_clock::now();
    metrics.elapsed_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
}
