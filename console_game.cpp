#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

class Lutador{
private:
    std::string nome;
    size_t vida;
    size_t dano;
    size_t vida_maxima; 
public:
    Lutador(std::string n, size_t v, size_t d, size_t vm = 0);

    std::string getNome() const;
    size_t getVida() const;
    size_t getDano() const;
    size_t getVidaMaxima() const;

    void atacar(Lutador &l);
    void curar(Lutador &l);
};

std::string Lutador::getNome() const { return nome; }
size_t Lutador::getVida() const { return vida; }
size_t Lutador::getDano() const { return dano; }
size_t Lutador::getVidaMaxima() const { return vida_maxima; }

void Lutador::atacar(Lutador &l) {
    size_t dano_causado = (rand() % dano) + 1;

    if (l.vida <= dano_causado) {
        l.vida = 0;
    } else {
        l.vida -= dano_causado;
    }

    std::cout << nome << " atacou " << l.nome << " causando " << dano_causado << " de dano.\n";
}

void Lutador::curar(Lutador &l) {
    if(vida == vida_maxima){
        std::cout << nome << " ja esta com vida maxima" << std::endl;
        return;
    } 

    size_t cura = (rand() % 30) + 10;

    if (l.vida + cura > l.vida_maxima) {
        l.vida = l.vida_maxima;
    } else {
        l.vida += cura;
    }

    std::cout << nome << " curou " << l.nome << " em " << cura << " pontos de vida.\n";
}

//list initializer for constructor
Lutador::Lutador(std::string n, size_t v, size_t d, size_t vm)
    : nome(n), vida(v), dano(d), vida_maxima(vm) {}

int main() {
    srand(time(0));
    Lutador heroi("Filipe", 125, 50, 125);
    Lutador vilao("Vilao", 150, 50, 150);

    while(heroi.getVida() > 0 && vilao.getVida() > 0) {
        system("cls"); 

        std::cout << "--- BATALHA ---\n";
        std::cout << heroi.getNome() << " HP: " << heroi.getVida() << "\n";
        std::cout << vilao.getNome() << " HP: " << vilao.getVida() << "\n\n";

        std::cout << "O que voce quer fazer?" << std::endl;
        std::cout << "[1] Atacar" << std::endl;
        std::cout << "[2] Curar" << std::endl;

        size_t escolha {0};
        std::cin >> escolha;
        std::cin.ignore();

        switch (escolha)
        {
        case 1: heroi.atacar(vilao); break;
        case 2: heroi.curar(heroi); break;
        default: std::cout << "Digite uma opcao valida" << std::endl; break;   
        }

        if(vilao.getVida() == 0) {
            std::cout << "\nO INIMIGO CAIU!\n";
            break; 
        }

        std::cout << "\nO inimigo se prepara para atacar...\n";
        vilao.atacar(heroi); 

        if(heroi.getVida() == 0) {
            std::cout << "\nVOCE MORREU!\n";
            break;
        }

        std::cout << "\n(Pressione ENTER para proximo turno)";
        std::cin.get(); 
    }

    return 0;
}