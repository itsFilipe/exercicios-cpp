//jogo simples para estudo

#include <iostream>
#include <vector>
#include <cstdlib> // Para system()

using namespace std;

// === CLASSE ROBO ===
// O Robô agora é uma entidade inteligente que sabe se cuidar.
class Robo {
private:
    // Dados privados: Ninguém de fora pode tocar aqui diretamente.
    int x, y; 

public:
    // CONSTRUTOR: Define onde o robô nasce.
    // Uso de "Member Initializer List" (: x(inicioX)...) -> Mais eficiente que fazer atribuição dentro {}.
    Robo(int inicioX, int inicioY) : x(inicioX), y(inicioY) {}

    // GETTERS: Métodos de leitura (Read-Only)
    // O 'const' no final avisa o compilador: "Esse método NÃO altera o robô".
    int getX() const { return x; }
    int getY() const { return y; }

    // O CÉREBRO: Método que tenta realizar o movimento
    // Recebe o mapa por REFERÊNCIA CONSTANTE (const vector... &)
    // Motivo: Não queremos copiar o mapa (lento) e não queremos estragar o mapa (const).
    bool tentarMover(char comando, const vector<vector<int>>& mapa) {
        
        // 1. Calcula a intenção (Fantasma)
        int novoX = x;
        int novoY = y;

        switch (comando) {
            case 'W': novoY--; break;
            case 'S': novoY++; break;
            case 'A': novoX--; break;
            case 'D': novoX++; break;
            default: return false; // Comando inválido
        }

        // 2. Validação (Encapsulada dentro da classe)
        // O Robô é responsável por saber se ele cabe no lugar.
        
        // Verifica Limites (Bounds Checking)
        if (novoY < 0 || novoY >= mapa.size() || 
            novoX < 0 || novoX >= mapa[0].size()) {
            return false; // Saiu do mapa
        }

        // Verifica Paredes (Collision Checking)
        if (mapa[novoY][novoX] == 1) {
            return false; // Bateu na parede
        }

        // 3. Commit
        // Se chegou aqui, é seguro. Atualiza o estado interno.
        x = novoX;
        y = novoY;
        return true; // Sucesso
    }
};

// === FUNÇÃO DE RENDERIZAÇÃO ===
// Separei a renderização da Main para ficar mais limpo.
// Recebe o Robô como referência const (apenas leitura).
void desenharTela(const vector<vector<int>>& mapa, const Robo& robo) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    cout << "--- NAVEGADOR OOP ---" << endl;
    cout << "Posicao Atual: [" << robo.getY() << "][" << robo.getX() << "]" << endl;

    for (size_t i = 0; i < mapa.size(); i++) {
        for (size_t j = 0; j < mapa[i].size(); j++) {
            
            // Usamos os Getters aqui, pois x e y são privados
            if (i == robo.getY() && j == robo.getX()) {
                cout << " R "; 
            } else if (mapa[i][j] == 1) {
                cout << "[#]"; 
            } else {
                cout << " . "; 
            }
        }
        cout << endl;
    }
}

// === MAIN (CONTROLE) ===
int main() {
    // Mapa: 1=Parede, 0=Livre
    // Dica: 'static const' aqui seria melhor em projetos grandes, mas ok por enquanto.
    vector<vector<int>> mapa = {
        {1, 0, 1, 0, 0, 0, 1, 1, 1, 1},
        {1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 1}
    };

    // Instancia o objeto Robô (Construtor chamado aqui)
    Robo meuRobo(1, 0); // x=1, y=0

    bool rodando = true;

    while (rodando) {
        
        // 1. Renderiza
        desenharTela(mapa, meuRobo);

        // 2. Input
        char comando;
        cout << "\nComando (WASD / Q): ";
        cin >> comando;
        comando = toupper(comando);

        if (comando == 'Q') {
            rodando = false;
            continue;
        }

        // 3. Ação
        // A main não sabe COMO o robô se move, ela só PEDE para ele tentar.
        // Isso é abstração.
        if (meuRobo.tentarMover(comando, mapa)) {
            // Se retornou true, moveu com sucesso.
            // Poderíamos tocar um som aqui, por exemplo.
        } else {
            // Se retornou false (bateu), o robô não se mexeu.
            // A gente nem precisa "desfazer" nada, porque o robô já se protejeu internamente.
        }
    }

    return 0;
}