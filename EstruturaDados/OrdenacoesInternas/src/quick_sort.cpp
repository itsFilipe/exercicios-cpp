/**
 * @file quick_sort.cpp
 * @brief Implementação do Quick Sort com pivô mediana-de-três (Método por Troca).
 *
 * Estratégia de pivô — Mediana de Três:
 *   O pivô é escolhido como a mediana entre arr[left], arr[mid] e arr[right].
 *   Isso reduz a probabilidade do pior caso O(n²): no vetor já ordenado, o pivô
 *   será sempre o elemento central, gerando partições equilibradas O(n log n).
 *
 * Particionamento utilizado: Lomuto com pivô = arr[right].
 *   A mediana-de-três ordena os três extremos e coloca a mediana em arr[right],
 *   garantindo que arr[left] <= arr[right] <= arr[right] antes do particionamento.
 *
 * Por que pode ser O(n²) sem mediana-de-três?
 *   Com pivô = último elemento e vetor já ordenado, cada partição resulta em
 *   0 | n-1 elementos → n níveis de recursão com n comparações cada → O(n²).
 */

#include "quick_sort.h"
#include <chrono>
#include <algorithm>  // std::swap

// ── Coloca a mediana de arr[left], arr[mid], arr[right] em arr[right] ────────
// Após essa função: arr[left] <= arr[right] (mediana está no pivô)
static void medianOfThreePivot(std::vector<int>& arr,
                                int left, int right,
                                SortMetrics& metrics)
{
    int mid = left + (right - left) / 2;

    // Garante arr[left] <= arr[mid]
    metrics.comparisons++;
    if (arr[left] > arr[mid]) { std::swap(arr[left], arr[mid]); metrics.swaps++; }

    // Garante arr[left] <= arr[right]
    metrics.comparisons++;
    if (arr[left] > arr[right]) { std::swap(arr[left], arr[right]); metrics.swaps++; }

    // Garante arr[mid] <= arr[right]  →  mediana está em arr[mid]
    metrics.comparisons++;
    if (arr[mid] > arr[right]) { std::swap(arr[mid], arr[right]); metrics.swaps++; }

    // Após os três passos acima:  arr[left] <= arr[mid] <= arr[right]
    // A mediana é arr[mid]. Coloca-a em arr[right] para ser o pivô do Lomuto.
    std::swap(arr[mid], arr[right]);
    metrics.swaps++;
    // Agora arr[right] = mediana  e  arr[left] <= arr[right]
}

// ── Particionamento de Lomuto ────────────────────────────────────────────────
// Usa arr[right] como pivô. Retorna o índice final do pivô.
static int partition(std::vector<int>& arr,
                     int left, int right,
                     SortMetrics& metrics)
{
    if (right - left >= 2) {
        medianOfThreePivot(arr, left, right, metrics);
    }
    // arr[right] é agora o pivô (mediana ou simplesmente arr[right] para n<3)

    int pivot = arr[right];
    int i     = left - 1;  // último índice com elemento <= pivô

    for (int j = left; j < right; ++j) {
        metrics.comparisons++;
        if (arr[j] <= pivot) {
            ++i;
            if (i != j) { std::swap(arr[i], arr[j]); metrics.swaps++; }
        }
    }

    // Posiciona o pivô entre os elementos menores e maiores
    int pivot_pos = i + 1;
    if (pivot_pos != right) { std::swap(arr[pivot_pos], arr[right]); metrics.swaps++; }

    return pivot_pos;
}

// ── Recursão principal ───────────────────────────────────────────────────────
static void quickSortHelper(std::vector<int>& arr,
                             int left, int right,
                             SortMetrics& metrics)
{
    if (left >= right) return;

    int pivot_pos = partition(arr, left, right, metrics);

    // Processa a partição menor primeiro → limita a profundidade máxima da pilha
    if ((pivot_pos - left) < (right - pivot_pos)) {
        quickSortHelper(arr, left,          pivot_pos - 1, metrics);
        quickSortHelper(arr, pivot_pos + 1, right,         metrics);
    } else {
        quickSortHelper(arr, pivot_pos + 1, right,         metrics);
        quickSortHelper(arr, left,          pivot_pos - 1, metrics);
    }
}

// ── Interface pública ────────────────────────────────────────────────────────
void quickSort(std::vector<int>& arr, SortMetrics& metrics) {
    metrics.algorithm   = "Quick Sort";
    metrics.size        = static_cast<int>(arr.size());
    metrics.comparisons = 0;
    metrics.swaps       = 0;

    if (arr.size() <= 1) return;

    auto t_start = std::chrono::high_resolution_clock::now();

    quickSortHelper(arr, 0, static_cast<int>(arr.size()) - 1, metrics);

    auto t_end = std::chrono::high_resolution_clock::now();
    metrics.elapsed_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
}

