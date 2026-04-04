#include <iostream>

using namespace std;

int main() {
    size_t op {0};
    size_t alcool {0}, gasolina {0}, diesel {0};

    while (op != 4) {
        cin >> op;
        switch (op) {
            case 1: alcool++; break;
            case 2: gasolina++; break;
            case 3: diesel++; break;
        }
    }

    cout << "MUITO OBRIGADO" << endl;
    cout << "Alcool: " << alcool << endl;
    cout << "Gasolina: " << gasolina << endl;
    cout << "Diesel: " << diesel << endl;

    return 0;
}

/* Outra boa opcao, boa para simplicidade e escalabilidade 

size_t votos[4] = {0, 0, 0, 0}; // votos[1]=alcool, [2]=gasolina, [3]=diesel

while (op != 4) {
    cin >> op;
    if (op >= 1 && op <= 3) votos[op]++;
}

*/