/* exception handling é uma forma segura de lidar com erros, principalmente 
   em funções que não podem retornar o erro, então a exception é capturada por um catch, que está na stack
   irei falar um pouco mais do uso e do porque existe... Segue exemplo abaixo
*/

#include <iostream>

int main(){
    int km {0};
    int litros {0};
    double km_por_litros;

    std::cout << "Digite a kilometragem: " << std::endl;
    std::cin >> km;
    std::cout << "Digite os litros: " << std::endl;
    std::cin >> litros;

    try { /* embala logica que possivelmente pode resultar em exceção, exemplo div por 0*/
        if (litros == 0){
            throw std::runtime_error("Não pode dividir por 0");
        }

        if (litros < 0 || km < 0){
            throw std::out_of_range("Não pode ter numeros negativos");
        }
        km_por_litros = static_cast<double>(km) / litros;
        std::cout << "Andou " << km_por_litros << " km por litro." << std::endl;
    }

    catch (const std::runtime_error &ex) {
        std::cerr << ex.what() << std::endl;
    }

    catch (const std::out_of_range &ex) {
        std::cerr << ex.what() << std::endl;
    }
    
    catch (...) { // catch-all — captura qualquer exceção não tratada acima
        std::cerr << "Erro desconhecido" << std::endl;
    }

    std::cout << "Fim" << std::endl;
}

/* caso exista a exceção, existe o throw e o catch captura, e o programa é finalizado
   se não tivesse o catch, programa seria finalizado instantaneamente, o fim nao seria imprimido
   isso é eficiente em locais que o return é limitado, uma função que nao sabe lidar com um erro, etc
*/