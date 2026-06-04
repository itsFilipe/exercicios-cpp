/*
O Quadro de Medalhas
Foco: Inserção, Ordenação Customizada e Redimensionamento.
Cenário: Você está desenvolvendo um jogo e tem um std::vector<int> que guarda as pontuações históricas dos jogadores. 
Acabou de acontecer um torneio e você recebeu três novas pontuações de uma vez.
Seu Objetivo:
    Crie um vetor inicial com 5 pontuações aleatórias.
    Adicione 3 novas pontuações simuladas.
    Ordene o vetor do MAIOR para o MENOR (o padrão do C++ é do menor pro maior, você terá que descobrir como inverter isso de forma elegante).
    O seu jogo só mostra o "Top 5" na tela. Corte o vetor para que ele mantenha apenas os 5 primeiros elementos de forma permanente, descartando o resto.
    Imprima o pódio.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

void display(const std::vector<int> &vec) {
    std::cout << "[ ";
    std::for_each(vec.begin(), vec.end(),
        [](int x) { std::cout << x << " ";});
    std::cout << "]" << std::endl;
}

int main(){
    std::vector<int> pontuacoes {100, 77, 40, 76, 50};

    pontuacoes.push_back(33);
    pontuacoes.push_back(99);
    pontuacoes.push_back(43);

    display(pontuacoes);

    std::sort(pontuacoes.begin(), pontuacoes.end(), std::greater<int>());
    std::vector<int> pontuacoes2 = pontuacoes;

    //agora eu posso dar erase em todos apos o quinto e dar shrink to fit
    pontuacoes.erase(pontuacoes.begin() + 5, pontuacoes.end());
    // ou pontuacoes2.resize(5);
    pontuacoes.shrink_to_fit();
    display(pontuacoes);
    
    // Outra alternativa, criar uma copia de um vector com apenas os 5 primeiros
    std::vector<int> primeiros_cinco(pontuacoes2.begin(), pontuacoes2.begin() + 5);
    display(primeiros_cinco);

    return 0;
}

