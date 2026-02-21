#include <iostream>

using namespace std;

int main() {
    
    cout << "Insira a largura do quarto em cm: ";
    //boa pratica inicializar dessa forma
    int largura_quarto {0}; 
    cin >> largura_quarto;

    cout << "Insira o comprimento do quarto em cm: ";
    int comprimento_quarto {0};
    cin >> comprimento_quarto;

    cout << "A area do quarto e " << largura_quarto * comprimento_quarto << " cm quadrado"<< endl;

    return 0;
}