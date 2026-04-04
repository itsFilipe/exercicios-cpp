#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    double score, sum = 0.0;

    cout << fixed << setprecision(2);

    for (int count = 0; count < 2; ) {  
        cin >> score;

        if (score >= 0.0 && score <= 10.0) {
            sum += score;
            count++;  
        } else {
            cout << "nota invalida\n";
        }
    }

    cout << "media = " << sum / 2.0 << endl;

    return 0;
}
