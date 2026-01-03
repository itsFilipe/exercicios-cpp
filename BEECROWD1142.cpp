#include <iostream>

using namespace std;

int main() {

    size_t n {0}, numeros {1};

    cin >> n;

    for (size_t i {0}; i < n; ++i){ //dificultei demais com dois loops.
        for( size_t j {0}; j < 3; ++j) {
            cout << numeros << " ";
            numeros++;
            if(numeros % 4 == 0) {
                cout << "PUM" << endl;
                numeros++;
            }
        }

        //cout << endl;
    }

    return 0;
}

/*
uma forma melhor

for (int i = 0; i < n; ++i) {
        // Imprime a sequência: X X X PUM
        cout << numero << " " << numero + 1 << " " << numero + 2 << " PUM" << endl;
        
        // Salta 4 números para iniciar a próxima linha (ex: 1,2,3,PUM -> próxima linha começa em 5)
        numero += 4;
    }


*/