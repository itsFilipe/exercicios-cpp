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
    size_t pocao_vida;
public:
    Lutador(std::string n, size_t v, size_t d, size_t vm = 0, size_t pv = 0);

    std::string getNome() const;
    size_t getVida() const;
    size_t getDano() const;
    size_t getVidaMaxima() const;
    size_t getPocaoVida() const;

    void atacar(Lutador &l);
    void curar();
};

std::string Lutador::getNome() const { return nome; }
size_t Lutador::getVida() const { return vida; }
size_t Lutador::getDano() const { return dano; }
size_t Lutador::getVidaMaxima() const { return vida_maxima; }
size_t Lutador::getPocaoVida() const { return pocao_vida; }

void Lutador::atacar(Lutador &l) {
    size_t dano_causado = (rand() % dano) + 1;

    if (l.vida <= dano_causado) {
        l.vida = 0;
    } else {
        l.vida -= dano_causado;
    }

    std::cout << nome << " atacou " << l.nome << " causando " << dano_causado << " de dano.\n";
}

void Lutador::curar() {
    if(vida == vida_maxima){
        std::cout << nome << " ja esta com vida maxima" << std::endl;
        return;
    } 

    if(pocao_vida == 0){
        std::cout << "As pocoes de cura acabaram" << std::endl;
        return;
    }

    size_t cura = (rand() % 30) + 10;

    if (vida + cura > vida_maxima) {
        vida = vida_maxima;
    } else {
        vida += cura;
    }

    std::cout << "Curando..." << std::endl;
    std::cout << nome << " curou " << nome << " em " << cura << " pontos de vida.\n";
    pocao_vida -= 1;
    std::cout << "Restam " << pocao_vida << " pocoes" << std::endl; 
    
}

//list initializer for constructor
Lutador::Lutador(std::string n, size_t v, size_t d, size_t vm, size_t pv)
    : nome(n), vida(v), dano(d), vida_maxima(vm), pocao_vida(pv) {}

int main() {
    srand(time(0));
    Lutador heroi("Filipe", 125, 50, 125, 3);
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
        case 2: heroi.curar(); break;
        default: std::cout << "Digite uma opcao valida" << std::endl; break;   
        }

        if(vilao.getVida() == 0) {
            std::cout << "\nO INIMIGO CAIU!\n";
            break; 
        }

        if(escolha == 1){
            std::cout << "\nO inimigo se prepara para atacar...\n";
            vilao.atacar(heroi); 
        }
        
        if(heroi.getVida() == 0) {
            std::cout << "\nVOCE MORREU!\n";
            break;
        }

        std::cout << "\n(Pressione ENTER para proximo turno)";
        std::cin.get(); 
    }

    return 0;
} 