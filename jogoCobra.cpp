#include <iostream>
#include <conio.h>   // Necessário para _kbhit() e _getch()
#include <windows.h> // Necessário para a função Sleep()
#include <cstdlib>   // Necessário para rand() e srand()
#include <ctime>     // Necessário para time()

using namespace std;

/* 
   Programa gerado por IA para estudo do jogo da cobra em C++
*/

// Configurações do jogo
bool gameOver;
const int width = 20;  // Largura do mapa
const int height = 20; // Altura do mapa

// Variáveis de posição e pontuação
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100]; // Arrays para guardar as coordenadas da cauda
int nTail; // Tamanho atual da cauda

// Direções possíveis
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    
    // Semente para números aleatórios
    srand(time(0));
    
    // Posicionar a fruta aleatoriamente
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw() {
    // Limpar janela (comando específico do Windows)
    system("cls"); 

    // Desenhar a borda superior
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    // Desenhar o mapa, cobra e fruta
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#"; // Parede esquerda

            if (i == y && j == x)
                cout << "O"; // Cabeça da Cobra
            else if (i == fruitY && j == fruitX)
                cout << "F"; // Fruta
            else {
                bool print = false;
                // Verificar se desenha um segmento da cauda
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; // Corpo da cobra
                        print = true;
                    }
                }
                if (!print)
                    cout << " "; // Espaço vazio
            }

            if (j == width - 1)
                cout << "#"; // Parede direita
        }
        cout << endl;
    }

    // Desenhar a borda inferior
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    cout << "Pontos: " << score << endl;
    cout << "Use W, A, S, D para mover. X para sair." << endl;
}

void Input() {
    // Verificar se uma tecla foi pressionada
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            if (dir != RIGHT) dir = LEFT;
            break;
        case 'd':
            if (dir != LEFT) dir = RIGHT;
            break;
        case 'w':
            if (dir != DOWN) dir = UP;
            break;
        case 's':
            if (dir != UP) dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic() {
    // Atualizar a posição da cauda
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Mover a cabeça baseado na direção
    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    // --- Colisão com Paredes ---
    // Se nao quiser que a cobra atravesse as paredes, comente este bloco e descomente o de baixo:
    
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    /*
    // Se bater na parede -> Game Over
    if (x > width - 1 || x < 0 || y > height - 1 || y < 0)
        gameOver = true;
    */

    // --- Colisão com a própria cauda ---
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    // --- Comer a fruta ---
    if (x == fruitX && y == fruitY) {
        score += 10;
        // Gerar nova fruta
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100); // Controla a velocidade do jogo (100ms)
    }
    
    // Limpar o ecrã uma última vez e mostrar mensagem
    system("cls");
    cout << "### GAME OVER ###" << endl;
    cout << "Pontuacao Final: " << score << endl;
    system("pause"); // Pausa para ver o resultado antes de fechar
    return 0;
}