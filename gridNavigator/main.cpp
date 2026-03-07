#include <iostream>
#include "robo.h"

void renderizar_mapa(std::vector<std::vector<int>>& mapa, const robo& r);
bool pegar_fruta(std::vector<std::vector<int>>& mapa, const robo& r);
void limpar_tela();

int main() {

    robo meu_robo; //ja esta instanciado com o construtor padrao, entao x=1 e y=1

    std::cout << meu_robo.getX() << std::endl;
    std::cout << meu_robo.getY() << std::endl;

    std::vector<std::vector<int>> mapa = {
        {1, 0, 1, 0, 0, 0, 1, 1, 1, 1},
        {1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 2, 1}
    };

    

    char comando;
    bool rodando = true;

    while(rodando) {
        limpar_tela();
        renderizar_mapa(mapa, meu_robo);
        std::cout << "Comando: W, A, S, D -- Q para sair" << std::endl;
        std::cin >> comando;
        comando = toupper(comando); 

        if(comando == 'Q') {
            rodando = false;
            //continue;
        }

        meu_robo.tentar_mover(comando, mapa);

        if(pegar_fruta(mapa, meu_robo)){
            std::cout << "O robo comeu a fruta!!!" << std::endl;
            rodando = false;
        }
    }


    return 0;
}

void renderizar_mapa(std::vector<std::vector<int>>& mapa, const robo& r) {
    int rx, ry;
    rx = r.getX();
    ry = r.getY();

    for(size_t i = 0; i < mapa.size() ; i++){
        for(size_t j = 0; j < mapa[i].size() ; j++){
            if(i == rx && j == ry){
                std::cout << "O" << " ";
            } else if(mapa[i][j] == 1){
                std::cout << "#" << " ";
            } else if(mapa[i][j] == 0){
                std::cout << " " << " ";
            } else if(mapa[i][j] == 2){
                std::cout << "X" << " ";
            }
        }
        std::cout << "\n";
    }
}

bool pegar_fruta(std::vector<std::vector<int>>& mapa, const robo& r){
    int rx, ry;
    rx = r.getX();
    ry = r.getY();

    //int aux_i, aux_j;

    for(size_t i = 0; i < mapa.size() ; i++){
        for(size_t j = 0; j < mapa[i].size() ; j++){
            if(mapa[i][j] == 2){
                //aux_i = i;
                //aux_j = j;

                if(i == rx && j == ry)
                    return true;
            }
        }
    }

    return false;
}

void limpar_tela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}