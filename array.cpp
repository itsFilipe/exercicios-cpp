#include <iostream>
using namespace std;

int main() {
    int v[50] {0};  //importante inicializar o array para evitar lixo de memoria
    int j = 0;

    for(int i = 0; i < 100; i += 2) {
        v[j] = i;
        // Using `endl` flushes the output buffer, while `\n` is usually more efficient
        cout << v[j] << "\n"; 
        j++;
    }

    int n;
    cout << "Enter a number to search: "; 
    cin >> n;

    bool found = false; // Use a flag to track if the element is found

    for(int i = 0; i < 50; i++){ 
        if(n == v[i]){
            cout << "element " << n << " is at array position " << i << "\n";
            found = true;
            // Optional: break the loop once found for efficiency
            // break; 
        }
    }
    
    if (!found) {
        cout << "Element " << n << " was not found in the array." << "\n";
    }

    return 0;
}
