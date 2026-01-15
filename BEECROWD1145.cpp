#include <iostream>

using namespace std;

int main() {
    int X{0};
    int Y{0};

    // Lê os dois números X (elementos por linha) e Y (limite superior)
    cin >> X >> Y;

    // Loop principal, controlando o início de cada linha.
    // 'i' representa o primeiro número da linha atual.
    for (int i = 1; i <= Y; i += X) {
        // Loop interno, imprime X números a partir de 'i'.
        for (int j = 0; j < X; ++j) {
            int numero_atual = i + j;

            // Garante que não imprimimos além do limite Y
            if (numero_atual <= Y) {
                cout << numero_atual;

                // Adiciona espaço apenas se não for o último número da linha
                // ou o último número de toda a sequência.
                if (numero_atual != Y && j < X - 1) {
                    cout << " ";
                }
            } else {
                break;
            }
        }
        cout << endl;
    }

    return 0;
}