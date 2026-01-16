#include <iostream>

int main() {
    int x;

    while (std::cin >> x && x != 0) {
        for (int i = 1; i <= x; ++i) {
            std::cout << i;
            if (i != x) {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }

    return 0;
}