#include <iostream>
#include <vector>
#include <map>

std::map<std::string, int> contabilizar(const std::vector<std::string> &producao){
    std::map<std::string, int> producao_contabilizada;

    for(const auto &produto : producao)
        // O operador [] busca o produto. Se não existir, cria com valor 0 e soma 1.
        producao_contabilizada[produto] += 1;

    return producao_contabilizada;
}

void print_map(const std::map<std::string, int>& m){
    for (const auto& [key, value] : m)
        std::cout << '[' << key << "] = " << value << std::endl;
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
