#include <iostream>
#include <iomanip>

using namespace std;

double calculo(int leitura); 

int main() {
    double media = 0.0;
    int op = 0;

    cout << fixed << setprecision(2);

    while (true) {
        media = calculo(2);
        cout << "media = " << media << "\n";

        do {
            cout << "novo calculo (1-sim 2-nao)\n";
            cin >> op;
        } while (op != 1 && op != 2);

        if (op == 2) {
            break;
        }
    }

    return 0;
}

double calculo(int leitura) {
    double nota = 0, sum = 0;
    for (int c = 0; c < leitura; ) {
        cin >> nota;
        if (nota >= 0.0 && nota <= 10.0) {
            sum += nota;
            c++;
        } else {
            cout << "nota invalida\n";
        }
    }
    return sum / leitura;
}

