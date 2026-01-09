#include <iostream>

int *criar_lista(size_t tam, int num);
void mostrar_lista(const int *const lista, const int tam); //protege o endereço apontado e o conteúdo, não deixa alterar nada.

using namespace std;

int main () {
    int *array {nullptr}; // null p/ não deixar lixo de memoria de um endereço aleatorio.

    cout << "Qual o tamanho da lista?" << endl;
    int tam;
    cin >> tam;

    cout << "Qual o numero para preencher a lista?" << endl;
    int num;
    cin >> num;

    array = criar_lista(tam, num); //array recebe o endereço retornado pela função, que aponta para o primeiro elemento do array alocado dinamicamente.

    mostrar_lista(array, tam);

    delete [] array;

    return 0;
}

int *criar_lista(size_t tam, int num){
    int *p {nullptr};

    p = new int[tam];

    for(size_t i{0}; i < tam; ++i)
        *(p + i) = num;

    return p;
}

void mostrar_lista(const int *const lista, const int tam){
    for(size_t i {0}; i < tam; ++i)
        cout << lista[i] << " ";

    cout << endl;
}