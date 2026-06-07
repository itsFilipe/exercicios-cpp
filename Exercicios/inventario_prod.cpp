#include <iostream>
#include <vector>
#include <map>

std::map<std::string, int> contabilizar(const std::vector<std::string> &producao){
    std::map<std::string, int> producao_contabilizada;

    for(const auto produto : producao){
        auto it = producao_contabilizada.find(produto);
        if(it != producao_contabilizada.end())
            producao_contabilizada[produto] += 1;

        producao_contabilizada[produto] = 1;
    }

    return producao_contabilizada;
}

void print_map(const std::map<std::string, int>& m){
    for (const auto& [key, value] : m)
        std::cout << '[' << key << "] = " << value << "; ";
}

int main(){

    std::vector<std::string> lote = {
    "Terminal de Cobre", "Conector Bimetalico", "Terminal de Cobre",
    "Luva de Emenda", "Conector Bimetalico", "Terminal de Cobre",
    "Terminal de Aluminio", "Luva de Emenda"
    };

    std::map<std::string, int> inventario = contabilizar(lote);
    print_map(inventario);

    return 0;
}
