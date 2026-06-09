#include <iostream>

void exercise1(){
    int value {100};
    int *ptr = &value;

    std::cout << "EXERCICIO 1" << std::endl;
    std::cout << *ptr << std::endl;
    std::cout << ptr << std::endl;
    std::cout << "---------------" << std::endl;
}

void exercise2(){
    int number {50};
    int *num_ptr = &number;

    *num_ptr = 99;

    std::cout << "EXERCICIO 2" << std::endl;
    std::cout << *num_ptr << std::endl;
    std::cout << "---------------" << std::endl;
}

void exercise3(){
    int x {42};
    int *p1 = &x;
    int **p2 = &p1;

    std::cout << "EXERCICIO 3" << std::endl;
    std::cout << **p2 << std::endl;
    std::cout << "---------------" << std::endl;
}

void exercise4(){
    int data[] = {10, 20, 30, 40, 50};

    int *data_ptr = data;
    int tamanho = sizeof(data) / sizeof(int);

    std::cout << "EXERCICIO 4" << std::endl;
    for(int i {0}; i < tamanho; i++){
        std::cout << *data_ptr << " ";
        *data_ptr++;
    }
    std::cout << "\n" << "---------------" << std::endl;
}

void exercise5(){
    int scores[] = {85, 90, 78, 95, 88};

    int *score_ptr = scores;

    std::cout << "EXERCICIO 5" << std::endl;
    std::cout << *(scores + 2) << std::endl;
    std::cout << "---------------" << std::endl;
}

void exercise6(){
    char word[] = "CODE";

    char *char_ptr = word;

    std::cout << "EXERCICIO 6" << std::endl;
    std::cout << *(word + 2) << std::endl;
    std::cout << "---------------" << std::endl;
}

void exercise7(){
    std::cout << "EXERCICIO 7" << std::endl;

    int* safe_ptr = nullptr;
    if (safe_ptr == nullptr) {
        std::cout << "Pointer is null, cannot dereference." << std::endl;
        
        int valid_data = 77;
        safe_ptr = &valid_data;
    } 

    if (safe_ptr != nullptr) {
        std::cout << "Pointer is now valid. Dereferenced value: " << *safe_ptr << std::endl;
    }

    std::cout << "---------------" << std::endl;
}

void exercise8(int *ptr){
    if (ptr != nullptr)
        *ptr +=10;

    std::cout << "EXERCICIO 8" << std::endl;
    std::cout << *ptr << std::endl;
    std::cout << "---------------" << std::endl;
}

void exercise9(){
    int i {0};
    int *ptr = nullptr;

    std::cout << "EXERCICIO 9" << std::endl;
    std::cout << "Size of int: " << sizeof(i) << std::endl;
    std::cout << "Size of ptr: " << sizeof(ptr) << std::endl;
    std::cout << "---------------" << std::endl;
}

void exercise10(){
    int array[] = {1, 5, 10, 15, 20};
    int *array_ptr = array;
    int sum{0};
    int tamanho = sizeof(array) / sizeof(array[0]);

    for(int i{0} ; i < tamanho ; i++)
        sum += *(array_ptr + i);

    std::cout << "EXERCICIO 10" << std::endl;
    std::cout << "The sum of array elements is: " << sum << std::endl;
    std::cout << "----------------" << std::endl;
}

void exercise11(){
    int numbers[] = {1, 2, 3, 4, 5};

    int *numbers_ptr = numbers;
    int tamanho = (sizeof(numbers) / sizeof(int)) - 1;

    std::cout << "EXERCICIO 11" << std::endl;
    for(int i = tamanho; i >= 0; i--){
        std::cout << *(numbers_ptr + i) << " ";
    }
    std::cout << "\n" << "---------------" << std::endl;
}

int* exercise12(int arr[], int s){
    if (s == 0)
        return nullptr;

    int *smallest_ptr = arr;

    for(int i{0}; i < s; i++){
        if (*smallest_ptr > *(arr + i))
            smallest_ptr = &arr[i];
    }

    return smallest_ptr;
}

void exercise13(){
    int matrix[3][3] = {
     {1, 2, 3},
     {4, 5, 6},
     {7, 8, 9}
    };

    int *matrix_ptr = &matrix;
    int tamanho = sizeof(matrix) / sizeof(int);

    for(int i{0}; i < tamanho ; i++)
}

//tem até o 30 !!!!!

int main(){
    exercise1();
    exercise2();
    exercise3();
    exercise4();
    exercise5();
    exercise6();
    exercise7();

    int n {15};
    exercise8(&n);

    exercise9();
    exercise10();
    exercise11();

    std::cout << "EXERCICIO 12" << std::endl;
    int array[] = {45, 12, 67, 8, 33};
    int size = sizeof(array) / sizeof(array[0]);
    int *ptr = exercise12(array, size);
    if (ptr != nullptr){
         std::cout << "The smallets element is " << *ptr << std::endl;
    } else {
        std::cout << "the array is empty." <<std::endl;
    }
    std::cout << "---------------" << std::endl;

    return 0;
}