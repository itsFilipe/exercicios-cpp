#include <iostream>
#include "robo.h"

void renderizar_mapa(std::vector<std::vector<int>>& mapa, const robo& robo);

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
        std::cout << "Comando: W, A, S, D -- Q para sair" << std::endl;
        std::cin >> comando;
        comando = toupper(comando); 

        if(comando == 'Q') {
            rodando = false;
            //continue;
        }

        meu_robo.tentar_mover(comando, mapa);
    }

    

    return 0;
}

void renderizar_mapa(std::vector<std::vector<int>>& mapa, const robo& robo) {
    for(size_t i = 0; i < mapa.size() ; i++){
        for(size_t j = 0; j < mapa[i].size() ; j++){
            //condições para renderizar
        }
    }


}