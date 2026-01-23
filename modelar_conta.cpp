#include <iostream>
#include <string>

class ContaCorrente {
private:    
    size_t numero;
    std::string nome;
    int saldo;
public:
    void alterarNome(const std::string &nomeValor);
    void depositar(int depositoValor);
    void sacar(int saqueValor);
    size_t getNumero();
    std::string getNome();
    int getSaldo();

    ContaCorrente(size_t numeroValor, std::string nomeValor, int saldoValor = 0);
};

ContaCorrente::ContaCorrente(
    size_t numeroValor,
    std::string nomeValor,
    int saldoValor
) : numero(numeroValor), nome(nomeValor), saldo(saldoValor) {}

void ContaCorrente::alterarNome(const std::string &nomeValor){
    nome = nomeValor;
}

void ContaCorrente::depositar(int depositoValor){
    saldo += depositoValor;
}

void ContaCorrente::sacar(int saqueValor){
    saldo -= saqueValor;
}

size_t ContaCorrente::getNumero(){ return numero; }
std::string ContaCorrente::getNome(){ return nome; }
int ContaCorrente::getSaldo(){ return saldo; }

int main() {
    ContaCorrente conta1(1234, "Joao");
    
    std::cout << "Conta: " << conta1.getNumero() 
              << " | Nome: " << conta1.getNome() 
              << " | Saldo: " << conta1.getSaldo() << "\n";

    conta1.depositar(100);
    
    std::cout << "Conta: " << conta1.getNumero() 
              << " | Nome: " << conta1.getNome() 
              << " | Saldo: " << conta1.getSaldo() << "\n";

    return 0;
}
