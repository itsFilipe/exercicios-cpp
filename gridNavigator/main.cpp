#include <iostream>
#include <cstdlib>
#include <queue>

#include "robo.h"

void renderizar_mapa(std::vector<std::vector<int>>& mapa, const robo& r);
void nova_fruta(std::vector<std::vector<int>>& mapa);
void encontra_caminho(std::vector<std::vector<int>>& mapa, Ponto começo, Ponto fruta);
bool pegar_fruta(std::vector<std::vector<int>>& mapa, const robo& r);
void limpar_tela();

struct Ponto {
    size_t x, y;

    // Sobrecarga do operador de igualdade para facilitar a comparação 
    bool operator==(const Ponto& other) const {
        return x == other.x && y == other.y;
    }
};

/*  
    Proximas melhorias, implementar funcao em que o robo encontra o caminho
    mais curto p fruta, por meio de algoritmo de busca, como bfs ou a* por exemplo, e o robo se move automaticamente
    para a fruta, e quando chegar na fruta, o processo se repete, gerando nova fruta e o robo se movendo novamente
*/

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
    Nao le o mapa a todo momento, apenas 1 vez o(n) -- OK!
*/

void nova_fruta(std::vector<std::vector<int>>& mapa){
    std::vector<Ponto> lista_cord_ok;

    for(size_t i = 0; i < mapa.size() ; i++){
        for(size_t j = 0; j < mapa[i].size() ; j++){
            if(mapa[i][j] == 0){ //guardando coordenadas possiveis
                lista_cord_ok.push_back({i,j}); 
            }
        }
    }
    
    if (lista_cord_ok.size() == 0){
        std::cout << "Nao tem mais lugar para colocar a fruta, parabens voce venceu o jogo!!!" << std::endl;
        return;
    }

    int indice_random;
    indice_random = rand() % lista_cord_ok.size();

    auto p = lista_cord_ok.at(indice_random);
    mapa[p.x][p.y] = 2;
}

void encontra_caminho(std::vector<std::vector<int>>& mapa, Ponto comeco, Ponto alvo){

    int rows = mapa.size();
    int col  = mapa[0].size();

    //primeiro criar espelho
    std::vector<std::vector<bool>> passou(rows, std::vector<bool>(col, false));

    //auxiliares para encontrar vizinhos
    int dr[] = {-1, 1, 0, 0}; //sobe, desce
    int dc[] = { 0, 0,-1, 1}; //esquerda, direita

    //crio fila, insiro o ponto inicial, marco como passou
    std::queue<Ponto> q;
    q.push(comeco);
    passou[comeco.x][comeco.y] = true;
    bool encontrou = false;

    while (!q.empty()) //enqt nao estiver vazia
    {
        //Pega elemento e encontra vizinhos

        Ponto atual = q.front();
        q.pop();

        // Condição de sucesso
        if (atual == alvo) {
            encontrou = true;
            break;
        }

        //atinge vizinhos, valida e insere na fila
        for(size_t i = 0; i < 4; i++){
            int nova_r = atual.x + dr[i];
            int nova_c = atual.y + dc[i];

            //validar de ponto esta dentro dos limites, nao foi visitado, e nao é parede..
            if(nova_r >= 0 && nova_r <= rows && nova_c >= 0 && nova_c <= col && !passou[nova_r][nova_c] && mapa[nova_r][nova_c] != 1){

                passou[nova_r][nova_c] = true;

                Ponto aux;
                aux.x = nova_r;
                aux.y = nova_c;

                q.push(aux);
            }
        }
    }
    
    /* 
    a duvida que tenho no momento, vou encontrar o caminho, ok, mas eu vou ter que
    salvar ele, porque vou ter que aplicar esse caminho pro meu robo execeutar, certo? 
    */

}

