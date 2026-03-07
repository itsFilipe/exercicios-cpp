#include "robo.h"
#include <vector>

robo::robo(int x, int y) 
    :  x(1), y(1) {}

bool robo::tentar_mover(char comando, std::vector<std::vector<int>>& mapa) {
    //utiliza auxiliares

    int aux_x = x;
    int aux_y = y;

    switch (comando) {
            case 'W': aux_x--; break;
            case 'S': aux_x++; break;
            case 'A': aux_y--; break;
            case 'D': aux_y++; break;
            default: return false; // Comando inválido
        }

    /*
        necessario checar se passou dos limites
    */

    /* mapa.size() retorna o tamanho das linhas  e mapa[0].size retorna colunas*/

    if (aux_y < 0 || aux_y >= mapa.size() || 
            aux_x < 0 || aux_x >= mapa[0].size()) {
            return false; // Saiu do mapa
        }

    if(mapa[aux_x][aux_y] == 1){ //bateu em uma parede
        return false;
    }

    //passou as validações quer dizer que está correto
    x = aux_x;
    y = aux_y;

    return true;
}

