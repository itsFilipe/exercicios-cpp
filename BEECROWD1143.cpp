#include <iostream>

using namespace std;

int main() {

    size_t n {0};
    size_t num {1};

    cin >> n;

    for(size_t i{0} ; i < n ; ++i) {
        cout << num << " " << num * num << " " << num * num * num << endl; 

        num += 1;
    }

    return 0;
}