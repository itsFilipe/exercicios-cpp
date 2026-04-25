#ifndef SENSOR_GIROSCOPIO_H
#define SENSOR_GIROSCOPIO_H

#include "Sensor.h"

class SensorGiroscopio : public Sensor {
private:
    int min;
protected:
public:
    SensorGiroscopio(int res, int max, int min)
        : Sensor(res, max), min(min) {}

    virtual ~SensorGiroscopio() {} // Destrutor Virtual é obrigatório

    std::unique_ptr<std::vector<int>> readData() override {
        std::uniform_int_distribution<> distr(min, maxDistance);
        
        std::unique_ptr<std::vector<int>> vec_ptr_giro = std::make_unique<std::vector<int>>(resolution);

        for(size_t i = 0; i < resolution; i++){
            (*vec_ptr_giro)[i] = distr(gen); 
        }

        return vec_ptr_giro;
    }
};

#endif
