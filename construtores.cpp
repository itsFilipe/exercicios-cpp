#include <iostream>

class Pessoa {
public:
    std::string nome;
    int idade;
    double altura;

    //construtores é possivel fazer overloading exatamente como funções

    // Construtor padrão, ele só é gerado automaticamente caso nao possua nenhum outro construtor
    // caso exista outro construtor, é necessario definir o padrão manualmente se desejado
    Pessoa() : nome("Desconhecido"), idade(0), altura(0.0) {
        std::cout << "Construtor padrão chamado\n";
    }
    // Construtor parametrizado
    Pessoa(std::string n, int i, double a) : nome(n), idade(i), altura(a) {
        std::cout << "Construtor parametrizado chamado\n";
    }

    // Destrutor
    ~Pessoa() {
        std::cout << "Destrutor chamado para " << nome << "\n";
    }
};

int main() {
    std::cout << "Construtores em C++\n";

    Pessoa pessoa1; // Chama o construtor padrão
    std::cout << "Nome: " << pessoa1.nome << ", Idade: " << pessoa1.idade << ", Altura: " << pessoa1.altura << "\n";

    Pessoa pessoa2("Ana", 25, 1.65); // Chama o construtor parametrizado
    std::cout << "Nome: " << pessoa2.nome << ", Idade: " << pessoa2.idade << ", Altura: " << pessoa2.altura << "\n";

    //alterando valores do objeto criado com construtor padrão

    pessoa1.nome = "Carlos";
    pessoa1.idade = 30;
    pessoa1.altura = 1.75;
    std::cout << "Nome: " << pessoa1.nome << ", Idade: " << pessoa1.idade << ", Altura: " << pessoa1.altura << "\n";

    return 0;
}