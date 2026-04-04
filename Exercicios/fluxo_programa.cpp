// Section 9
// Challenge
/*    
    This challenge is about using a collection (list) of integers and allowing the user
    to select options from a menu to perform operations on the list.
    
    Your program should display a menu options to the user as follows:
    
    P - Print numbers
    A - Add a number
    M - Display mean of the numbers
    S - Display the smallest number
    L - Display the largest number
    Q - Quit

    Enter your choice:
    
The program should only accept valid choices from the user, both upper and lowercase selections should be allowed.
If an illegal choice is made, you should display, "Unknown selection, please try again" and the menu options should be
displayed again.


If the user enters 'P' or 'p', you should display all of the elements (ints) in the list.
If the list is empty you should display "[] - the list is empty"
If the list is not empty then all the list element should be displayed inside square brackets separated by a space. 
For example, [ 1 2 3 4 5 ]
      
If the user enters 'A' or 'a' then you should prompt the user for an integer to add to the list 
which you will add to the list and then display it was added. For example, if the user enters 5
You should display, "5 added".
Duplicate list entries are OK

If the user enters 'M' or 'm'  you should calculate the mean or average of the elements in the list and display it.
If the list is empty you should display, "Unable to calculate the mean - no data"

If the user enters 'S' or 's' you should display the smallest element in the list.
For example, if the list contains [2 4 5 1],  you should display, "The smallest number is 1"
If the list is empty you should display, "Unable to determine the smallest number - list is empty"

If the user enters 'L' or 'l' you should display the largest element in the list
For example, if the list contains [2 4 5 1], you should display, "The largest number is 5"
If the list is empty you should display, "Unable to determine the largest number - list is empty"

If the user enters 'Q' or 'q' then you should display 'Goodbye" and the program should terminate.

Before you begin. Write out the steps you need to take and decide in what order they should be done.
Think about what loops you should use as well as what you will use for your selection logic.

This exercise can be challenging! It may likely take a few attempts before you complete it -- that's OK!

Finally, be sure to test your program as you go and at the end.

Hint: Use a vector!

Additional functionality if you wish to extend this program.

- search for a number in the list and if found display the number of times it occurs in the list
- clearing out the list (make it empty again) (Hint: the vector class has a .clear() method)
- don't allow duplicate entries
- come up with your own ideas!

Good luck!

*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void menu();
bool lista_vazia(vector <int> l);
void print_num(vector <int> l);
void add_num(vector <int> &l);
void mean_num(vector <int> l);
void smallest_num(vector <int> l);
void largest_num(vector <int> l);
void order_list(vector <int> &l);
void find_number(vector <int> l);

int main() {
    
    vector <int> lista;
    char op;

    do
    {
        menu();
        cin >> op;
        op = toupper(op);

        switch (op)
        {
        case 'P':
            if(lista_vazia(lista) == false){
                print_num(lista);
            } 
            break;

        case 'A':   
            add_num(lista);
            break;

        case 'M':
            if(lista_vazia(lista) == false){
                mean_num(lista);
            } 
            break;

        case 'S':
            if(lista_vazia(lista) == false){
                smallest_num(lista);
            }
            break;

        case 'L':
            if(lista_vazia(lista) == false){
                largest_num(lista);
            }    
            break;

        case 'Q':   
            cout << "Goodbye" << "\n";
            break;  

        case 'O':
            if(lista_vazia(lista) == false){
                order_list(lista);
            }  
            break;

        case 'F':
            if(lista_vazia(lista) == false){
                find_number(lista);
            }  
            break;
            
        default:
            cout << "Unknown selection, please try again" << "\n";
            break;
        }

    } while (op != 'Q');

    return 0;
}

void menu() {
    cout << "\n";
    cout << "P - Print numbers" << "\n";
    cout << "A - Add a number" << "\n";
    cout << "M - Display mean of the numbers" << "\n";
    cout << "S - Display the smallest number" << "\n";
    cout << "L - Display the largest number" << "\n";
    cout << "O - Order the list" << "\n";
    cout << "F - Find a number in the list" << "\n";
    cout << "Q - Quit" << "\n";
    cout << "\nEnter your choice:" << "\n";
}

bool lista_vazia(vector <int> l){
    if(l.empty() == 1){
        cout << "[] - the list is empty" << "\n";
        return true;
    } else {
        return false;
    }
}

void print_num(vector <int> l){
    cout << "[ ";

    for(size_t i{0}; i < l.size(); ++i){
        cout << l.at(i) << " ";
    }

    cout << "]" << "\n";
}

void add_num(vector <int> &l){
    int num;
    cin >> num;
    l.push_back(num);
    cout << num << " was added" << "\n";
}

void mean_num(vector <int> l){
    double mean {0};

    for(size_t i{0}; i < l.size(); ++i){
        mean += l.at(i);
    }

    mean = mean / l.size();
    cout << "The mean is " << mean << "\n";
}

void smallest_num(vector <int> l){
    int menor = l.at(0);

    for(size_t i{1}; i < l.size(); ++i){ //?
        if(menor > l.at(i))
            menor = l.at(i);
    }

    cout << "The smallest number is " << menor << "\n";
}

void largest_num(vector <int> l){
    int maior = l.at(0);

    for(size_t i{1}; i < l.size(); ++i){ //?
        if(maior < l.at(i))
            maior = l.at(i);
    }

    cout << "The biggest number is " << maior << "\n";
}       

void order_list(vector <int> &l){
    sort(l.begin(), l.end());

    cout << "The list has been sorted" << "\n";
}

void find_number(vector <int> l) {
    int num;
    bool found = false;
    cout << "Enter the number: " << "\n";
    cin >> num;

    for(size_t i{0}; i < l.size() ; ++i){
        if(l.at(i) == num){
            cout << "Number " << num << " was found at the position "; 
            cout << i + 1 << " of the list" << "\n";
            found = true;
        } 
    }

    if(found == false) {
            cout << "Number " << num << "was not found at the list" << "\n";
    }
}

/*
Código refatorado por gemini para estudo pessoal.

#include <iostream>
#include <vector>
#include <algorithm> // Para sort, min_element, max_element
#include <numeric>   // Para accumulate (soma de vetores)

using namespace std;

// Protótipos das funções
void exibir_menu();
void imprimir_lista(const vector<int> &v); // Passagem por referência constante
void adicionar_numero(vector<int> &v);
void exibir_media(const vector<int> &v);
void exibir_menor(const vector<int> &v);
void exibir_maior(const vector<int> &v);
void ordenar_lista(vector<int> &v);
void buscar_numero(const vector<int> &v);

int main() {
    vector<int> lista;
    char escolha;

    do {
        exibir_menu();
        cin >> escolha;
        escolha = toupper(escolha);

        switch (escolha) {
            case 'P': imprimir_lista(lista); break;
            case 'A': adicionar_numero(lista); break;
            case 'M': exibir_media(lista); break;
            case 'S': exibir_menor(lista); break;
            case 'L': exibir_maior(lista); break;
            case 'O': ordenar_lista(lista); break;
            case 'F': buscar_numero(lista); break;
            case 'Q': cout << "Goodbye!" << endl; break;
            default:  cout << "Unknown selection, please try again" << endl;
        }
    } while (escolha != 'Q');

    return 0;
}

void exibir_menu() {
    cout << "\n--- Opcoes ---" << "\n"
         << "P - Print numbers\n"
         << "A - Add a number\n"
         << "M - Display mean\n"
         << "S - Display smallest\n"
         << "L - Display largest\n"
         << "O - Order list\n"
         << "F - Find a number\n"
         << "Q - Quit\n"
         << "\nEnter choice: ";
}

// 1. Passagem por const vector<int> &v: Não copia o vetor e garante que não será alterado
void imprimir_lista(const vector<int> &v) {
    if (v.empty()) {
        cout << "[] - the list is empty" << endl;
        return;
    }
    cout << "[ ";
    for (const auto &num : v) { // 2. Range-based for loop: mais limpo e moderno
        cout << num << " ";
    }
    cout << "]" << endl;
}

void adicionar_numero(vector<int> &v) {
    int num;
    cout << "Enter an integer to add: ";
    cin >> num;
    v.push_back(num);
    cout << num << " added" << endl;
}

void exibir_media(const vector<int> &v) {
    if (v.empty()) {
        cout << "Unable to calculate the mean - no data" << endl;
        return;
    }
    // 3. std::accumulate: Forma idiomática de somar valores em C++
    double soma = accumulate(v.begin(), v.end(), 0.0);
    cout << "The mean is: " << soma / v.size() << endl;
}

void exibir_menor(const vector<int> &v) {
    if (v.empty()) {
        cout << "Unable to determine the smallest number - list is empty" << endl;
        return;
    }
    // 4. std::min_element: Retorna um iterador para o menor elemento
    auto menor = min_element(v.begin(), v.end());
    cout << "The smallest number is " << *menor << endl;
}

void exibir_maior(const vector<int> &v) {
    if (v.empty()) {
        cout << "Unable to determine the largest number - list is empty" << endl;
        return;
    }
    auto maior = max_element(v.begin(), v.end());
    cout << "The largest number is " << *maior << endl;
}

void ordenar_lista(vector<int> &v) {
    if (v.empty()) {
        cout << "List is empty, nothing to sort." << endl;
        return;
    }
    sort(v.begin(), v.end());
    cout << "The list has been sorted" << endl;
}

void buscar_numero(const vector<int> &v) {
    if (v.empty()) {
        cout << "List is empty." << endl;
        return;
    }
    int alvo;
    cout << "Enter the number to find: ";
    cin >> alvo;

    int contador = 0;
    for (size_t i = 0; i < v.size(); ++i) {
        if (v[i] == alvo) {
            cout << "Found " << alvo << " at index " << i << endl;
            contador++;
        }
    }

    if (contador == 0) 
        cout << alvo << " was not found" << endl;
    else 
        cout << "Total occurrences: " << contador << endl;
}

*/