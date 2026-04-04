#ifndef _LIDAR_SENSOR_
#define _LIDAR_SENSOR_

#include <random>
#include <vector>
#include <memory>

class LidarSensor {
private:
    std::mt19937 gen;
    int maxDistance;
    int resolution; // Quantidade de pontos (ex: 360)

public:
    // Construtor agora aceita parâmetros (com valores padrão)
    LidarSensor(int resolution = 360, int maxDistance = 115) {
        std::random_device rd; 
        gen = std::mt19937(rd());
        this->resolution = resolution;
        this->maxDistance = maxDistance;
    }

    //metodo vai retornar um ponteiro unico que aponta pra um vetor de inteiros
    std::unique_ptr<std::vector<int>> ReadData();
};

#endif