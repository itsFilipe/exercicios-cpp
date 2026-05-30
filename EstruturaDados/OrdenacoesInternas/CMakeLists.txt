cmake_minimum_required(VERSION 3.16)
project(OrdenacoesInternas CXX)

# ── Padrão C++17 (necessário para std::filesystem) ──────────────────────────
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── Sem otimizações para que os tempos medidos sejam realistas ───────────────
# Troque para -O2/-O3 para testes de performance máxima
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Wextra")

# ── Inclui o diretório de headers ────────────────────────────────────────────
include_directories(include)

# ── Fontes do projeto ────────────────────────────────────────────────────────
set(SOURCES
    main.cpp
    src/counting_sort.cpp
    src/insertion_sort.cpp
    src/merge_sort.cpp
    src/selection_sort.cpp
    src/quick_sort.cpp
)

# ── Executável ────────────────────────────────────────────────────────────────
add_executable(benchmark ${SOURCES})

# ── Linka std::filesystem (necessário no GCC < 9) ────────────────────────────
target_link_libraries(benchmark stdc++fs)
