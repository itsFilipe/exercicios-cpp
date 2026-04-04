#include "lidarSensor.h"

std::unique_ptr<std::vector<int>> LidarSensor::ReadData(){
    // Usa as variáveis da classe em vez de números fixos
    std::uniform_int_distribution<> distr(1, maxDistance);
    
    std::unique_ptr<std::vector<int>> vec_ptr = std::make_unique<std::vector<int>>(resolution);

    for(size_t i = 0; i < resolution; i++){
        (*vec_ptr)[i] = distr(gen); // O [] é levemente mais rápido que o .at() quando já garantimos o tamanho
    }

    return vec_ptr;
}



