#ifndef ROBO_H
#define ROBO_H

#include <vector>

// ============================================================
// CLASSE robo
// Representa o agente que navega pelo mapa.
//
// CONCEITO — Encapsulamento:
//   Os dados (x, y) são privados. Ninguém de fora lê ou
//   escreve diretamente. O acesso é controlado por métodos
//   públicos. Isso evita estados inválidos (ex: robô dentro
//   de uma parede).
// ============================================================
class robo {
    // private (implícito no início de class):
    int x; // linha  — eixo vertical   (aumenta para baixo)
    int y; // coluna — eixo horizontal (aumenta para direita)

public:
    // ----------------------------------------------------------
    // CONSTRUTOR COM ARGUMENTO PADRÃO
    //
    // CONCEITO — Default argument:
    //   robo()        → x=1, y=1  (usa defaults)
    //   robo(3, 5)    → x=3, y=5  (sobrescreve defaults)
    //   Um único construtor cobre os dois casos.
    //
    // CONCEITO — Member Initializer List  : x(xi), y(yi)
    //   Inicializa os membros ANTES do corpo {} executar.
    //   É mais eficiente que fazer  x = xi;  dentro do corpo,
    //   porque evita a inicialização default seguida de
    //   atribuição (para tipos simples como int a diferença
    //   é mínima, mas o hábito é importante para tipos complexos).
    // ----------------------------------------------------------
    robo(int xi = 1, int yi = 1);

    // ----------------------------------------------------------
    // GETTERS — métodos de leitura
    //
    // CONCEITO — const ao final da assinatura:
    //   Avisa o compilador que este método NÃO modifica o
    //   objeto. Isso permite chamá-lo com referências
    //   const robo& r, que são usadas em funções que só
    //   leem o robô (renderizar, pegar_fruta, etc.).
    //   Sem o const, o compilador rejeitaria a chamada.
    // ----------------------------------------------------------
    int getX() const { return x; }
    int getY() const { return y; }

    // ----------------------------------------------------------
    // tentar_mover
    //
    // Recebe o mapa por referência (não-const) pois
    // tecnicamente poderíamos querer marcá-lo no futuro.
    // Retorna true se o movimento foi realizado, false se
    // foi bloqueado (parede ou borda).
    //
    // CONCEITO — Responsabilidade única:
    //   A lógica de validação fica DENTRO da classe.
    //   Quem chama não precisa saber como a verificação
    //   funciona — apenas recebe o resultado booleano.
    // ----------------------------------------------------------
    bool tentar_mover(char comando, const std::vector<std::vector<int>>& mapa);
};

#endif