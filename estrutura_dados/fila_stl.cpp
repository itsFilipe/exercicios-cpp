#include <iostream>
#include <queue>

int main(){

    std::queue<int> q;

    q.push(10);
    q.push(5);

    std::cout << "Elemento da frente: " << q.front() << std::endl;
    std::cout << "Elemento de tras:   " << q.back() << std::endl;

    q.pop();

    std::cout << "Elemento da frente apos o pop: " << q.front() << std::endl;

    return 0;
}

/*
    caso precise listar e retirar os elementos

    while (!fila.empty()) {
        std::cout << fila.front() << " "; // Acessa o primeiro
        fila.pop();                       // Remove o primeiro
    }

    caso precise apenas listar

    void imprimirFila(std::queue<int> q) { // Passar por valor cria uma cópia automática
        while (!q.empty()) {
            std::cout << q.front() << " ";
            q.pop();
        }
    std::cout << std::endl;
    }
*/