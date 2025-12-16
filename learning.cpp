#include <iostream>

int main() {
    int x;

    std::cout << "Digite um numero: ";
    std::cin >> x;
    std::cout << "Seu numero e: " << x << std::endl;
    
    return 0;
}

/*
**** LEARNING C++ BASICS

#### types in c++ 

int myNum = 5;               // Integer (whole number)
float myFloatNum = 5.99;     // Floating point number
double myDoubleNum = 9.98;   // Floating point number
char myLetter = 'D';         // Character
bool myBoolean = true;       // Boolean
string myText = "Hello";     // String

boolean	|1 byte      |Stores true or false values
char    |1 byte      |Stores a single character/letter/number, or ASCII values
int	    |2 or 4 bytes|Stores whole numbers, without decimals
float   |4 bytes     |Stores fractional numbers, containing one or more decimals. Sufficient for storing 6-7 decimal digits
double  |8 bytes	 |Stores fractional numbers, containing one or more decimals. Sufficient for storing 15 decimal digits

#### display variables

int myAge = 35;
cout << "I am " << myAge << " years old.";

string name = "John";
int age = 35;
double height = 6.1;

cout << name << " is " << age << " years old and " << height << " feet tall.";

#### Add Variables Together

int x = 5;
int y = 6;
int sum = x + y;
cout << sum;

#### Get input from user

int x; 
cout << "Type a number: "; // Type a number and press enter
cin >> x; // Get user input from the keyboard
cout << "Your number is: " << x; // Display the input value

*/

