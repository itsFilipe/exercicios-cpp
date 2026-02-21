//Numeros aleatorios

#include <iostream>
#include <cstdlib> //rand()
#include <ctime>   //time()

using namespace std;

int main() {

    int nmr_aleatorio {};
    size_t count {10};
    int min {1};
    int max {6};

    cout << "RAND_MAX no meu sistema: " << RAND_MAX << endl;
    srand(time(nullptr));

    for (size_t i{1}; i <= count; ++i) {
        nmr_aleatorio = rand() % max + min; //gera nmr entre min e max
        cout << nmr_aleatorio << endl;
    }

    cout << endl;

    return 0;
}