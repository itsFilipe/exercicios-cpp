//jogo simples para movimentar robo sem deixar bater nas paredes.

#include <iostream>
#include <vector>

using namespace std;

int main() {

    //mapa[][] linha/coluna
    vector <vector <int>> mapa = 
    {
        {1,0,0,0,1},
        {1,0,0,0,1},
        {1,0,0,0,1},
        {1,0,0,0,1},
        {1,0,0,0,1}
    }; 

    struct Robo {
        int y, x;
    };

    Robo robo1;

    robo1.y = 0;
    robo1.x = 1;

    /*
    for(size_t i{0}; i < mapa.size(); ++i){
        for(size_t j{0}; j < mapa.at(i).size(); ++j){
            cout << mapa[i][j] << " ";
        }
        cout << endl;
    }

    mais moderno

    for (const auto& linha : mapa) {
        for (auto elemento : linha) {
            std::cout << elemento << " ";
        }
        std::cout << std::endl;
    }
    */

    bool continua = true;

    while (continua){
        
        for(size_t i{0}; i < mapa.size(); ++i){
            for(size_t j{0}; j < mapa.at(i).size(); ++j){
                if(robo1.y == i && robo1.x == j)
                    cout << " # ";
                else if (mapa[i][j] == 0)
                    cout << " - ";
                else 
                    cout << " | ";
            }
            cout << endl;
        }

        char op;

        cout << "W - CIMA" << endl;
        cout << "A - ESQUERDA" << endl;
        cout << "S - BAIXO" << endl;
        cout << "D - DIREITA" << endl;
        cout << "Q - SAIR" << endl;
        cout << "Insira um comando" << endl;
        cin >> op;
        op = toupper(op);

        switch (op)
        {
        case 'W':
            //IRA SUBIR UMA LINHA
            robo1.y -= 1;
            break;

        case 'A':
            //IRA MOVER 1 COLUNA PRA ESQUERDA
            robo1.x -= 1;
            break;

        case 'S':
            //IRA DESCER UMA LINHA
            robo1.y += 1;
            break;

        case 'D':
            //IRA MOVER 1 COLUNA PRA DIREITA
            robo1.x += 1;
            break;

        case 'Q':
            cout << "Saindo..." << endl;
            continua = false;
            break;
        
        default:
            cout << "Not a valid option" << endl;
            break;
        }
    }
    
    return 0;
}