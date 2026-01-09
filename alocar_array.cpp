#include <iostream>
using namespace std;

// Declaração das funções
int *criar_lista(size_t tam, int num);
void mostrar_lista(const int *const lista, const size_t tam);

int main () {
    int *array {nullptr}; // null p/ não deixar lixo de memoria de um endereço aleatorio.
    
    cout << "Qual o tamanho da lista?" << endl;
    size_t tam;
    cin >> tam;
    
    cout << "Qual o numero para preencher a lista?" << endl;
    int num;
    cin >> num;
    
    // array recebe o endereço retornado pela função, que aponta para o primeiro elemento do array alocado dinamicamente.
    array = criar_lista(tam, num);
    
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

void mostrar_lista(const int *const lista, const size_t tam){
    for(size_t i {0}; i < tam; ++i)
        cout << lista[i] << " ";
    cout << endl;
}