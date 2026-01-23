#include <iostream>

int main() {
    int A, N, sum = 0;

    std::cin >> A;
    while (std::cin >> N && N <= 0);

    for (int i = 0; i < N; i++) {
        sum += (A + i);
    }

    std::cout << sum << std::endl;

    return 0;
}