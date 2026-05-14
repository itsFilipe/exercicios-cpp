#include <iostream>
#include <set>

int main(){

    std::set<char> suits = {'C', 'H', 'S', 'D'};

    //std::set<char>::iterator it = vetor.begin();

    auto it = suits.begin();

    while (it != suits.end()) {
        std::cout << *it << " " << std::endl;
        ++it;
    }

    return 0;
}