#include "lidarSensor.h"

std::vector<int> LidarSensor::ReadData(){
    // Usa as variáveis da classe em vez de números fixos
    std::uniform_int_distribution<> distr(1, maxDistance);
    
    std::vector<int> numbers(resolution);

    for(size_t i = 0; i < resolution; i++){
        numbers[i] = distr(gen); // O [] é levemente mais rápido que o .at() quando já garantimos o tamanho
    }

    return numbers;
}



