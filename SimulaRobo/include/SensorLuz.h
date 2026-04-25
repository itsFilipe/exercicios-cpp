#ifndef SENSOR_LUZ_H
#define SENSOR_LUZ_H

#include "Sensor.h"

class SensorLuz : public Sensor {
private:
    int min;
protected:
public:
    SensorLuz(int res, int max, int min)
        : Sensor(res, max), min(min) {}

    virtual ~SensorLuz() {} // Destrutor Virtual é obrigatório

    std::unique_ptr<std::vector<int>> readData() override {
        std::uniform_int_distribution<> distr(min, maxDistance);
        
        std::unique_ptr<std::vector<int>> vec_ptr_luz = std::make_unique<std::vector<int>>(resolution);

        for(size_t i = 0; i < resolution; i++){
            (*vec_ptr_luz)[i] = distr(gen); 
        }

        return vec_ptr_luz;
    }
};

#endif
