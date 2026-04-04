#include <iostream>
#include <string>
#include <iomanip>

class Carro {
public:
    std::string modelo;
    double capacidade_tanque;
    double nivel_atual;

    Carro(std::string m, double cap) : modelo(m), capacidade_tanque(cap), nivel_atual(0) {}

    void status() {
        std::cout << "Carro: " << modelo << " | Tanque: " << nivel_atual << "/" << capacidade_tanque << " L" << std::endl;
    }
};

class BombaCombustivel {
public:
    std::string tipo_combustivel;
    double valor_litro;
    double estoque_bomba;

    BombaCombustivel(std::string tipo, double valor, double estoque) 
        : tipo_combustivel(tipo), valor_litro(valor), estoque_bomba(estoque) {}

    // bomba recebe um Carro por referência (&)
    void abastecerCarro(Carro &veiculo, double valor_dinheiro) {
        double litros_pedidos = valor_dinheiro / valor_litro;

        std::cout << "\n>>> Tentando abastecer R$ " << valor_dinheiro << " (" << litros_pedidos << "L)..." << std::endl;

        // Verificar estoque da bomba
        if (litros_pedidos > estoque_bomba) {
            std::cout << "ERRO: Bomba sem combustivel suficiente!" << std::endl;
            return;
        }

        // verificar capacidade do tanque do carro
        double espaco_no_tanque = veiculo.capacidade_tanque - veiculo.nivel_atual;
        
        if (litros_pedidos > espaco_no_tanque) {
            std::cout << "AVISO: O combustivel transbordaria! Abastecendo apenas ate encher o tanque." << std::endl;
            litros_pedidos = espaco_no_tanque;
        }

        // Executa a transação
        estoque_bomba -= litros_pedidos;         // Retira da bomba
        veiculo.nivel_atual += litros_pedidos;    // Coloca no carro

        std::cout << "SUCESSO: Abastecimento concluido!" << std::endl;
        std::cout << "Total pago: R$ " << litros_pedidos * valor_litro << std::endl;
    }
};

int main() {
    std::cout << std::fixed << std::setprecision(2);

    BombaCombustivel bomba("Gasolina", 5.80, 1000.0);
    Carro meuCarro("Fusca", 40.0);

    std::cout << "--- STATUS INICIAL ---" << std::endl;
    std::cout << "Bomba tem: " << bomba.estoque_bomba << "L" << std::endl;
    meuCarro.status();

    bomba.abastecerCarro(meuCarro, 100.0); // Abastece R$ 100

    std::cout << "\n--- APOS ABASTECIMENTO 1 ---" << std::endl;
    meuCarro.status();
    std::cout << "Bomba agora tem: " << bomba.estoque_bomba << "L" << std::endl;

    bomba.abastecerCarro(meuCarro, 500.0);

    std::cout << "\n--- STATUS FINAL ---" << std::endl;
    meuCarro.status();

    return 0;
}

//proximos passos
// criar um vetor (array) de carros e uma lista de bombas
// permitir ao usuario escolher qual carro abastecer e qual bomba usar
// implementar interface de menu para interagir com o usuario
