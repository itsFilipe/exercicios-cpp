#include <iostream>
#include <cstring>       //for c-style string functions
#include <cctype>        //for character-based functions

using namespace std;    

int main()
{
    char first_name[20] {};
    char  last_name[20] {};
    char  full_name[50] {};
    char       temp[50] {};
    
    cout << first_name;      //Will likely display garbage, se nao estiver inicializado!

    cout << "Please enter your first name: ";
    cin >> first_name;

    cout << "Please enter your last name: ";
    cin >> last_name;
    cout << "-------------------------------" << endl; 
    
    cout << "Hello, " << first_name << " your first name has " << strlen(first_name) << " characters" << endl;
    cout << "and your last name, " << last_name << " has " << strlen(last_name) << " characters" << endl;

    strcpy(full_name, first_name);           //first_name to full_name
    strcat(full_name, " ");                  //concatenate full_name and a space
    strcat(full_name, last_name);            //concatenate last_name to full_name
    cout << "Your full name is " << full_name << endl;

    /*Nesse caso sem getline, daria erro pois no primeiro espaço iria parar o input

    cout << "-------------------------------" << endl;
    cout << "Enter your full name: ";
    cin >> full_name;

    cout << "Your full name is " << full_name << endl;

    */

    full_name[0] = '\0'; //zera o full_name para evitar lixo no buffer
    cin.ignore();       //ignora o lixo que ficou no buffer do cin
    cout << "-------------------------------" << endl;

    cout << "Enter your full name: ";
    cin.getline(full_name, 50); //Usa getline para pegar o nome completo com espacos, pois cin sozinho para no primeiro espaco e sobra lixo no buffer
    cout << "Your full name is " << full_name << endl;

    cout << "-------------------------------" << endl;
    strcpy(temp, full_name); //atribui full_name a temp
    if(strcmp(temp, full_name) == 0) //compara os dois, se iguais retorna 0
        cout << temp << " and " << full_name << " are the same" << endl;
    else
        cout << temp << " and " << full_name << " are different" << endl;
        
    cout << "-------------------------------" << endl;
    
    /*For comparando letra por letra, se for alpha (letra) vira UPPERCASE*/
    for(size_t i{ 0 }; i < strlen(full_name); ++i) { //size_t para evitar warning, é bom utilizar quando lidamos com tamanhos que nunca serao negativos
        if(isalpha(full_name[i]))
            full_name[i] = toupper(full_name[i]);
    }
    cout << "Your full name is " << full_name << endl; 

    cout << "-------------------------------" << endl;
    if(strcmp(temp, full_name) == 0)
        cout << temp << " and " << full_name << " are the same" << endl;
    else
        cout << temp << " and " << full_name << " are different" << endl;

    cout << "-------------------------------" << endl;
    cout << "Result of comparing " << temp << " and " <<  full_name <<  ": " << strcmp(temp, full_name) << endl;
    cout << "Result of comparing " << full_name << " and " <<  temp <<  ": " << strcmp(full_name, temp) << endl;

    cout  << endl;
    return 0;
}
