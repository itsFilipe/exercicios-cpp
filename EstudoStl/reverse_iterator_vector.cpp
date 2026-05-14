#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec {1, 2, 3};
    // Use rbegin() para o início reverso e rend() para o fim reverso
    std::vector<int>::reverse_iterator it = vec.rbegin(); 
    
    while (it != vec.rend()) {
        std::cout << *it << " "; // Saída: 3 2 1
        ++it;
    }

    return 0;
}
