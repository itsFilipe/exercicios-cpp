#include <iostream>
#include <vector>

int contar_linhas_condenadas(const std::vector<std::vector<int>> &v){
    int linhas_condenadas {0};

    for (const auto& linha : v) {
        int contagem {0};
        for (int val : linha) {
            if (val == 1)
                contagem++;

            if (contagem == 2){
                linhas_condenadas++;
                break; // muito importante para poupar processamento
            }    
        }
    }
 
    return linhas_condenadas;
}

int main(){

    std::vector<std::vector<int>> chapa = {
        {0, 0, 0, 0, 0}, // Linha 0: 0 defeitos -> OK
        {0, 1, 0, 0, 1}, // Linha 1: 2 defeitos -> Condenada
        {1, 1, 1, 0, 0}, // Linha 2: 3 defeitos -> Condenada
        {0, 0, 0, 1, 0}, // Linha 3: 1 defeito  -> OK
        {1, 0, 0, 0, 1}  // Linha 4: 2 defeitos -> Condenada
    };

    std::cout << "Total de linhas condenadas: " << contar_linhas_condenadas(chapa) 
              << std::endl;

    return 0;
}

/*
    solução STL, porém varre linha inteira!

    #include <algorithm> // Necessário para std::count

    int contar_linhas_condenadas_stl(const std::vector<std::vector<int>> &v){
        int linhas_condenadas {0};

        for (const auto& linha : v) {
            // Conta quantos '1' existem do início ao fim da linha
            if (std::count(linha.begin(), linha.end(), 1) >= 2) {
                linhas_condenadas++;
            }
        }
 
        return linhas_condenadas;
    }

*/