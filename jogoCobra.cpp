#include <iostream>
#include <termios.h>  // Para configuração do terminal
#include <unistd.h>   // Para usleep()
#include <fcntl.h>    // Para controle de I/O não bloqueante
#include <cstdlib>    // Para rand() e srand()
#include <ctime>      // Para time()
using namespace std;

/* 
   Programa gerado por IA para estudo do jogo da cobra em C++
   Adaptado para Linux
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

// Função para detectar tecla pressionada (substitui _kbhit)
int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    
    return 0;
}

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
    nTail = 0;
}

void Draw() {
    // Limpar janela (comando Linux)
    system("clear"); 
    
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
    if (kbhit()) {
        char c = getchar();
        switch (c) {
        case 'a':
        case 'A':
            if (dir != RIGHT) dir = LEFT;
            break;
        case 'd':
        case 'D':
            if (dir != LEFT) dir = RIGHT;
            break;
        case 'w':
        case 'W':
            if (dir != DOWN) dir = UP;
            break;
        case 's':
        case 'S':
            if (dir != UP) dir = DOWN;
            break;
        case 'x':
        case 'X':
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
    // Cobra atravessa as paredes (modo wrap-around)
    if (x >= width) x = 0; 
    else if (x < 0) x = width - 1;
    if (y >= height) y = 0; 
    else if (y < 0) y = height - 1;
    
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
        usleep(100000); // Controla a velocidade do jogo (100ms = 100000 microssegundos)
    }
    
    // Limpar o ecrã uma última vez e mostrar mensagem
    system("clear");
    cout << "### GAME OVER ###" << endl;
    cout << "Pontuacao Final: " << score << endl;
    cout << "Pressione Enter para sair...";
    cin.get();
    
    return 0;
}