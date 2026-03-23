#include "robo.h"

// ============================================================
// IMPLEMENTAÇÃO — robo.cpp
// Separar declaração (.h) de implementação (.cpp) é prática
// padrão em C++. O .h é o "contrato" (interface pública);
// o .cpp é o "como" (implementação privada).
// ============================================================

// ----------------------------------------------------------
// CONSTRUTOR
//
// ----------------------------------------------------------
robo::robo(int xi, int yi)
    : x(xi), y(yi) {}

// ----------------------------------------------------------
// tentar_mover
//
// Padrão "calcular → validar → confirmar":
//   1. Calcula nova posição em auxiliares (não altera x,y ainda).
//   2. Valida limites e colisão.
//   3. Só commita se tudo estiver ok.
//
// CONCEITO — por que usar auxiliares ao invés de mover direto?
//   Se movêssemos x diretamente e o y fosse inválido,
//   precisaríamos "desfazer" o x. Com auxiliares, o estado
//   do objeto nunca fica inconsistente.
// ----------------------------------------------------------
bool robo::tentar_mover(char comando, const std::vector<std::vector<int>>& mapa) {

    // Passo 1 — intenção (ainda não altera o estado)
    int aux_x = x;
    int aux_y = y;

    // CONVENÇÃO DE COORDENADAS usada neste projeto:
    //   x → linha  (mapa[x][y]) — W diminui, S aumenta
    //   y → coluna (mapa[x][y]) — A diminui, D aumenta
    switch (comando) {
        case 'W': aux_x--; break; // sobe   (linha menor)
        case 'S': aux_x++; break; // desce  (linha maior)
        case 'A': aux_y--; break; // esquerda
        case 'D': aux_y++; break; // direita
        default:  return false;   // tecla inválida
    }

    // Passo 2a — bounds check (verificação de limites)
    //
    // CONCEITO — mapa.size() retorna size_t (inteiro sem sinal).
    //   Comparar int com size_t pode gerar warning. O cast
    //   explícito (int) deixa a intenção clara e evita o warning.
    //
    // BUG CORRIGIDO: o original checava aux_y contra mapa.size()
    //   (linhas) e aux_x contra mapa[0].size() (colunas),
    //   invertendo os eixos. Corrigido abaixo.
    int linhas  = (int)mapa.size();
    int colunas = (int)mapa[0].size();

    if (aux_x < 0 || aux_x >= linhas ||
        aux_y < 0 || aux_y >= colunas) {
        return false; // fora do mapa
    }

    // Passo 2b — colisão com parede (valor 1)
    if (mapa[aux_x][aux_y] == 1) {
        return false;
    }

    // Passo 3 — commit: só agora o estado é atualizado
    x = aux_x;
    y = aux_y;
    return true;
}