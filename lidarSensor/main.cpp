#include "lidarSensor.h"
#include "lidarFilter.h"
#include <iostream>
#include <memory>
#include <vector>

int main(){
    std::cout << "--- Inicializando Modulos do Carro ---" << std::endl;
    // O Lidar vai gerar resolucoes grandes de dados com o maximo possivel em 115
    LidarSensor sensor(1000, 115); 
    
    // O filtro via "ignorar" tudo que for erro da reflexao e focar no que e importante
    LidarFilter filter(5, 100);

    // Passo 1: O Sensor recebe dados e aloca 1000 numeros na memória Heap
    std::unique_ptr<std::vector<int>> raw_ptr = sensor.ReadData();
    std::cout << "1. Sensor adquiriu dados brutos. Tamanho na memoria: " << raw_ptr->size() << " pontos.\n";

    // Passo 2: O Pipeline. O Filtro pede posse ABSOLUTA para trabalhar. 
    // Como unique_ptr nao pode ser copiado, a gente passa ele no formato 'std::move()'.
    // Durante a execucão dessa funcao, a variavel raw_ptr do Main fica temporariamente esvaziada ("null").
    
    std::unique_ptr<std::vector<int>> clean_ptr = filter.applyFilter(std::move(raw_ptr));

    // Passo 3: Retorno. O dado agora eh um pacote filtrado. Imprimindo resultado:
    std::cout << "2. Filtro de Ruido aplicado com sucesso (Zero Cópias Realizadas).\n";
    std::cout << "3. Dados limpos, novo tamanho na memoria: " << clean_ptr->size() << " pontos validos.\n";

    std::cout << "\nPrimeiros 10 pontos limpos para inspecao:\n[ ";
    for (size_t i = 0; i < 10 && i < clean_ptr->size(); i++) {
        std::cout << (*clean_ptr)[i] << " ";
    }
    std::cout << "]" << std::endl;
    
    return 0; // A memoria limpa restante do ponteiro vai ser apagada da RAM aqui.
}