/*
O Filtro de Ruído do Sensor Lidar
Foco: Iteradores, Mutação e o temido (mas essencial) idioma "Erase-Remove".
Cenário:
Lidando com hardware na vida real, os dados nunca chegam perfeitos.
Imagine que aquele seu sensor Lidar fez uma varredura e retornou um vetor com várias leituras, mas o motor falhou e gerou ruído. 
Algumas distâncias vieram como 0 (o laser foi ofuscado) e outras vieram como -1 (falha grave de leitura).

Seu Objetivo:
Crie o seguinte vetor de teste no seu main(): std::vector<int> scan = {12, 0, 45, -1, 22, -1, 0, 115, 90, -1, 0};
    Você não quer criar um vetor novo. Modifique este vetor no próprio local (in-place).
    Onde houver um 0, você deve substituir pelo valor de segurança 1. (Use um algoritmo pronto da STL para isso, não faça um loop for manual com if).
    Onde houver um -1, você deve remover o elemento do vetor completamente, fazendo ele encolher (deletar a sujeira).

O que você deve pesquisar na documentação do C++:
    A função std::replace().
    O famosíssimo "Erase-Remove Idiom" do C++ (pesquise exatamente por esse termo).
    Envolve combinar o método .erase() do vetor com a função std::remove() da biblioteca <algorithm>. É um clássico de entrevistas técnicas.
*/

#include <iostream>
#include <vector>
#include <algorithm>

void display(const std::vector<int> &vec) {
    std::cout << "[ ";
    std::for_each(vec.begin(), vec.end(),
        [](int x) { std::cout << x << " ";});
    std::cout << "]" << std::endl;
}

int main(){
    std::vector<int> scan = {12, 0, 45, -1, 22, -1, 0, 115, 90, -1, 0};
    std::replace(scan.begin(), scan.end(), 0, 1);
    display(scan);
    auto fim_pos_limpeza = std::remove_if(scan.begin(), scan.end(), 
                                [](int x) { return x == -1;}); //quem atende predicado é sobrescrito
    //lambda é para pesquisas mais complexas, nesse caso é simples e pode ser usado
    //auto fim_pos_limpeza = std::remove(scan.begin(), scan.end(), -1);

    display(scan);

    scan.erase(fim_pos_limpeza, scan.end());
    
    // Se o seu compilador estiver configurado para C++20, isso substitui o Erase-Remove inteiro:
    //std::erase(scan, -1);
    
    display(scan);
    
    return 0;
}
