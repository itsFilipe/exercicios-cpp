/**
 * @file merge_sort.h
 * @brief Merge Sort — Método por Intercalação.
 *
 * Complexidade:
 *   - Melhor caso:  O(n log n)
 *   - Médio caso:   O(n log n)
 *   - Pior caso:    O(n log n)  — garante desempenho consistente
 *   - Espaço:       O(n)        — requer vetor auxiliar
 *
 * Características:
 *   - Estável: preserva a ordem relativa de elementos iguais.
 *   - Divide-and-conquer: divide o vetor ao meio recursivamente, depois intercala.
 *   - Previsível: complexidade idêntica nos três cenários (ótimo para sistemas críticos).
 *   - Base do Timsort (Python/Java), que combina Merge + Insertion Sort.
 *
 * Casos de uso embarcados / reais:
 *   - Ordenação de arquivos grandes em disco (merge externo).
 *   - Sistemas que exigem garantia de O(n log n) no pior caso.
 *   - Contagem de inversões em arrays (problema clássico de algoritmos).
 *   - Ordenação estável em sistemas de banco de dados.
 */

#pragma once

#include "sorting_metrics.h"
#include <vector>

/**
 * @brief Executa o Merge Sort sobre o vetor fornecido.
 * @param arr     Vetor de inteiros a ser ordenado (modificado in-place).
 * @param metrics Struct de saída com as métricas coletadas.
 */
void mergeSort(std::vector<int>& arr, SortMetrics& metrics);
