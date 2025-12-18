#include <iostream>
#include <memory> // smart pointers

using namespace std;

/*
========================================
DATA SEGMENT
- Variáveis globais e estáticas
========================================
*/
int variavel_global = 100;

void exemplo_stack(int x) {
    /*
    STACK:
    - Variáveis locais
    - Parâmetros de função
    - Cada chamada cria um stack frame
    */

    int variavel_local = x;
    cout << "[STACK] Variavel local: " << variavel_local << endl;
}

int main() {

    cout << "===== STACK =====" << endl;
    exemplo_stack(10);

    /*
    ========================================
    HEAP - Alocação manual em C (conceitual)
    ========================================
    */
    /*
    int *p_c;
    p_c = (int*) malloc(sizeof(int)); // malloc retorna void* por isso o typecast 
    *p_c = 20;
    free(p_c);
    */

    cout << "\n===== HEAP (C++) - new/delete =====" << endl;

    int *p = nullptr;     // inicialização segura
    p = new int;          // alocação no heap
    *p = 30;

    cout << "Endereco: " << p << endl;
    cout << "Valor: " << *p << endl;

    delete p;             // libera memória
    p = nullptr;          // evita dangling pointer

    /*
    ========================================
    HEAP - Array dinâmico
    ========================================
    */
    cout << "\n===== HEAP - Array =====" << endl;

    int *array = new int[5];

    for (int i = 0; i < 5; i++) {
        array[i] = i * 10;
        cout << "array[" << i << "] = " << array[i] << endl;
    }

    delete[] array; // IMPORTANTE: delete[]
    array = nullptr;

    /*
    ========================================
    ERRO COMUM 1: MEMORY LEAK
    ========================================
    */
    cout << "\n===== ERRO: MEMORY LEAK =====" << endl;

    int *leak = new int(50);
    cout << "Valor (leak): " << *leak << endl;

    // delete leak; // ESQUECER ISSO CAUSA MEMORY LEAK

    /*
    ========================================
    ERRO COMUM 2: DANGLING POINTER
    ========================================
    */
    cout << "\n===== ERRO: DANGLING POINTER =====" << endl;

    int *dangling = new int(60);
    delete dangling;
    // dangling ainda aponta para um endereço inválido
    // cout << *dangling; // COMPORTAMENTO INDEFINIDO

    dangling = nullptr; // correção

    /*
    ========================================
    C++ MODERNO - SMART POINTER
    ========================================
    */
    cout << "\n===== C++ MODERNO - smart pointer =====" << endl;

    unique_ptr<int> smart = make_unique<int>(70);
    cout << "Valor (smart pointer): " << *smart << endl;

    // memória liberada automaticamente ao sair do escopo

    /*
    ========================================
    RESUMO:
    - Stack: automática, rápida
    - Heap: manual, flexível
    - new/delete: cuidado com leaks
    - Smart pointers: seguros e recomendados
    ========================================
    */

    cout << "\n===== FIM DO ESTUDO =====" << endl;
    return 0;
}
