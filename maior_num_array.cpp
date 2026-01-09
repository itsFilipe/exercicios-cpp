#include <iostream>

using namespace std;

// Declaração das funções
int *criar_lista(size_t tam);
void mostrar_lista(const int *const lista, const size_t tam);
int maior_numero(const int *const lista, size_t tam);
void inverter_lista(int *lista, size_t tam);

int main () {
    int *array {nullptr}; // null p/ não deixar lixo de memoria de um endereço aleatorio.
    
    cout << "Qual o tamanho da lista?" << endl;
    size_t tam;
    cin >> tam;
    
    // array recebe o endereço retornado pela função, que aponta para o primeiro elemento do array alocado dinamicamente.
    array = criar_lista(tam);
    
    mostrar_lista(array, tam);

    inverter_lista(array, tam);

    mostrar_lista(array, tam);

    int maior {0};
    maior = maior_numero(array, tam);

    cout << "O maior numero da lista e " << maior << endl;
    
    delete [] array;
    
    return 0;
}

int *criar_lista(size_t tam){
    int *p {nullptr};
    p = new int[tam];
    
    for(size_t i{0}; i < tam; ++i){
        //*(p + i) = num
        cout << "Digite o " << i + 1 << " numero: " << endl;
        cin >> *(p + i);
    }
        
    return p;
}

void mostrar_lista(const int *const lista, const size_t tam){
    for(size_t i {0}; i < tam; ++i)
        cout << lista[i] << " ";
    cout << endl;
}

int maior_numero(const int *const lista, size_t tam){
    int maior = *lista;

    for(size_t i{1}; i < tam ; ++i){
        if( *(lista + i) > maior)
            maior = *(lista + i);
    }
    
    return maior;
}

void inverter_lista(int *lista, size_t tam) {
    for (size_t i = 0; i < tam / 2; ++i) {
        // Calcula o índice oposto
        size_t oposto = tam - 1 - i;
        
        // Troca os valores usando uma variável auxiliar
        int temp = lista[i];
        lista[i] = lista[oposto];
        lista[oposto] = temp;
    }
}