#include <iostream>

class Quadrado{
private:
    size_t tamanho_lado;
public:
    void mudar_valor(size_t valor);

    // Métodos 'const' garantem que a função não altera o objeto
    size_t mostrar_valor() const;
    size_t calcula_area() const;

    Quadrado(size_t tamanho_lado = 10);
};

void Quadrado::mudar_valor(size_t valor) {
    tamanho_lado = valor;
}

size_t Quadrado::mostrar_valor() const {
    return tamanho_lado;
}

size_t Quadrado::calcula_area() const {
    return tamanho_lado * tamanho_lado;
}

//inicializador de construtor, é uma forma mais eficiente de inicializar atributos da classe
Quadrado::Quadrado(size_t lado_valor) : tamanho_lado(lado_valor) {}

int main(){

    Quadrado meu_quadrado;

    std::cout << meu_quadrado.mostrar_valor() << "\n";
    std::cout << meu_quadrado.calcula_area() << "\n";

    size_t value {0};
    std::cout << "Qual o novo valor do lado do Quadrado? ";
    std::cin >> value;

    meu_quadrado.mudar_valor(value);

    std::cout << meu_quadrado.mostrar_valor() << "\n";
    std::cout << meu_quadrado.calcula_area() << "\n";

    return 0;
}