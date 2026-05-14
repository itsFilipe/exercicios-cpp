// Section 20
// Algorithms
// TODO: Estudar C++20 Ranges (<ranges>) — evolucao direta dos algoritmos abaixo.
// Com Ranges, os algoritmos ficam mais limpos (sem .begin()/.end()) e componiveis via pipe (|).
// Ex: vec | std::views::filter(...) | std::views::transform(...)
// E o padrao moderno e mais utilizado na industria.

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>  // accumulate, iota, reduce
#include <cctype>

class Person {
    std::string name;
    int age;
public:
    Person() = default;
    Person(std::string name, int age) 
        : name{name}, age{age}  {}
    bool operator<(const Person &rhs) const {
        return this->age < rhs.age;
    }
    bool operator==(const Person &rhs) const {
        return (this->name == rhs.name && this->age == rhs.age);
    }
        
    std::string get_name() const {
        return name;
    }
};

// Find an element in a container
void find_test() {
    std::cout << "\n========================" << std::endl;

    std::vector<int> vec {1,2,3,4,5};
    
    auto loc = std::find(std::begin(vec), std::end(vec), 1); //mesma coisa que std::find(vec.begin(), vec.end(), 1)
    
    if (loc != std::end(vec))
        std::cout << "Found the number: " << *loc <<  std::endl;
    else 
        std::cout << "Couldn't find the number" << std::endl;
        
    std::list<Person> players {
        {"Larry", 18},
        {"Moe", 20},
        {"Curly", 21}
    };
    
    auto loc1 = std::find(players.begin(), players.end(), Person{"Moe", 20});
    if (loc1 != players.end())
        std::cout << "Found  Moe" << std::endl;
    else
        std::cout << "Moe not found" << std::endl;

    //e para procurar por atributo: usa-se o std::find_if e uma lambda expression para comparar o atributo
    auto loc2 = std::find_if(players.begin(), players.end(), [](const Person &p) { return p.get_name() == "Moe"; });
    if (loc2 != players.end())
        std::cout << "Found  Moe" << std::endl;
    else
        std::cout << "Moe not found" << std::endl;
}

// Count the number of elements in a container
void count_test() {
    std::cout << "\n========================" << std::endl;

     std::vector<int> vec {1,2,3,4,5,1,2,1};
     
     int num = std::count(vec.begin(), vec.end(), 1);
     std::cout << num << " occurrences found" << std::endl;
}

// Count the number of occurences of an element in a container
// based on a predicate using a lambda expression

void count_if_test() {
    std::cout << "\n========================" << std::endl;

    // count only if the element is even
    std::vector<int> vec {1,2,3,4,5,1,2,1,100};
    int num = std::count_if(vec.begin(), vec.end(), [](int x) { return x %2 == 0; });
    std::cout << num << " even numbers found" << std::endl;
    
    num = std::count_if(vec.begin(), vec.end(), [](int x) { return x %2 != 0; });
    std::cout << num << " odd numbers found" << std::endl;
    
    // how can we determine how many elements in vec are >= 5?
    num = std::count_if(vec.begin(), vec.end(), [](int x) { return x>=5;   });
    std::cout << num << "  numbers are >= 5" << std::endl;

}

// Replace occurrences of elements in a container
void replace_test() {
    std::cout << "\n========================" << std::endl;

     std::vector<int> vec {1,2,3,4,5,1,2,1};
     for (auto i: vec) {
         std::cout << i << " ";
     }
     std::cout << std::endl;
     
    std::replace(vec.begin(), vec.end(), 1, 100);
    for (auto i: vec) {
         std::cout << i << " ";
     }
    std::cout << std::endl;
}

void all_of_test() {
    std::vector<int> vec1 {1,3,5,7,9,1,3,13,19,5};
    if (std::all_of(vec1.begin(), vec1.end(), [](int x) { return x > 10; }))
        std::cout << "All the elements are > 10" << std::endl;
    else    
        std::cout << "Not all the elements are > 10" << std::endl;
    
    if (std::all_of(vec1.begin(), vec1.end(), [](int x) { return x < 20; }))
        std::cout << "All the elements are < 20" << std::endl;
    else    
        std::cout << "Not all the elements are < 20" << std::endl;        
}

// Transform elements in a container - string in this example
void string_transform_test() {
    std::cout << "\n========================" << std::endl;

    std::string str1 {"This is a test"};
    std::cout << "Before transform: " << str1 << std::endl;
    std::transform(str1.begin(), str1.end(), str1.begin(), ::toupper); //:: significa que a funcao toupper esta na biblioteca global
    std::cout << "After transform: " << str1 << std::endl;
}

// ---- NOVOS SHOWCASES ----

// Ordenacao com std::sort e std::stable_sort
void sort_test() {
    std::cout << "\n========================" << std::endl;

    std::vector<int> vec {5, 3, 1, 4, 2};
    std::cout << "Antes do sort: ";
    for (auto i : vec) std::cout << i << " ";
    std::cout << std::endl;

    std::sort(vec.begin(), vec.end()); // ordena em ordem crescente
    std::cout << "Depois do sort: ";
    for (auto i : vec) std::cout << i << " ";
    std::cout << std::endl;

    // stable_sort preserva a ordem relativa de elementos iguais
    std::vector<std::pair<int,std::string>> pessoas {{2,"Ana"},{1,"Bob"},{2,"Carlos"},{1,"Diana"}};
    std::stable_sort(pessoas.begin(), pessoas.end()); // ordena pelo primeiro campo (int)
    std::cout << "Apos stable_sort: ";
    for (auto& p : pessoas) std::cout << "(" << p.first << "," << p.second << ") ";
    std::cout << std::endl;
}

// Busca binaria com std::binary_search, lower_bound e upper_bound
// IMPORTANTE: o container precisa estar ordenado!
void binary_search_test() {
    std::cout << "\n========================" << std::endl;

    std::vector<int> vec {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // binary_search: retorna true/false
    bool found = std::binary_search(vec.begin(), vec.end(), 5);
    std::cout << "binary_search(5): " << (found ? "encontrado" : "nao encontrado") << std::endl;

    // lower_bound: iterador para o primeiro elemento >= valor
    auto low = std::lower_bound(vec.begin(), vec.end(), 4);
    std::cout << "lower_bound(4): " << *low << std::endl; // 4

    // upper_bound: iterador para o primeiro elemento > valor
    auto up = std::upper_bound(vec.begin(), vec.end(), 4);
    std::cout << "upper_bound(4): " << *up << std::endl; // 5
}

// Remocao, copia e unicidade
void remove_copy_unique_test() {
    std::cout << "\n========================" << std::endl;

    // remove_if + erase (idioma erase-remove)
    std::vector<int> vec {1, 2, 3, 4, 5, 6, 7, 8};
    vec.erase(std::remove_if(vec.begin(), vec.end(), [](int x){ return x % 2 == 0; }), vec.end());
    std::cout << "Apos remover pares: ";
    for (auto i : vec) std::cout << i << " ";
    std::cout << std::endl;

    // copy: copia elementos de um container para outro
    std::vector<int> origem {10, 20, 30, 40, 50};
    std::vector<int> destino(origem.size());
    std::copy(origem.begin(), origem.end(), destino.begin());
    std::cout << "Apos copy: ";
    for (auto i : destino) std::cout << i << " ";
    std::cout << std::endl;

    // unique: remove duplicatas CONSECUTIVAS (precisa estar ordenado para remover todas)
    std::vector<int> dups {1, 1, 2, 3, 3, 3, 4, 5, 5};
    auto it = std::unique(dups.begin(), dups.end());
    dups.erase(it, dups.end());
    std::cout << "Apos unique: ";
    for (auto i : dups) std::cout << i << " ";
    std::cout << std::endl;
}

// Algoritmos numericos: std::accumulate e std::iota
void numeric_test() {
    std::cout << "\n========================" << std::endl;

    // iota: preenche um range com valores sequenciais
    std::vector<int> vec(5);
    std::iota(vec.begin(), vec.end(), 1); // 1, 2, 3, 4, 5
    std::cout << "Apos iota: ";
    for (auto i : vec) std::cout << i << " ";
    std::cout << std::endl;

    // accumulate: soma (ou outra operacao binaria) todos os elementos
    int soma = std::accumulate(vec.begin(), vec.end(), 0);
    std::cout << "Soma (accumulate): " << soma << std::endl;

    // accumulate com lambda: produto de todos os elementos
    int produto = std::accumulate(vec.begin(), vec.end(), 1, [](int acc, int x){ return acc * x; });
    std::cout << "Produto (accumulate): " << produto << std::endl;
}

// Particao: separa elementos que satisfazem um predicado
void partition_test() {
    std::cout << "\n========================" << std::endl;

    std::vector<int> vec {1, 2, 3, 4, 5, 6, 7, 8, 9};
    // partition: pares ficam no inicio, impares no final
    auto it = std::partition(vec.begin(), vec.end(), [](int x){ return x % 2 == 0; });
    std::cout << "Pares: ";
    for (auto i = vec.begin(); i != it; ++i) std::cout << *i << " ";
    std::cout << "\nImpares: ";
    for (auto i = it; i != vec.end(); ++i) std::cout << *i << " ";
    std::cout << std::endl;
}

// Minimo e maximo de um container
void minmax_test() {
    std::cout << "\n========================" << std::endl;

    std::vector<int> vec {3, 1, 4, 1, 5, 9, 2, 6, 5};

    auto min_it = std::min_element(vec.begin(), vec.end());
    auto max_it = std::max_element(vec.begin(), vec.end());

    std::cout << "Minimo: " << *min_it << std::endl;
    std::cout << "Maximo: " << *max_it << std::endl;
}

int main() {
    int n {0};
    do {        
    std::cout << "\n========================" << std::endl;
    std::cout << "Escolha a opcao: " << std::endl;
    std::cout << "1.  Find" << std::endl;
    std::cout << "2.  Count" << std::endl;
    std::cout << "3.  Count if" << std::endl;
    std::cout << "4.  Replace" << std::endl;
    std::cout << "5.  All of" << std::endl;
    std::cout << "6.  String transform" << std::endl;
    std::cout << "7.  Sort" << std::endl;
    std::cout << "8.  Binary search" << std::endl;
    std::cout << "9.  Remove / Copy / Unique" << std::endl;
    std::cout << "10. Numeric (iota + accumulate)" << std::endl;
    std::cout << "11. Partition" << std::endl;
    std::cout << "12. Min / Max element" << std::endl;
    std::cout << "0.  Sair" << std::endl;
    std::cin >> n;
    switch(n) {
        case 1:  find_test(); break;
        case 2:  count_test(); break;
        case 3:  count_if_test(); break;
        case 4:  replace_test(); break;
        case 5:  all_of_test(); break;
        case 6:  string_transform_test(); break;
        case 7:  sort_test(); break;
        case 8:  binary_search_test(); break;
        case 9:  remove_copy_unique_test(); break;
        case 10: numeric_test(); break;
        case 11: partition_test(); break;
        case 12: minmax_test(); break;
        case 0:  return 0;
        default: std::cout << "Opcao invalida" << std::endl;
    }
    }while(n != 0);

    return 0;
}

