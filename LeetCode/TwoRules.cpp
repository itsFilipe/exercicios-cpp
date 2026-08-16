#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) { // metodo da classe
        for (int i = 0; i < nums.size(); i++)
        {
            for (int j = i + 1; j < nums.size(); j++)
            {
                if(target == nums.at(i) + nums.at(j)){
                    return {i, j};
                }
            }

        }
        
        return {};
    }
};

/*
    Meu primeiro código usei 2 break, 3 variaveis, apenas para sair dos loops e guardar a variavel, mas nao é necessário...
    return já quebra o loop na hora, e dá para guardar valor em vetor direto.

    antes:
    for (int i = 0; i < nums.size(); i++)
        {
            for (int j = i + 1; j < nums.size(); j++)
            {
                if(target == nums.at(i) + nums.at(j)){
                    found = true;
                    firstN = i;
                    secondN = j;
                    break;
                }
            }

            if (found)  
                break;
        }

    para otimizar, deve ser utilizado hashmap....
*/

int main(){
    Solution teste;
    std::vector<int> nums = {3, 2, 4};
    int target = 6;

    std::vector<int> answer = teste.twoSum(nums, target);

    if (!answer.empty()){
        for (auto i : answer){
            std::cout << i << " ";
        }   
    } else {
        std::cout << "Sem solucao\n";
    }
}