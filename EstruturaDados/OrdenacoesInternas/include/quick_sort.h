/**
 * @file quick_sort.h
 * @brief Quick Sort — Método por Substituição/Troca (particionamento).
 *
 * Implementação com pivô mediana-de-três para mitigar o pior caso em
 * vetores já ordenados ou inversamente ordenados.
 *
 * Complexidade:
 *   - Melhor caso:  O(n log n)  — pivô sempre divide ao meio
 *   - Médio caso:   O(n log n)  — comportamento esperado com dados aleatórios
 *   - Pior caso:    O(n²)       — pivô sempre é o menor/maior (sem mediana-de-três)
 *   - Espaço:       O(log n)    — pilha de recursão (médio); O(n) no pior caso
 *
 * Características:
 *   - NÃO estável na forma canônica.
 *   - In-place: não requer vetor auxiliar de tamanho n.
 *   - Cache-friendly: acesso sequencial durante o particionamento.
 *   - Mediana-de-três: escolhe o pivô como a mediana entre primeiro, meio e último,
 *     reduzindo drasticamente a probabilidade do pior caso.
 *
 * Casos de uso embarcados / reais:
 *   - Biblioteca padrão C (qsort) e C++ (std::sort usa Introsort = Quick + Heap + Insertion).
 *   - Sistemas embarcados com suficiente RAM para a pilha de recursão.
 *   - Arquivos grandes onde desempenho médio é crítico.
 *   - NÃO recomendado onde garantia de pior caso é mandatória (use Merge/Heap Sort).
 */

#pragma once

#include "sorting_metrics.h"
#include <vector>

/**
 * @brief Executa o Quick Sort (mediana-de-três) sobre o vetor fornecido.
 * @param arr     Vetor de inteiros a ser ordenado (modificado in-place).
 * @param metrics Struct de saída com as métricas coletadas.
 */
void quickSort(std::vector<int>& arr, SortMetrics& metrics);
