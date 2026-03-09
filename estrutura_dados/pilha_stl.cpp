#include <iostream>
#include <stack>

int main(){
    std::stack<int> st;
    st.push(10);
    st.push(5);
    
    std::cout << "Elemento do topo: " << st.top() << std::endl;
    
    st.pop();
    std::cout << "Elemento do topo apos o pop: " << st.top() << std::endl;
    return 0;
}

/*
    caso precise listar e retirar os elementos (LIFO - o último que entra é o primeiro que sai)

    while (!pilha.empty()) {
        std::cout << pilha.top() << " "; // Acessa o topo (último inserido)
        pilha.pop();                     // Remove o topo
    }

    caso precise apenas listar (sem destruir a pilha original)

    void imprimirPilha(std::stack<int> s) { // Passar por valor cria uma cópia automática
        while (!s.empty()) {
            std::cout << s.top() << " ";
            s.pop();
        }
        std::cout << std::endl;
    }
*/