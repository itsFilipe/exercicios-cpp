/**
 * @file selection_sort.h
 * @brief Selection Sort — Método por Seleção.
 *
 * Complexidade:
 *   - Melhor caso:  O(n²)   — mesmo com vetor ordenado, percorre tudo
 *   - Médio caso:   O(n²)
 *   - Pior caso:    O(n²)
 *   - Espaço:       O(1)    — in-place
 *
 * Características:
 *   - NÃO estável na forma canônica (trocas longas podem inverter iguais).
 *   - Número de swaps é O(n) — mínimo possível entre os quadráticos.
 *   - Número de comparações é sempre fixo: n(n-1)/2 (independe do cenário).
 *   - Não adaptive: não se beneficia de dados parcialmente ordenados.
 *
 * Casos de uso embarcados / reais:
 *   - Situações onde o custo de escrita/swap é alto (memória flash/EEPROM):
 *     o número mínimo de swaps reduz o desgaste do meio de armazenamento.
 *   - Memórias EEPROM em microcontroladores (AVR, PIC): ciclos de escrita limitados.
 *   - Vetores muito pequenos onde a simplicidade supera a eficiência.
 */

#pragma once

#include "sorting_metrics.h"
#include <vector>

/**
 * @brief Executa o Selection Sort sobre o vetor fornecido.
 * @param arr     Vetor de inteiros a ser ordenado (modificado in-place).
 * @param metrics Struct de saída com as métricas coletadas.
 */
void selectionSort(std::vector<int>& arr, SortMetrics& metrics);
