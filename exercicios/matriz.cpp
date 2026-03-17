#include <iostream>
#include <vector>

int main(){
    // Definimos o tamanho que queremos para o mapa
    int linhas = 5;
    int colunas = 4;

    // Criamos o vetor já com o tamanho exato e preenchido com zeros
    // Lê-se: "Crie um vetor de 'linhas' elementos, onde cada elemento é um vetor de 'colunas' inteiros (iniciados em 0)"
    std::vector<std::vector<int>> mapa(linhas, std::vector<int>(colunas, 0));

    // Agora mapa.size() é 5, e mapa[0].size() é 4. O loop vai funcionar!
    for(size_t i = 0; i < mapa.size(); i++){ // row

        for(size_t j = 0; j < mapa[0].size(); j++){ // column
            
            // As duas formas abaixo funcionam, mas [] é mais rápido, 
            // enquanto .at() é mais seguro pois checa se o índice existe.
            mapa[i][j] = i * 2; 

        }
    }

    // Imprimindo o resultado
    for(size_t i = 0; i < mapa.size(); i++){ // row

        for(size_t j = 0; j < mapa[0].size(); j++){ // column

            std::cout << mapa.at(i).at(j) << " ";

        }
        std::cout << std::endl;
    }

    return 0;
}