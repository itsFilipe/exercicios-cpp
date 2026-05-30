/**
 * @file counting_sort.h
 * @brief Counting Sort — Método por Distribuição.
 *
 * Complexidade:
 *   - Melhor caso:  O(n + k)
 *   - Médio caso:   O(n + k)
 *   - Pior caso:    O(n + k)
 *   - Espaço:       O(k)   onde k = (max - min + 1)
 *
 * Características:
 *   - Algoritmo NÃO baseado em comparações — por isso escapa do limite O(n log n).
 *   - Estável: preserva a ordem relativa de elementos iguais.
 *   - Adequado apenas para inteiros (ou valores mapeáveis a inteiros) em faixa limitada.
 *
 * Casos de uso embarcados / reais:
 *   - Ordenação de notas, idades, prioridades (domínio pequeno e conhecido).
 *   - Etapa interna do Radix Sort.
 *   - Contadores de frequência em DSP/telecomunicações.
 */

#pragma once

#include "sorting_metrics.h"
#include <vector>
#include <algorithm>

/**
 * @brief Executa o Counting Sort sobre o vetor fornecido.
 *
 * Como o Counting Sort não realiza comparações elemento-a-elemento nem trocas
 * diretas entre elementos do vetor original, as métricas de comparação e swap
 * refletem, respectivamente:
 *   - comparisons: iterações sobre o vetor de contagem (proporcional a k).
 *   - swaps:       posicionamentos de elementos no vetor de saída (proporcional a n).
 *
 * @param arr    Vetor de inteiros a ser ordenado (modificado in-place).
 * @param metrics Struct de saída com as métricas coletadas.
 */
void countingSort(std::vector<int>& arr, SortMetrics& metrics);
