#include "lidarSensor.h"
#include <iostream>

int main(){

    LidarSensor sensor;

    std::unique_ptr<std::vector<int>> num;

    num = sensor.ReadData();

    // Lê-se: "Para cada valor inteiro 'val' dentro de '*num'..."
    for (int val : *num) {
        std::cout << val << " ";
    }
    
    return 0;
}