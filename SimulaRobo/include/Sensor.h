#ifndef SENSOR_H
#define SENSOR_H

#include <random>
#include <vector>
#include <memory>

class Sensor {
private:
protected:
    std::mt19937 gen;
    int maxDistance;
    int resolution;
public:
    Sensor(int resolution = 100, int maxDistance = 100){
        std::random_device rd;
        gen = std::mt19937(rd());
        this->resolution = resolution;
        this->maxDistance = maxDistance;
    }

    virtual ~Sensor() {} // Destrutor Virtual é obrigatório

    virtual std::unique_ptr<std::vector<int>> readData() = 0;
};

#endif
