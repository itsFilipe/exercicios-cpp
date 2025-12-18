#include <iostream>

using namespace std;

int main() {
    int x{0}, y{0}, inter{0}, gremio{0}, empate{0}, partidas{0};
    int op{0};

    while (true) {
        do {
            cin >> x >> y;
            if(x > y) { inter++; } else if (y > x) { gremio++; } else { empate++; }
            
            cout << "Novo grenal (1-sim 2-nao)\n";
            cin >> op;
        } while (op != 1 && op != 2);

        if (op == 2) {
            break;
        }
    }
    
    partidas = inter + gremio + empate;

    cout << partidas << " grenais\n";
    cout << "Inter:" << inter << "\n";
    cout << "Gremio:" << gremio << "\n";
    cout << "Empates:" << empate << "\n";
    
    if(inter > gremio) { cout << "Inter venceu mais\n"; } else { cout << "Gremio venceu mais\n"; }

    return 0;
}

