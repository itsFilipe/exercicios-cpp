// ============================================================
// ROBÔ NAVEGADOR — main.cpp
//
// Projeto de estudo de C++ cobrindo:
//   • Classes e encapsulamento
//   • Matrizes (vector<vector<int>>)
//   • Structs e sobrecarga de operadores
//   • BFS (Breadth-First Search) com reconstrução de caminho
//   • Referências const, ponteiros implícitos, iteração
//   • Diretivas de pré-processador (#ifdef / #endif)
// ============================================================

#include <iostream>
#include <cstdlib>   // rand(), srand(), system()
#include <ctime>     // time()
#include <queue>     // std::queue  — usado no BFS
#include <vector>    // std::vector
#include <algorithm> // std::reverse

#include "robo.h"

// ============================================================
// STRUCT Ponto
//
// CONCEITO — struct vs class:
//   Por padrão, membros de struct são PUBLIC; de class são
//   PRIVATE. Para dados simples (x, y), struct é idiomático.
//
// CONCEITO — Sobrecarga de operador (operator==):
//   Permite escrever  if (a == b)  em vez de
//   if (a.x == b.x && a.y == b.y).
//   O compilador substitui  a == b  por  a.operator==(b).
//
// CONCEITO — const ao final:
//   O mesmo de métodos de classe: garante que este operador
//   não altera o objeto (this).
// ============================================================
struct Ponto {
    int x; // linha
    int y; // coluna

    bool operator==(const Ponto& outro) const {
        return x == outro.x && y == outro.y;
    }
};

// ============================================================
// PROTÓTIPOS DAS FUNÇÕES
//
// CONCEITO — Forward declaration:
//   O compilador lê o arquivo de cima para baixo. Se main()
//   chama renderizar_mapa() antes da sua definição, o
//   compilador não sabe a assinatura ainda → erro.
//   O protótipo declara a assinatura antecipadamente.
//   A implementação real pode ficar abaixo do main().
// ============================================================
void renderizar_mapa(const std::vector<std::vector<int>>& mapa, const robo& r,
                     const std::vector<Ponto>& caminho);
void nova_fruta(std::vector<std::vector<int>>& mapa, const robo& r);
std::vector<Ponto> encontra_caminho(const std::vector<std::vector<int>>& mapa,
                                    Ponto inicio, Ponto alvo);
bool pegar_fruta(std::vector<std::vector<int>>& mapa, const robo& r);
Ponto encontrar_fruta(const std::vector<std::vector<int>>& mapa);
void limpar_tela();

// ============================================================
// MAIN — loop principal do jogo
// ============================================================
int main() {

    // CONCEITO — srand / rand:
    //   rand() gera sequências pseudo-aleatórias. Se a semente
    //   (seed) for a mesma, a sequência é idêntica.
    //   srand(time(0)) usa o tempo atual como semente,
    //   garantindo sequências diferentes a cada execução.
    srand((unsigned)time(0));

    robo meu_robo; // construtor default: x=1, y=1

    // ----------------------------------------------------------
    // MAPA
    //
    // CONCEITO — vector<vector<int>> (matriz dinâmica):
    //   Cada linha é um std::vector<int>.
    //   mapa[i][j] → linha i, coluna j.
    //   mapa.size()    → número de linhas.
    //   mapa[0].size() → número de colunas.
    //
    // Legenda de valores:
    //   0 → livre
    //   1 → parede
    //   2 → fruta (objetivo)
    // ----------------------------------------------------------
    std::vector<std::vector<int>> mapa = {
        {1, 0, 1, 0, 0, 0, 1, 1, 1, 1},
        {1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 2, 1}
    };

    bool rodando = true;

    while (rodando) {

        // ----------------------------------------------------------
        // Calcula o caminho BFS a cada frame para refletir
        // qualquer mudança no mapa (nova fruta, movimento manual).
        // ----------------------------------------------------------
        Ponto pos_robo  = { meu_robo.getX(), meu_robo.getY() };
        Ponto pos_fruta = encontrar_fruta(mapa);
        std::vector<Ponto> caminho;

        if (pos_fruta.x != -1) { // há fruta no mapa
            caminho = encontra_caminho(mapa, pos_robo, pos_fruta);
        }

        limpar_tela();
        renderizar_mapa(mapa, meu_robo, caminho);

        // ----------------------------------------------------------
        // Menu de modo
        // ----------------------------------------------------------
        std::cout << "\n[M] Manual (WASD)   [B] Auto-BFS   [Q] Sair\n";
        std::cout << "Comando: ";

        char entrada;
        std::cin >> entrada;
        entrada = (char)toupper((unsigned char)entrada);

        if (entrada == 'Q') {
            rodando = false;
            continue;
        }

        // ── MODO AUTOMÁTICO ──────────────────────────────────────
        if (entrada == 'B') {

            if (caminho.empty()) {
                std::cout << "Nenhuma rota encontrada!\n";
                std::cin.get(); // pausa
                continue;
            }

            // CONCEITO — range-based for:
            //   for (Tipo elemento : colecao) itera sobre cada
            //   elemento. Equivale ao for com índice mas é mais
            //   legível quando o índice em si não importa.
            //
            // O caminho inclui a posição inicial (índice 0),
            // então pulamos ela com início em 1.
            for (size_t passo = 1; passo < caminho.size(); passo++) {

                // Recalcula caminho restante para renderização
                std::vector<Ponto> restante(caminho.begin() + (int)passo,
                                            caminho.end());

                limpar_tela();
                renderizar_mapa(mapa, meu_robo, restante);
                std::cout << "\n[AUTO-BFS] Passo " << passo
                          << " de " << caminho.size() - 1 << "\n";

                // Determina o comando de movimento para chegar
                // ao próximo ponto do caminho.
                //
                // CONCEITO — diferença de coordenadas:
                //   Se próximo.x < atual.x → estamos subindo → 'W'
                //   Se próximo.x > atual.x → estamos descendo → 'S'
                //   Análogo para y / A / D.
                Ponto proximo = caminho[passo];
                char  cmd     = 0;

                if      (proximo.x < meu_robo.getX()) cmd = 'W';
                else if (proximo.x > meu_robo.getX()) cmd = 'S';
                else if (proximo.y < meu_robo.getY()) cmd = 'A';
                else if (proximo.y > meu_robo.getY()) cmd = 'D';

                meu_robo.tentar_mover(cmd, mapa);

                // Verifica se chegou na fruta a cada passo
                if (pegar_fruta(mapa, meu_robo)) {
                    limpar_tela();
                    renderizar_mapa(mapa, meu_robo, {});
                    std::cout << "\nO robô comeu a fruta! 🎉\n";
                    std::cout << "Pressione Enter para continuar...";
                    std::cin.ignore();
                    std::cin.get();

                    std::cout << "Deseja gerar nova fruta? (S/N): ";
                    char resp;
                    std::cin >> resp;
                    resp = (char)toupper((unsigned char)resp);

                    if (resp == 'S') {
                        nova_fruta(mapa, meu_robo);
                    } else {
                        rodando = false;
                    }
                    break; // interrompe o loop de passos
                }

                // Pequena pausa para visualização
                // (em ms — implementado com loop vazio portável)
                // Para pausas reais, use <thread> + sleep_for em C++11.
                volatile long contador = 0;
                while (contador < 30000000L) contador++;
            }
            continue;
        }

        // ── MODO MANUAL ──────────────────────────────────────────
        meu_robo.tentar_mover(entrada, mapa);

        if (pegar_fruta(mapa, meu_robo)) {
            limpar_tela();
            renderizar_mapa(mapa, meu_robo, {});
            std::cout << "\nO robô comeu a fruta! 🎉\n";
            std::cout << "Deseja gerar nova fruta? (S/N): ";

            char resp;
            std::cin >> resp;
            resp = (char)toupper((unsigned char)resp);

            if (resp == 'S') {
                nova_fruta(mapa, meu_robo);
            } else {
                rodando = false;
            }
        }
    }

    std::cout << "\nAté logo!\n";
    return 0;
}

// ============================================================
// renderizar_mapa
//
// Recebe mapa, robô e o vetor de caminho calculado pelo BFS.
// Marca os tiles do caminho com '·' para visualização.
//
// CONCEITO — const vector& vs vector:
//   Passar por valor (vector<...> mapa) copiaria toda a
//   matriz a cada chamada → lento e desnecessário.
//   Passar por referência const (const vector<...>& mapa)
//   é O(1): só passa o endereço, sem cópia, sem risco de
//   modificar o original.
// ============================================================
void renderizar_mapa(const std::vector<std::vector<int>>& mapa,
                     const robo& r,
                     const std::vector<Ponto>& caminho) {

    int rx = r.getX(); // linha do robô
    int ry = r.getY(); // coluna do robô

    // Constrói um set de posições que pertencem ao caminho
    // para lookup O(1) durante a renderização.
    //
    // CONCEITO — vector<vector<bool>> como "máscara":
    //   Criamos uma matriz de booleanos do mesmo tamanho
    //   do mapa. Marcamos true onde há caminho.
    //   Alternativa seria usar std::set<Ponto>, mas exigiria
    //   definir operator< ou um hash.
    int linhas  = (int)mapa.size();
    int colunas = (int)mapa[0].size();
    std::vector<std::vector<bool>> no_caminho(linhas,
                                   std::vector<bool>(colunas, false));

    for (const Ponto& p : caminho) {
        if (p.x >= 0 && p.x < linhas && p.y >= 0 && p.y < colunas)
            no_caminho[p.x][p.y] = true;
    }

    std::cout << "\n";
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {

            if (i == rx && j == ry) {
                std::cout << "O ";   // robô
            } else if (mapa[i][j] == 1) {
                std::cout << "# ";   // parede
            } else if (mapa[i][j] == 2) {
                std::cout << "X ";   // fruta
            } else if (no_caminho[i][j]) {
                std::cout << ". ";   // caminho BFS
            } else {
                std::cout << "  ";   // livre
            }
        }
        std::cout << "\n";
    }

    std::cout << "\nPosição: [" << rx << "][" << ry << "]\n";
    std::cout << "Legenda: O=Robô  #=Parede  X=Fruta  .=Caminho\n";
}

// ============================================================
// encontrar_fruta
//
// Varre o mapa e retorna as coordenadas da fruta (valor 2).
// Retorna {-1, -1} se não houver fruta.
// ============================================================
Ponto encontrar_fruta(const std::vector<std::vector<int>>& mapa) {
    for (int i = 0; i < (int)mapa.size(); i++)
        for (int j = 0; j < (int)mapa[i].size(); j++)
            if (mapa[i][j] == 2)
                return {i, j};
    return {-1, -1};
}

// ============================================================
// pegar_fruta
//
// Verifica se o robô está na mesma célula que a fruta.
// Se sim, remove a fruta do mapa (seta para 0) e retorna true.
//
// ============================================================
bool pegar_fruta(std::vector<std::vector<int>>& mapa, const robo& r) {
    Ponto fruta = encontrar_fruta(mapa);
    if (fruta.x == -1) return false;

    if (fruta.x == r.getX() && fruta.y == r.getY()) {
        mapa[fruta.x][fruta.y] = 0; // remove fruta
        return true;
    }
    return false;
}

// ============================================================
// nova_fruta
//
// Gera uma fruta em posição aleatória livre, exceto onde
// o robô está.
//
// CONCEITO — abordagem determinística em 2 fases:
//   Fase 1: varre o mapa UMA vez e coleta todas as posições
//           válidas num vector (O(n)).
//   Fase 2: sorteia um índice aleatório nesse vector (O(1)).
//   Total: O(n) — melhor que tentar posições aleatórias em
//   loop (que poderia nunca terminar se o mapa estiver cheio).
// ============================================================
void nova_fruta(std::vector<std::vector<int>>& mapa, const robo& r) {
    std::vector<Ponto> livres;

    for (int i = 0; i < (int)mapa.size(); i++) {
        for (int j = 0; j < (int)mapa[i].size(); j++) {
            // Só considera células livres que não sejam onde o robô está
            if (mapa[i][j] == 0 && !(i == r.getX() && j == r.getY())) {
                livres.push_back({i, j});
            }
        }
    }

    if (livres.empty()) {
        std::cout << "Mapa completo! Você venceu!\n";
        return;
    }

    // CONCEITO — rand() % N:
    //   Gera número de 0 a N-1.
    //   livres.size() retorna size_t; o cast (int) é necessário
    //   pois rand() retorna int e a divisão de inteiros de tipos
    //   diferentes pode gerar warning.
    int idx = rand() % (int)livres.size();
    mapa[livres[idx].x][livres[idx].y] = 2;
}

// ============================================================
// encontra_caminho — BFS (Breadth-First Search)
//
// ALGORITMO:
//   BFS explora o grafo em "ondas" a partir do ponto inicial,
//   nível por nível. Por isso, o primeiro caminho encontrado
//   até o alvo é GARANTIDAMENTE o mais curto (em nº de passos).
//
// ESTRUTURA DE DADOS — std::queue (Fila):
//   • FIFO: First In, First Out.
//   • push() → insere no final.
//   • front() → lê o primeiro.
//   • pop()   → remove o primeiro.
//   A fila garante que exploramos nó por nível (BFS),
//   e não em profundidade (que seria uma pilha / DFS).
//
// RECONSTRUÇÃO DO CAMINHO — came_from (mapa de predecessores):
//   Enquanto exploramos, gravamos de onde cada nó foi
//   descoberto: came_from[x][y] = ponto_anterior.
//   Quando chegamos ao alvo, caminhamos de volta
//   alvo → ... → inicio usando came_from.
//   Depois invertemos o vetor para ter inicio → alvo.
//
//   Exemplo visual (mapa 3x3 sem paredes):
//
//   Inicio: (0,0)   Alvo: (2,2)
//
//   came_from preenchido pelo BFS:
//     (0,1) ← (0,0)       (0,0) é o início, sem predecesser
//     (1,0) ← (0,0)
//     (1,1) ← (0,1)  ou (1,0)  (depende da ordem de descoberta)
//     (2,2) ← (2,1)
//
//   Reconstrução reversa:
//     (2,2) → came_from[2][2] = (2,1)
//     (2,1) → came_from[2][1] = (1,1)
//     ...até chegar em (0,0)
//
//   Após reverse:  (0,0) → (0,1) → ... → (2,2)
//
// COMPLEXIDADE:
//   Tempo:  O(V + E) onde V = células, E = arestas (4 por célula)
//   Espaço: O(V) para passou[][] e came_from[][]
// ============================================================
std::vector<Ponto> encontra_caminho(const std::vector<std::vector<int>>& mapa,
                                    Ponto inicio, Ponto alvo) {

    int linhas  = (int)mapa.size();
    int colunas = (int)mapa[0].size();

    // ----------------------------------------------------------
    // Matriz "passou" — marca células já visitadas.
    //
    // CONCEITO — inicialização de vector 2D:
    //   vector<vector<bool>>(linhas, vector<bool>(colunas, false))
    //   Cria linhas vetores de tamanho colunas, todos com false.
    //   É o equivalente a:
    //     bool passou[linhas][colunas] = {};
    //   mas dinâmico (tamanho definido em tempo de execução).
    // ----------------------------------------------------------
    std::vector<std::vector<bool>> passou(linhas,
                                std::vector<bool>(colunas, false));

    // ----------------------------------------------------------
    // came_from — armazena de onde cada célula foi descoberta.
    //
    // Sentinel {-1, -1}: indica "sem predecessor" (ponto inicial).
    // ----------------------------------------------------------
    std::vector<std::vector<Ponto>> came_from(linhas,
                                   std::vector<Ponto>(colunas, {-1, -1}));

    // ----------------------------------------------------------
    // Vetores de direção — os 4 vizinhos (cima, baixo, esq, dir)
    //
    // CONCEITO — arrays paralelos de deslocamento:
    //   dr[i] e dc[i] formam o par de deslocamento i.
    //   Para i=0: dr=−1, dc=0 → sobe uma linha.
    //   Para i=3: dr=0,  dc=1 → move uma coluna para direita.
    //   Iterar de 0 a 3 examina os 4 vizinhos de qualquer célula.
    // ----------------------------------------------------------
    const int dr[] = {-1,  1,  0,  0}; // linha:   cima, baixo
    const int dc[] = { 0,  0, -1,  1}; // coluna: esquerda, direita

    // Fila BFS
    std::queue<Ponto> fila;
    fila.push(inicio);
    passou[inicio.x][inicio.y] = true;

    bool encontrou = false;

    // ----------------------------------------------------------
    // LOOP PRINCIPAL DO BFS
    // ----------------------------------------------------------
    while (!fila.empty()) {

        // Retira o próximo nó da fila (FIFO)
        Ponto atual = fila.front();
        fila.pop();

        // Condição de parada: chegamos ao alvo
        if (atual == alvo) {
            encontrou = true;
            break;
        }

        // Explora os 4 vizinhos
        for (int i = 0; i < 4; i++) {
            int nr = atual.x + dr[i]; // nova linha
            int nc = atual.y + dc[i]; // nova coluna

            // Valida:
            //   1. Dentro dos limites  (< não <=, evita out-of-bounds)
            //   2. Não visitado ainda
            //   3. Não é parede
            if (nr >= 0 && nr < linhas &&
                nc >= 0 && nc < colunas &&
                !passou[nr][nc] &&
                mapa[nr][nc] != 1) {

                passou[nr][nc]    = true;
                came_from[nr][nc] = atual; // grava o predecessor
                fila.push({nr, nc});
            }
        }
    }

    // ----------------------------------------------------------
    // RECONSTRUÇÃO DO CAMINHO
    //
    // Se encontrou o alvo, caminhamos de volta usando came_from,
    // do alvo até o início.
    // ----------------------------------------------------------
    std::vector<Ponto> caminho;

    if (!encontrou) {
        return caminho; // vetor vazio = sem rota
    }

    // Começa no alvo e volta para o início
    Ponto cursor = alvo;
    while (!(cursor == Ponto{-1, -1})) {
        caminho.push_back(cursor);
        if (cursor == inicio) break;          // chegamos ao início
        cursor = came_from[cursor.x][cursor.y]; // passo anterior
    }

    // CONCEITO — std::reverse:
    //   O caminho foi construído de trás para frente (alvo→inicio).
    //   reverse() inverte o vetor in-place em O(n).
    //   Após isso: caminho[0] = inicio, caminho[n-1] = alvo.
    std::reverse(caminho.begin(), caminho.end());

    return caminho;
}

// ============================================================
// limpar_tela
//
// CONCEITO — Diretivas de pré-processador (#ifdef / #else):
//   O pré-processador roda ANTES da compilação e decide
//   qual trecho de código incluir com base em macros.
//   _WIN32 é definida automaticamente em compiladores Windows.
//   system("cls") / system("clear") limpa o terminal,
//   mas são dependentes do SO — por isso o ifdef.
// ============================================================
void limpar_tela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}