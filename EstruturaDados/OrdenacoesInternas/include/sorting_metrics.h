/**
 * @file sorting_metrics.h
 * @brief Estruturas e tipos para coleta de métricas dos algoritmos de ordenação.
 *
 * Define a struct SortMetrics utilizada por todos os algoritmos para
 * registrar comparações, trocas (swaps) e tempo de execução.
 */

#pragma once

#include <cstdint>
#include <string>

/**
 * @brief Armazena as métricas coletadas durante uma execução de ordenação.
 */
struct SortMetrics {
    uint64_t    comparisons = 0;  ///< Número de comparações realizadas
    uint64_t    swaps       = 0;  ///< Número de trocas (swaps) realizadas
    double      elapsed_ms  = 0.0;///< Tempo de execução em milissegundos
    std::string algorithm;        ///< Nome do algoritmo
    std::string scenario;         ///< Cenário: "Aleatorio", "Ordenado", "Inv. Ordenado"
    int         size        = 0;  ///< Tamanho do vetor testado
};
