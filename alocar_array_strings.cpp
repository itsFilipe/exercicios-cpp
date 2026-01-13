#include <iostream>
#include <vector>

using namespace std;

// Declaração das funções
string *criar_lista(size_t tam);
void mostrar_lista(const string *const lista, const size_t tam);
void inverter_lista(string *lista, size_t tam);

int main () {
    string *nomes {nullptr}; // null p/ não deixar lixo de memoria de um endereço aleatorio.
    
    cout << "Qual o tamanho da lista?" << endl;
    size_t tam;
    cin >> tam;
    
    // array recebe o endereço retornado pela função, que aponta para o primeiro elemento do array alocado dinamicamente.
    nomes = criar_lista(tam);
    
    mostrar_lista(nomes, tam);

    inverter_lista(nomes, tam);         
    mostrar_lista(nomes, tam);
    
    delete [] nomes; // libera a memoria alocada dinamicamente
    nomes = nullptr; // boa pratica zerar o ponteiro apos liberar a memoria
    
    return 0;   
}

string *criar_lista(size_t tam){
    string *ptrVetor {nullptr};
    ptrVetor = new string[tam];
    // std::vector<std::string>* ptrVetor = new std::vector<std::string>();
    
    for(size_t i{0}; i < tam; ++i){
        //*(p + i) = num
        cout << "Digite o " << i + 1 << " nome: " << endl;
        cin >> *(ptrVetor + i);
    }
        
    return ptrVetor;
}

void mostrar_lista(const string *const lista, const size_t tam){
    for(size_t i {0}; i < tam; ++i)
        cout << lista[i] << " ";
    cout << endl;
}

void inverter_lista(string *lista, size_t tam) {
    for (size_t i = 0; i < tam / 2; ++i) {
        // Calcula o índice oposto
        size_t oposto = tam - 1 - i;
        
        // Troca os valores usando uma variável auxiliar
        string temp = lista[i];
        lista[i] = lista[oposto];
        lista[oposto] = temp;
    }
}