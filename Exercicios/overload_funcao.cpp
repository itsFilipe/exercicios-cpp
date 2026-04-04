#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print(int);
void print(double);
void print(string);
void print(string, string);
void print(vector<string>);

/*
Overload de funcao nada mais é do que utilizar o mesmo nome de funcao,
mas utilizar tipos de argumentos diferentes. É necessario tomar cuidado
caso for utilizar parametro default, se tiver mais de 1 default 
ira dar erro de ambiguidade, compilador não irá saber qual escolher
*/

void print(int num) {
    cout << "Printing int: " << num << endl;
}

void print(double num) {
    cout << "Printing double: " << num << endl;
}

void print(string s) {
    cout << "Printing string: " << s << endl;
}

void print(string s, string t) {
    cout << "Printing 2 strings: " << s << " and " << t << endl;
}

void print(vector<string> v) {
    cout << "Printing vector of strings: " ;
    for (auto s: v )
        cout << s + " ";
    cout << endl;
}

int main() {
    print(100);    // int
    print('A');     //  character is always promoted to int should print 65 ASCII ('A')
    
    print(123.5);   // double
    print(123.3F);  // Float is promoted to double
    
    print("C-style string");  // C-style string is converted to a C++ string
    
    string s {"C++ string"};    
    print(s);       // C++ string
    
    print("C-style string", s); // First argument is converted to a C++ string
    
    vector<string> nomes {"Larry", "Moe", "Curly"};
    print(nomes);
    
    cout << endl;
    return 0;
}

