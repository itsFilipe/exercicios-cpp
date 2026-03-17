#include <iostream>
#include <vector>
#include <queue>
#include <algorithm> // Necessário para a função std::reverse()

using namespace std;

/* * Estrutura simples para representar as coordenadas (Linha, Coluna) no grid.
 * Usar uma struct deixa o código mais limpo do que usar std::pair para tudo.
 */
struct Point {
    int r, c;
    
    // Sobrecarga do operador de igualdade para facilitar a comparação (ex: current == start)
    bool operator==(const Point& other) const {
        return r == other.r && c == other.c;
    }
};

void print_shortest_path(const vector<vector<int>>& grid, Point start, Point target) {
    // 1. OBTENDO AS DIMENSÕES DO MAPA
    int rows = grid.size();
    int cols = grid[0].size();

    // 2. PREPARANDO AS ESTRUTURAS DE MEMÓRIA
    // visited: Matriz booleana para não andarmos em círculos. Inicia tudo como 'false'.
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    
    // came_from: O "fio de Ariadne" ou "migalhas de pão". 
    // Guarda de qual ponto viemos para chegar no ponto atual.
    // Inicializamos com {-1, -1} para representar que uma célula ainda não tem "pai".
    vector<vector<Point>> came_from(rows, vector<Point>(cols, {-1, -1}));

    // 3. VETORES DE DIREÇÃO (O truque de movimentação)
    // Cima, Baixo, Esquerda, Direita. 
    // Ex: para ir para Cima, subtraímos 1 da linha (dr[0]) e somamos 0 na coluna (dc[0]).
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    // 4. A FILA DO BFS (A essência da Busca em Largura)
    queue<Point> q;
    
    // O ponto de partida entra na fila e já é marcado como visitado.
    q.push(start);
    visited[start.r][start.c] = true;
    
    bool found_target = false;

    // 5. O LOOP PRINCIPAL (Exploração)
    while (!q.empty()) {
        // Pega o ponto que está na "frente" da fila e o remove em seguida.
        Point curr = q.front();
        q.pop();

        // Condição de sucesso: Chegamos no destino?
        if (curr == target) {
            found_target = true;
            break; // Interrompe o loop 'while', não precisamos explorar mais nada.
        }

        // 6. EXPLORANDO OS VIZINHOS
        // O loop 'for' roda 4 vezes (uma para cada direção: cima, baixo, esquerda, direita)
        for (int i = 0; i < 4; i++) {
            int newR = curr.r + dr[i]; // Nova linha
            int newC = curr.c + dc[i]; // Nova coluna

            // Regras de validação do vizinho:
            // a) newR e newC estão dentro dos limites do mapa? (Não vazou da tela?)
            // b) A célula já foi visitada antes? (Evita loop infinito)
            // c) A célula é um caminho livre? (grid == 0 significa chão, 1 seria parede)
            if (newR >= 0 && newR < rows && newC >= 0 && newC < cols && 
                !visited[newR][newC] && grid[newR][newC] == 0) {
                
                // Marca como visitado IMEDIATAMENTE. Isso previne que o mesmo ponto
                // seja adicionado à fila múltiplas vezes por caminhos diferentes.
                visited[newR][newC] = true;
                
                // Registra o rastro: "Para chegar em (newR, newC), eu vim de 'curr'"
                came_from[newR][newC] = curr;
                
                // Coloca o vizinho válido na fila para ser explorado no futuro
                q.push({newR, newC});
            }
        }
    }

    // 7. RECONSTRUÇÃO DO CAMINHO (Se encontramos o destino)
    if (found_target) {
        vector<Point> path;
        Point current = target; // Começamos a rastrear de trás para frente
        
        // Continua voltando até chegar no ponto de partida
        while (!(current == Point{-1, -1})) { // Evita erro se algo der errado
            path.push_back(current);
            if (current == start) break; // Chegamos na origem, paramos de voltar
            
            // O ponto "atual" passa a ser o ponto de onde ele veio
            current = came_from[current.r][current.c];
        }
        
        // Como o caminho foi adicionado do Destino -> Origem, precisamos inverter
        reverse(path.begin(), path.end());
        
        // 8. IMPRIMINDO O RESULTADO
        cout << "Rota encontrada (" << path.size() - 1 << " passos):" << endl;
        for (Point p : path) {
            cout << "[" << p.r << ", " << p.c << "] ";
        }
        cout << endl;
        
    } else {
        cout << "Destino inalcancavel. O alvo esta cercado por paredes." << endl;
    }
}

int main() {
    // 0 = Caminho livre, 1 = Parede/Obstáculo
    vector<vector<int>> map = {
        {0, 0, 0, 1, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0}
    };

    Point start = {0, 0};   // Início (Linha 0, Coluna 0)
    Point target = {4, 4};  // Fim (Linha 4, Coluna 4)

    print_shortest_path(map, start, target);

    return 0;
}