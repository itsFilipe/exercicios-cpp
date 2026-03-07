#include <iostream>
#include <cstdlib>
#include "robo.h"

void renderizar_mapa(std::vector<std::vector<int>>& mapa, const robo& r);
void nova_fruta(std::vector<std::vector<int>>& mapa);
bool pegar_fruta(std::vector<std::vector<int>>& mapa, const robo& r);
void limpar_tela();

int main() {
    srand(time(0));
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

            std::cout << "Deseja que o robo se alimente mais? S / N" << std::endl;
            char inp;
            std::cin >> inp;
            inp = toupper(inp);
            if(inp == 'S'){
                nova_fruta(mapa);
            } else {
                rodando = false;
            }
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

    for(size_t i = 0; i < mapa.size() ; i++){
        for(size_t j = 0; j < mapa[i].size() ; j++){
            if(mapa[i][j] == 2){
                if(i == rx && j == ry){
                    mapa[i][j] = 0;
                    return true;
                }
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

/*
    possivel melhoria nessa funcao, em vez de ser probabilistico, ser deterministico, ou seja
    em vez de percorrer tudo e gerar posicao aleatoria, tendo que ter condicao, varre o mapa e
    guarda apenas as solucoes possiveis, e nisso gera indices aleatorios entre essas solucoes
    Nao le o mapa a todo momento, apenas 1 vez o(n)
*/

void nova_fruta(std::vector<std::vector<int>>& mapa){
    bool position_not_ok = true;
    int rnd_numx, rnd_numy;

    while (position_not_ok) {
        rnd_numx = rand() % mapa.size();
        rnd_numy = rand() % mapa[0].size();

         if(mapa[rnd_numx][rnd_numy] == 0){
            mapa[rnd_numx][rnd_numy] = 2;
            position_not_ok = false;
        } 
    }
}
