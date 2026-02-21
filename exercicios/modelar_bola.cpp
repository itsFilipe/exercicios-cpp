#include <iostream>

class Bola{
private:
    std::string Cor;
    std::string Material;
public:
    void trocar_cor(std::string novaCor);
    std::string mostrar_cor();

    Bola(std::string Cor_valor = "Preta", std::string Material_valor = "Plastico");
};

void Bola::trocar_cor(std::string novaCor){
    Cor = novaCor;
};

std::string Bola::mostrar_cor(){
    return Cor;
};

//inicializador de construtor, é uma forma mais eficiente de inicializar atributos da classe
Bola::Bola(std::string Cor_valor, std::string Material_valor)
    :Cor(Cor_valor), Material(Material_valor) {}

int main(){

    Bola minha_bola;

    std::cout << minha_bola.mostrar_cor() << "\n";

    minha_bola.trocar_cor("Laranja");

    std::cout << minha_bola.mostrar_cor() << "\n";

    return 0;
}