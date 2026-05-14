#include <iostream>
#include <vector>

int main(){

    std::vector<int> vetor = {1, 2, 3};

    //std::vector<int>::iterator it = vetor.begin();

    for(auto it = vetor.begin(); it != vetor.end(); it++){
        std::cout << *it << " ";
    }

    return 0;
}