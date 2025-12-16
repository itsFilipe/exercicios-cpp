#include <iostream>
#include <iomanip> // Required for fixed and setprecision

using namespace std;

int main() {
 
    double slr, reaj, per;

    // Use manipulators to format output as currency (two decimal places)
    cout << fixed << setprecision(2);

    cin >> slr;
    
    if(slr <= 400.00) {
        per = 0.15;
    } else if (slr <= 800.00) {
        per = 0.12;
    } else if (slr <= 1200.00) {
        per = 0.10;
    } else if (slr <= 2000.00) {
        per = 0.07;
    } else {
        per = 0.04;
    }
    
    reaj = per * slr;
    slr += reaj;

    cout << "Novo salario: " << slr << endl;
    cout << "Reajuste ganho: " << reaj << endl;

    cout << defaultfloat; // Reset to default float formatting
    cout << "Em percentual: " << per * 100 << " %" << endl;
    
    return 0;
}