#include <iostream>

using namespace std;

int main() {

    int x {0}, y {0};

    cin >> x;
    cin >> y;

    if(x > y) {
        int aux {0};
        aux = x;
        x = y;
        y = aux;
    }

    for (int i = x + 1; i < y; i++) {
        if(i % 5 == 2 || i % 5 == 3)  {
            cout << i << "\n";
        }
    }

    return 0;
}