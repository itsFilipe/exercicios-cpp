#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string message;
    cout << "Digite uma mensagem: ";
    getline(cin, message);
    cout << "\nSaida: \n";

    size_t n = message.length();

    for (size_t i = 1; i <= n; ++i) {
        // Imprime os espaços para centralizar
        // A quantidade de espaços é (total de caracteres - caracteres na linha atual)
        for (size_t s = 0; s < n - i; ++s) {
            cout << " ";
        }

        // Parte central e esquerda (ex: "ABC")
        string piramide = message.substr(0, i);

        // Parte direita espelhada (ex: "BA")
        if (piramide.length() > 1) {
            string aux = piramide.substr(0, piramide.length() - 1);
            reverse(aux.begin(), aux.end());
            piramide += aux;
        }

        cout << piramide << endl;
    }

    cout << "\n";

    return 0;
}

/*

Teacher solution

// Letter Pyramid
// Written by Frank J. Mitropoulos

#include <iostream>
#include <string>

int main()
{
    std::string letters{};

    std::cout << "Enter a string of letters so I can create a Letter Pyramid from it: ";
    getline(std::cin, letters);

    size_t num_letters = letters.length();

    int position {0};

    // for each letter in the string
    for (char c: letters) {

        size_t num_spaces = num_letters - position;
        while (num_spaces > 0) {
            std::cout << " ";
            --num_spaces;
        }

        // Display in order up to the current character
        for (size_t j=0; j < position; j++) {
            std::cout << letters.at(j);
        }

        // Display the current 'center' character
        std::cout << c;

        // Display the remaining characters in reverse order
        for (int j=position-1; j >=0; --j) {
            // You can use this line to get rid of the size_t vs int warning if you want
            auto k = static_cast<size_t>(j);
            std::cout << letters.at(k);
        }

        std::cout << std::endl; // Don't forget the end line
        ++position;
    }

    return 0;
}





*/