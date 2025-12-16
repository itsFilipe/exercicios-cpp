#include <iostream>

using namespace std;

int main() {

//character type
char middleInitial {'J'};
cout << "My middle initial is " << middleInitial << endl;

//integer types
unsigned short int examScore {55};  
cout << "My exam score was " << examScore << endl;

int countriesRepresented {65};
cout << "There were " << countriesRepresented << " countries represented in my meeting" << endl;

long peopleInCity {5'000'000};
cout << "There are about " << peopleInCity << " people in my city" << endl;

long long distanceToAlphaCentauri {9'460'730'472'580};
cout << "The distance to Alpha Centauri is " << distanceToAlphaCentauri << " kilometers" << endl;   

//floating point types
float carPayment {401.23};  
cout << "My car payment is " << carPayment << endl;

double pi {3.14159};
cout << "Pi is approximately " << pi << endl;

long double largeAmount {2.7e120};
cout << "A very large amount is " << largeAmount << endl;

//boolean type
bool gameOver {false};
cout << "The value of gameOver is " << gameOver << endl;

//overflow example
/*
short int value1 {30000};
short int value2 {1000};
short int product {value1 * value2};
cout << "The product of " << value1 << " and " << value2 << " is " << product << endl;
*/

return 0;
}