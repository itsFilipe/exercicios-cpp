/**
 * @file insertion_sort.h
 * @brief Insertion Sort — Método por Inserção.
 *
 * Complexidade:
 *   - Melhor caso:  O(n)       — vetor já ordenado (apenas n-1 comparações)
 *   - Médio caso:   O(n²)
 *   - Pior caso:    O(n²)      — vetor inversamente ordenado
 *   - Espaço:       O(1)       — in-place
 *
 * Características:
 *   - Estável: preserva a ordem relativa de elementos iguais.
 *   - Adaptive: desempenho melhora proporcionalmente ao grau de ordenação prévia.
 *   - Online: pode ordenar um fluxo de dados elemento a elemento.
 *
 * Casos de uso embarcados / reais:
 *   - Vetores pequenos (< ~32 elementos): cache-friendly, baixo overhead.
 *   - Etapa final de híbridos como Timsort e Introsort.
 *   - Listas quase ordenadas em sistemas embarcados com RAM restrita.
 *   - Inserção em tempo real de novos elementos já em estrutura ordenada.
 */

#pragma once

#include "sorting_metrics.h"
#include <vector>

/**
 * @brief Executa o Insertion Sort sobre o vetor fornecido.
 * @param arr     Vetor de inteiros a ser ordenado (modificado in-place).
 * @param metrics Struct de saída com as métricas coletadas.
 */
void insertionSort(std::vector<int>& arr, SortMetrics& metrics);
