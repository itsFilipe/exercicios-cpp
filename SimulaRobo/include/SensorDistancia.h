#ifndef SENSOR_DISTANCIA_H
#define SENSOR_DISTANCIA_H

#include "Sensor.h"

class SensorDistancia : public Sensor {
private:
protected:
public:
    //como é o construtor mesmo?
    using Sensor::Sensor;

    virtual ~SensorDistancia() {} // Destrutor Virtual é obrigatório

    std::unique_ptr<std::vector<int>> readData() override {
        std::uniform_int_distribution<> distr(1, maxDistance);
        
        std::unique_ptr<std::vector<int>> vec_ptr_dist = std::make_unique<std::vector<int>>(resolution);

        for(size_t i = 0; i < resolution; i++){
            (*vec_ptr_dist)[i] = distr(gen); 
        }

        return vec_ptr_dist;
    }
};

#endif
