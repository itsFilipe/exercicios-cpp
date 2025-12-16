 #include <iostream>

 using namespace std;

 double multiplicar(double a, double b); 

 int main() {

    cout << "Quantidade de quartos a serem limpos: ";

    int qtd_quarto {0};
    cin >> qtd_quarto;

    //const define que variavel nao pode ser modificada 
    const double preco_por_quarto {32.6};
    const double quantidade_taxa {0.06};

    double custo = multiplicar(preco_por_quarto, qtd_quarto);
    double taxa = multiplicar(custo, quantidade_taxa);

    cout << "\nQuantidade de quartos: " << qtd_quarto << endl;
    cout << "Preco por quarto: " << preco_por_quarto << endl;
    cout << "Custo: " << custo << endl;
    cout << "Taxa: " << taxa << "\n\n";
    cout << "Total: " << custo + taxa << endl;

    cout << "\n";

    return 0;
 }

  double multiplicar(double a, double b) {
    return a * b;
 }