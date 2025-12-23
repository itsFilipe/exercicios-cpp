#include <iostream>

using namespace std;

int main() {

    int x {0}, y {0}, soma {0};

    cin >> x;
    cin >> y;

    if(x > y) {
        int aux {0};
        aux = x;
        x = y;
        y = aux;
    }

    for (int i = x; i <= y; i++) {
        if(i % 13 != 0) {
            soma+= i;
        }
    }

    cout << soma << "\n";


    return 0;
}