#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <list>

void display(const std::vector<int> &vec) {
    std::cout << "[ ";
    for (auto const &i: vec) {
        std::cout << i << " ";
    }
    std::cout << "]" << std::endl;
}

void teste1() {
    std::cout << "\n=============================" << std::endl;
    std::vector<int> nums1 {1, 2, 3, 4, 5}; //begin é 1, e end é o proximo depois do ultimo
    auto it = nums1.begin();            // aponta para 1
    std::cout << *it << std::endl;

    it++;                                           // aponta para 2
    std::cout << *it << std::endl;      

    it += 2;                                        // aponta para 4
    std::cout << *it << std::endl;

    it -= 2;                                        // aponta para 2
    std::cout << *it << std::endl;

    it = nums1.end() - 1;                           // aponta para 5
    std::cout << *it << std::endl;
}

void teste2() {
    std::cout << "\n=============================" << std::endl;
    // display all vector elements using an iterator
    
    std::vector<int> nums1 {1, 2, 3, 4, 5};

    std::vector<int>::iterator it = nums1.begin();
    while (it != nums1.end()) {
        std::cout << *it << std::endl;
        it++;
    }
    
    // change all vector elements to 0
    it = nums1.begin();
    while (it != nums1.end()) {
        *it = 0;
        it++;
    }

    display(nums1);
}

void teste3() {
    
    // using a const_iterator
    std::cout << "\n=============================" << std::endl;
    std::vector<int> nums1 {1, 2, 3, 4, 5};

    std::vector<int>::const_iterator it1 = nums1.begin();
    // auto it1 = nums1.cbegin();
    
    while (it1 != nums1.end()) {
        std::cout << *it1 << std::endl;
        it1++;
    }
    
    // compiler error when we try to change element
    it1 = nums1.begin();
    while (it1 != nums1.end()) {
       // *it1 = 0;   // Complier error - read only
        it1++;
    }

}

void teste4() {
    // more iterators
    // using a reverse iterator
    std::vector<int> vec {1,2,3,4};
    auto it1  = vec.rbegin();       // reverse iterator over vector of ints starts at 4
    while (it1 != vec.rend()) {
        std::cout << *it1 << std::endl;
        it1++;
    }

    // const reverse iterator over a list
    std::list<std::string> name {"Filipe", "Scott", "Rana"};
    auto it2 =name.crbegin();    // iterator over list of strings  point to Curly
    std::cout << *it2 << std::endl;
    it2++;  
    std::cout << *it2 << std::endl;

    // iterator over a map
    std::map<std::string, std::string> favorites {
        {"Filipe", "C++"},
        {"Scott", "Xuxu"},
        {"Rana", "Gatos"}
    };
    auto it3 = favorites.begin();   // iterator over map of string, string pairs
    while (it3 != favorites.end()) {
        std::cout << it3->first << " Ama " << it3->second << std::endl;
        it3++;
    }
}

void teste5() {
    // iterate over a subset of a container
    std::vector<int> vec {1,2,3,4,5,6,7,8,9,10};
    auto start = vec.begin() + 2;
    auto finish = vec.end() - 3;
    
    while (start != finish) {
        std::cout << *start << std::endl;
        start++;
    }
    
}
int main() {
    int n {0};
    std::cout << "Escolha uma opcao: " << std::endl;
    std::cout << "1 - Incremento de iterador" << std::endl;
    std::cout << "2 - Exibindo todos os elementos de um vector" << std::endl;
    std::cout << "3 - iterator Constante" << std::endl;
    std::cout << "4 - Outros iteradores" << std::endl;
    std::cout << "5 - Iterar em um subset do container" << std::endl;
    std::cout << "6 - Sair" << std::endl;
    std::cin >> n;
    std::cout << "---------------------------------------------" << std::endl;
    switch (n) {
        case 1:
            teste1();
            break;
        case 2:
            teste2();
            break;
        case 3:
            teste3();
            break;
        case 4:
            teste4();
            break;
        case 5:
            teste5();
            break;
        case 6:
            break;
        default:
            std::cout << "Invalid option" << std::endl;
            break;
    }

    return 0;
}