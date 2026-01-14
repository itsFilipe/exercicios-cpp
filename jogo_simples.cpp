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
    Robo tentativa;

    tentativa.y = 0;
    tentativa.x = 1;

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

        #ifdef _WIN32
            system("cls"); // Se estiver no Windows
        #else
            system("clear"); // Se estiver no Linux/Mac
        #endif
        
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
        case 'W': tentativa.y -= 1; break;
        case 'A': tentativa.x -= 1; break;
        case 'S':  tentativa.y += 1; break; 
        case 'D': tentativa.x += 1; break;
        case 'Q': 
            cout << "Saindo..." << endl;
            continua = false; 
            break;
        default:
            cout << "Not a valid option" << endl;
            break;  
        }

        // Se tentativa.y for -1, a primeira condição falha e o C++ PARA de ler o resto.
        bool dentroDosLimites = (tentativa.y >= 0 && tentativa.y < mapa.size()) && 
                                (tentativa.x >= 0 && tentativa.x < mapa[0].size());

        // Só acessamos o mapa se estivermos dentro dos limites
        if (dentroDosLimites && mapa[tentativa.y][tentativa.x] == 0) {
            // Movimento Aprovado
            robo1.y = tentativa.y;
            robo1.x = tentativa.x;
        } 
        else {
            // Movimento Recusado (bateu na parede ou saiu do mundo)
            cout << "BATEU! Movimento invalido!" << endl;
            
            // Importante: Resetar a tentativa para o robô não ficar "desincronizado"
            tentativa.y = robo1.y;
            tentativa.x = robo1.x;
            
            // Dica: Um system("pause") ou cin.get() aqui ajuda o usuário a ler a mensagem de erro
            cin.ignore(); 
            cin.get();
        }
        }
            
    return 0;
}