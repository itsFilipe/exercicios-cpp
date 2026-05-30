# OrdenacoesInternas — Benchmark de Algoritmos de Ordenação

Projeto de benchmark comparativo entre 5 algoritmos clássicos de ordenação interna, desenvolvido em C++17.

## Estrutura do Projeto

```
OrdenacoesInternas/
├── include/
│   ├── sorting_metrics.h    # Struct SortMetrics (comparações, swaps, tempo)
│   ├── counting_sort.h      # Método por Distribuição
│   ├── insertion_sort.h     # Método por Inserção
│   ├── merge_sort.h         # Método por Intercalação
│   ├── selection_sort.h     # Método por Seleção
│   └── quick_sort.h         # Método por Troca (mediana-de-três)
├── src/
│   ├── counting_sort.cpp
│   ├── insertion_sort.cpp
│   ├── merge_sort.cpp
│   ├── selection_sort.cpp
│   └── quick_sort.cpp
├── results/
│   └── benchmark_results.csv   # Gerado automaticamente ao executar
├── main.cpp                     # Runner do benchmark
├── CMakeLists.txt
└── README.md
```

## Compilação

### Via g++ direto
```bash
g++ -O0 -std=c++17 -Iinclude src/*.cpp main.cpp -o benchmark -lstdc++fs
```

### Via CMake
```bash
mkdir build && cd build
cmake ..
make
./benchmark
```

> **Importante**: Use `-O0` para que os tempos de execução reflitam o comportamento real dos algoritmos sem otimizações do compilador.

## Execução
```bash
./benchmark
```

A saída inclui:
- Tabela formatada no terminal com **tempo (ms)**, **comparações** e **swaps**
- Arquivo `results/benchmark_results.csv` para geração de gráficos

## Algoritmos Implementados

| # | Algoritmo | Método | Complexidade Pior Caso | Estável? | In-place? |
|---|-----------|--------|----------------------|----------|-----------|
| 8.1 | Counting Sort | Distribuição | O(n + k) | ✅ | ❌ |
| 8.2 | Insertion Sort | Inserção | O(n²) | ✅ | ✅ |
| 8.3 | Merge Sort | Intercalação | O(n log n) | ✅ | ❌ |
| 8.4 | Selection Sort | Seleção | O(n²) | ❌ | ✅ |
| 8.5 | Quick Sort | Troca | O(n²)* | ❌ | ✅ |

*Com mediana-de-três o pior caso é praticamente eliminado.

## Cenários Testados

- **Aleatório**: vetor com valores randômicos (semente fixa = 42)
- **Ordenado**: vetor crescente [1, 2, ..., n]
- **Inversamente Ordenado**: vetor decrescente [n, n-1, ..., 1]

## Tamanhos de Vetor

`5.000` | `10.000` | `50.000` elementos

## Casos de Uso em Sistemas Embarcados

| Algoritmo | Indicado para embarcados? | Motivo |
|-----------|--------------------------|--------|
| Counting Sort | ✅ domínios pequenos | Perfeito para ordenar prioridades, notas, IDs limitados |
| Insertion Sort | ✅ muito indicado | Online, O(n) no melhor caso, ideal para listas quase ordenadas |
| Merge Sort | ⚠️ com cuidado | Requer O(n) de RAM extra — limitante em MCUs com pouca memória |
| Selection Sort | ✅ memórias EEPROM/Flash | Mínimo de swaps (O(n)), reduz desgaste de escrita |
| Quick Sort | ⚠️ com cuidado | Ótimo desempenho médio, mas pilha de recursão pode ser problema |
